// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// You may use this file under the terms of the BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ****************************************************************************


#include "importdialog.hxx"

#include <cadex/ACIS_Reader.hxx>
#include <cadex/Base_ProgressScope.hxx>
#include <cadex/Base_ProgressStatus.hxx>
#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelAlgo_BRepMesher.hxx>
#include <cadex/ModelData_Model.hxx>
#include <iostream>
#include <cmath>

#include <QtCore/QThreadPool>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#else
#include <QtGui/QApplication>
#include <QtGui/QCheckBox>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#endif

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

static void Perform (const Base_UTF16String& theFileName, ImportDialog* theOwner);

enum EventType {
    ProgressValueId = QEvent::User + 1, // Progress value change notification
    CompletedId                         // Completed operation notification
};

class ImportDialog::CancellationChecker : public Base_ProgressStatus::CancellationChecker
{
public:

    CancellationChecker() : myIsCanceled (false) {}

    __CADEX_DEFINE_PRIMITIVE_PROPERTY (bool, IsCanceled)

    bool operator()() const override
    {
        return myIsCanceled;
    }
};

/*! Event holding a value of the progress status.*/
class ProgressValueEvent : public QEvent
{
public:

    ProgressValueEvent (int theValue) : QEvent (static_cast<QEvent::Type> (ProgressValueId)), myValue (theValue)
    {}

    int Value() const
    {
        return myValue;
    }

private:

    int myValue;
};

class ProgressBarProxy : public QObject
{
public:

    ProgressBarProxy (QObject* theParent, QProgressBar* theProgressBar) :
        QObject (theParent), myProgressBar (theProgressBar) {}

    void SetValue (cadex::Base_ProgressStatus::value_type theValue)
    {
        bool anIsGuiThread = thread() == QThread::currentThread();
        int aValue = static_cast<int> (floor (theValue + 0.5f)); //round
        if (anIsGuiThread) {
            myProgressBar->setValue (aValue);
            QCoreApplication::processEvents(); //enforce redraw
        } else {
            QCoreApplication::postEvent (this, new ProgressValueEvent (aValue));
        }
    }

protected:

    void customEvent (QEvent* theEvent) override
    {
        int aType = theEvent->type();
        if (aType == ProgressValueId) {
            ProgressValueEvent* anEvent = static_cast<ProgressValueEvent*> (theEvent);
            int aValue = anEvent->Value();
            myProgressBar->setValue (aValue);
            theEvent->accept();
        } else {
            QObject::customEvent (theEvent);
        }
    }

    QProgressBar* myProgressBar;
};

class ProgressBarObserver : public Base_ProgressStatus::Observer
{
public:

    ProgressBarObserver (ProgressBarProxy* theProxy) : myProxy (theProxy) {}

    void ChangedValue (const Base_ProgressStatus& theInfo) override
    {
        cout << theInfo.Value() << endl;
    }

    void Completed (const Base_ProgressStatus& theInfo) override
    {
        cout << theInfo.Value() << ": complete!" << endl;
    }

private:

    ProgressBarProxy* myProxy;
};

class Worker : public QRunnable
{
public:

    Worker (const Base_UTF16String& theFileName, ImportDialog* theOwner) : myFileName (theFileName), myOwner (theOwner)
    {}

protected:

    void run() override
    {
        Perform (myFileName, myOwner);
    }

    const Base_UTF16String  myFileName;
    ImportDialog*           myOwner;
};

ImportDialog::ImportDialog()
    {
        QVBoxLayout *aMainLayout = new QVBoxLayout;

        QLabel* aFileLabel = new QLabel (tr ("File:"));
        myFileNameLabel = new QLabel ();
        myFileNameLabel->setFrameShape (QFrame::StyledPanel);
        QPushButton* aBrowseButton = new QPushButton (tr ("..."));
        myThreadCheckBox = new QCheckBox (tr ("Start in a worker thread"));

        myStartButton = new QPushButton (tr ("Start"));
        myStartButton->setEnabled (false);
        myCancelButton = new QPushButton (tr ("Cancel"));
        myCancelButton->setEnabled (false);

        myProgressBar = new QProgressBar;
        myProgressBar->setMinimum (Base_ProgressStatus::MinValue());
        myProgressBar->setMaximum (Base_ProgressStatus::MaxValue());

        QHBoxLayout* aFileNameLayout = new QHBoxLayout;
        aFileNameLayout->addWidget (aFileLabel);
        aFileNameLayout->addWidget (myFileNameLabel, 1 /*stretch*/);
        aFileNameLayout->addWidget (aBrowseButton);

        QHBoxLayout* aButtonLayout = new QHBoxLayout;
        aButtonLayout->addWidget (myStartButton);
        aButtonLayout->addWidget (myCancelButton);

        aMainLayout->addLayout (aFileNameLayout);
        aMainLayout->addWidget (myThreadCheckBox);
        aMainLayout->addLayout (aButtonLayout);
        aMainLayout->addSpacing(12);
        aMainLayout->addWidget (myProgressBar);
        aMainLayout->addStretch (1);
        setLayout (aMainLayout);

        myProgressBarProxy = new ProgressBarProxy (this, myProgressBar);

        myCancellationChecker.reset (new CancellationChecker());

        connect (aBrowseButton,  SIGNAL (clicked()), this, SLOT (BrowseFile()));
        connect (myStartButton,  SIGNAL (clicked()), this, SLOT (Start()));
        connect (myCancelButton, SIGNAL (clicked()), this, SLOT (Cancel()));
    }

