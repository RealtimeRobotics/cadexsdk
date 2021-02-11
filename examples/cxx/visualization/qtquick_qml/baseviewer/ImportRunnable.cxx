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


#include "ImportRunnable.hxx"
#include "CustomEvents.hxx"

#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelPrs_Scene.hxx>
#include <cadex/ModelPrs_SceneNode.hxx>
#include <cadex/ModelPrs_SceneNodeFactory.hxx>
#include <cadex/ModelPrs_SceneNodeFactoryParameters.hxx>
#include <cadex/STEP_Reader.hxx>

#include <QtCore/QCoreApplication>
#include <QtCore/QFileInfo>

using namespace cadex;

ImportRunnable::ImportRunnable (const QString&                theFilename,
                                ModelPrs_Scene&               theScene,
                                ModelData_Model&              theModel,
                                cadex::STEP_ReaderParameters& theParameters,
                                BaseViewerApplication*        theParent) :
    myFilename (theFilename),
    myModel (theModel),
    myScene (theScene),
    myParameters (theParameters),
    myParent (theParent)
{

}

void ImportRunnable::Read()
{
    STEP_Reader aReader;
    aReader.Parameters() = myParameters;
    if (!aReader.ReadFile (myFilename.toStdString().data()) || !aReader.Transfer (myModel)) {
        QCoreApplication::postEvent (myParent, new ErrorEvent ("Failed to read the file " + myFilename));
        return;
    }
}

void ImportRunnable::DisplayModel()
{
    myParent->CreateSceneNodes();

    myScene.Update();
    myScene.Wait();
}

void ImportRunnable::run()
{
    Read();
    DisplayModel();

    QCoreApplication::postEvent (myParent, new QEvent (static_cast<QEvent::Type> (ImportResult::Success)));
}
