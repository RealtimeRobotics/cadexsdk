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


#include "BaseViewerApplication.hxx"
#include "ImportRunnable.hxx"
#include "CustomEvents.hxx"

#include <cadex/ModelPrs_Scene.hxx>
#include <cadex/ModelPrs_SceneNodeFactory.hxx>
#include <cadex/ModelPrsQtQuick_ViewPort.hxx>

#include <QtCore/QThreadPool>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>

using namespace cadex;

#if __ANDROID__
#include <QtAndroidExtras/QtAndroid>
#endif

#if __ANDROID__ && __ANDROID_DEBUG
#include <android/log.h>

namespace {
static void QMessageToAndroidLogRedirector (QtMsgType theType, const QMessageLogContext& /*theContext*/, const QString& theMsg)
{
    QString aText;
    switch (theType) {
    case QtDebugMsg:    aText += "qDebug(): "; break;
    case QtWarningMsg:  aText += "qWarning(): "; break;
    case QtCriticalMsg: aText += "qCritical(): "; break;
    case QtFatalMsg:    aText += "qFatal(): "; break;
    case QtInfoMsg:     aText += "qInfo(): "; break;
    default: break;
    }
    aText += theMsg;
    for (const QString& line : aText.split ('\n')) {
        __android_log_print (ANDROID_LOG_DEBUG, "baseviewer", "%s", qPrintable (line));
    }
}
}
#endif

BaseViewerApplication::BaseViewerApplication()
    : myRoot (ModelPrs_SceneNode::initialized())
{
    myScene.AddRoot (myRoot);
}

bool BaseViewerApplication::Initialize (const QUrl& theUrl, const QString& theViewPortName)
{
#if __ANDROID__ && __ANDROID_DEBUG
    // Redirecting qDebug(), qWarning(), qCritical() to android log
    qInstallMessageHandler (QMessageToAndroidLogRedirector);
#endif

    // register ModelPrsQtQuick_ViewPort package and ModelPrsQtQuick_ViewPort qml type.
    ModelPrsQtQuick_ViewPort::RegisterQtTypes();

    myMainWindow = CreateMainWindow (theUrl);

    Q_ASSERT (myMainWindow);

#if __ANDROID__
    if (!QtAndroid::shouldShowRequestPermissionRationale("android.permission.READ_EXTERNAL_STORAGE")) {
        QtAndroid::requestPermissions({{ "android.permission.READ_EXTERNAL_STORAGE" }},
        [] (const QtAndroid::PermissionResultMap & theResult) {
            if (theResult["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied) {
                qWarning ("User refused request to allow access to sdcard for reading.");
            }
        });
    }
#endif

    connect (myMainWindow, SIGNAL (importFile (const QVariant&)),
             this,         SLOT (onImportFile (const QVariant&)));

    myViewPort = myMainWindow->findChild<ModelPrsQtQuick_ViewPort*> (theViewPortName);
    Q_ASSERT (myViewPort);
    auto aRes = myViewPort->AttachToScene (myScene);

    myMainWindow->showNormal();

    emit initialized();

    return aRes;
}

//! Creates Qml Engine and create application window from qml.
QQuickWindow* BaseViewerApplication::CreateMainWindow (const QUrl& theUrl)
{
    auto anEngine = new QQmlApplicationEngine (this);

    QQmlComponent aComponent (anEngine);
    aComponent.loadUrl (theUrl);

    QObject* aQmlApp = nullptr;

    if (!aComponent.isReady()) {
        // For easy debugging redirect it to output.
        qDebug() << aComponent.errorString();
        QCoreApplication::postEvent (QCoreApplication::instance(), new QEvent (QEvent::Quit));
        return nullptr;
    }

    aQmlApp = aComponent.create();
    aQmlApp->setParent (this);
    return qobject_cast<QQuickWindow*> (aQmlApp);
}

void BaseViewerApplication::onImportFile (const QVariant& theUrl)
{
    if (!(theUrl.isValid() || !theUrl.canConvert<QUrl>())) {
        qWarning() << "BaseViewerApplication::OnImport: Invalid argument [" << theUrl << "]";
        return;
    }

    auto aFilename = theUrl.toUrl().toLocalFile();
    Import (aFilename);
}

void BaseViewerApplication::Import (const QString& theFilename)
{
    Clear();

    auto aRunnable = new ImportRunnable (theFilename, myScene, myModel, myReaderParameters, this);
    QThreadPool::globalInstance()->start (aRunnable);

    myMainWindow->setProperty ("loading", true);
    myMainWindow->setTitle (QString ("CAD Exchanger [%1]").arg (theFilename));
}

void BaseViewerApplication::Clear()
{
    myModel.Clear();
    myRoot.RemoveChildrenNodes();
    myScene.Update();
}

void BaseViewerApplication::CreateSceneNodes()
{
    ModelPrs_SceneNodeFactory aFactory (myFactoryParameters);
    auto aRoot = aFactory.Create (myModel);
    myRoot.AddChildNode (aRoot);
}

void BaseViewerApplication::onImportCompleted (QEvent* theEvent)
{
    auto anEventType = static_cast<ImportResult> (theEvent->type());

    switch (anEventType) {
    case ImportResult::Success: {
        myMainWindow->setProperty ("loading", false);
        myViewPort->animatedFitAll();
        break;
    }
    case ImportResult::Error: {
        Q_ASSERT (dynamic_cast<ErrorEvent*> (theEvent));
        auto anEvent = static_cast<ErrorEvent*> (theEvent);
        ShowMessageBox (anEvent->Message());
        break;
    }
    }
}

bool BaseViewerApplication::event (QEvent* theEvent)
{
    auto anEventType = static_cast<ImportResult> (theEvent->type());

    if (ImportResult::Error != anEventType && anEventType != ImportResult::Success) {
        return QObject::event (theEvent);
    }

    onImportCompleted (theEvent);
    return true;
}

void BaseViewerApplication::ShowMessageBox (const QString& theMessage)
{
    if (auto aDialog = myMainWindow->findChild<QObject*> ("dialog")) {
        aDialog->setProperty ("message", theMessage);
        QMetaObject::invokeMethod (aDialog, "open");
    }
}