void ImportDialog::BrowseFile()
{
    QString aFileName = QFileDialog::getOpenFileName (this, tr ("Open File"),
        myFileNameLabel->text(), tr ("ACIS-SAT files (*.sat)"));
    if (!aFileName.isEmpty()) {
        myFileNameLabel->setText (aFileName);
        myStartButton->setEnabled (true);
    }
}

void ImportDialog::Start()
{
    if (myCancellationChecker)
        myCancellationChecker->IsCanceled() = false;
    myStartButton->setEnabled (false);
    myCancelButton->setEnabled (true);

    myProgressBar->reset();
    bool anIsWorkerThread = myThreadCheckBox->isChecked();
    Base_UTF16String aFileName (myFileNameLabel->text().utf16());

    if (anIsWorkerThread) {
        //QRunnable will be deleted by thread pool
        Worker* aWorker = new Worker (aFileName, this);
        QThreadPool::globalInstance()->start (aWorker);
    } else {
        Perform (aFileName, this);
    }
}

void ImportDialog::Cancel()
{
    if (myCancellationChecker)
        myCancellationChecker->IsCanceled() = true;
}

void ImportDialog::customEvent (QEvent* theEvent)
{
    int aType = theEvent->type();
    if (aType == CompletedId) {
        myStartButton->setEnabled (true);
        myCancelButton->setEnabled (false);
        if (myCancellationChecker)
            myCancellationChecker->IsCanceled() = true;
        theEvent->accept();
    } else {
        QDialog::customEvent (theEvent);
    }
}

static void Perform (const Base_UTF16String& theFileName, ImportDialog* theOwner)
{
    ProgressBarProxy* aProgressBarProxy = theOwner->GetProgressBarProxy();

    // An observer must have a greater life span than aStatus
    // So create it in explicit external scope for aStatus
    ProgressBarObserver anObserver (aProgressBarProxy);
    //allow all threads to notify, synchronization is done by the proxy itself
    anObserver.SetAllNotifyingThreads();
    {
        ModelData_Model aModel;

        Base_ProgressStatus aStatus;
        aStatus.Register (anObserver);                              // Register an Observer to progress status

        if (theOwner->GetCancellationChecker()) {
            aStatus.SetCancellationChecker (*theOwner->GetCancellationChecker());
        }

        bool anIsOK = false;
        Base_ProgressScope aTopScope (aStatus);                     //take entire remaining range (in this case 100%)
        {
            Base_ProgressScope aReaderScope (aTopScope, 40);        // 40% of TopScope for file importing

            ACIS_Reader aReader;
            aReader.ProgressStatus() = aStatus;                     // Connect progress status object

            if (!aStatus.WasCanceled()) {
                Base_ProgressScope aSubScope (aReaderScope, 25);    // 25% of ReaderScope (10% of TopScope)
                anIsOK = aReader.ReadFile (theFileName);
            }
            if (anIsOK && !aStatus.WasCanceled()) {
                Base_ProgressScope aSubScope (aReaderScope, 75);    // 75% of ReaderScope (30% of TopScope)
                anIsOK = aReader.Transfer (aModel);
            }
        }
        if (anIsOK && !aStatus.WasCanceled()) {
            Base_ProgressScope aMesherScope (aTopScope, -1);        // The remaining 60% of TopScope for meshing

            ModelAlgo_BRepMesher aMesher;
            aMesher.ProgressStatus() = aStatus;                     // Connect progress status object
            aMesher.Compute (aModel);
        }
    }

    //notify the dialog box about completion
    QCoreApplication::postEvent (theOwner, new QEvent (static_cast<QEvent::Type> (CompletedId)));
}

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    QApplication anApp (argc, argv);
    ImportDialog aDialog;
    return aDialog.exec();

    return 0;
}
