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


#include "ManipulatorApplication.hxx"

#include <cadex/ModelPrsQtQuick_ViewPort.hxx>
#include <cadex/ModelPrs_Manipulator.hxx>
#include <cadex/ModelPrs_SceneNode.hxx>
#include <cadex/ModelPrs_Selection.hxx>
#include <cadex/ModelPrs_SelectionVisitor.hxx>
#include <cadex/ModelPrs_SelectionManager.hxx>

#include <QtQuick/QQuickWindow>

using namespace cadex;

namespace {

class SelectionVisitor : public ModelPrs_SelectionVisitor
{
public:
    void Visit (const ModelPrs_SceneNode& theNode) override
    {
        mySceneNode = theNode;
    }

    void Visit (const ModelPrs_SceneNode& /*theNode*/, const std::vector<ModelData_Shape>& /*theShapes*/) override
    {

    }

    ModelPrs_SceneNode mySceneNode;
};

} // end of unnamed namespace


SelectionChangesObserver::SelectionChangesObserver (ManipulatorApplication& theApplication)
    : myApplication (theApplication)
{

}

void SelectionChangesObserver::SelectionChangedByScene (const cadex::ModelPrs_Selection& theCurrent,
                                                        const cadex::ModelPrs_Selection& /*theSelected*/,
                                                        const cadex::ModelPrs_Selection& /*theDeselected*/)
{
    if (theCurrent.IsNull()) {
        mySceneNode.Nullify();
    } else {
        SelectionVisitor aVisitor;
        theCurrent.Accept (aVisitor);

        mySceneNode = aVisitor.mySceneNode;
    }

    myApplication.OnSelectionChanged (mySceneNode);
}


ManipulatorObserver::ManipulatorObserver (ManipulatorApplication& theApplication)
    : myApplication (theApplication)
{

}

void ManipulatorObserver::StartTransformation()
{
    myApplication.OnTransformationActiveChanged (true);
    myApplication.OnTransformationChanged (0.);
}

void ManipulatorObserver::ModeChanged (ModelPrs_ManipulatorMode theMode, const ModelData_Direction& /*theDirection*/)
{
    myApplication.OnTransformationModeChanged (theMode);
}

void ManipulatorObserver::StopTransformation()
{
    myApplication.OnTransformationActiveChanged (false);
}

void ManipulatorObserver::Transformed (const ModelData_Transformation& /*theLocalTrsf*/,
                                       const ModelData_Transformation& /*theGlobalTrsf*/,
                                       double theValue)
{
    myApplication.OnTransformationChanged (theValue);
}


ManipulatorApplication::ManipulatorApplication()
    : myManipulatorObserver (*this),
      mySelectionObserver (*this)

{
    myScene.SelectionManager().Register (mySelectionObserver);

    myRoot.SetSelectionMode (ModelPrs_SM_Node);

    connect (this, &BaseViewerApplication::initialized, this, &ManipulatorApplication::onInitialized);
}

void ManipulatorApplication::OnSelectionChanged (const ModelPrs_SceneNode& theNode)
{
    if (theNode) {
        myViewPort->Manipulator().AttachTo (theNode);
    } else {
        myViewPort->Manipulator().Detach();
    }
    OnAttachedChanged (!theNode.IsNull());
}

void ManipulatorApplication::onResetTransformation()
{
    myViewPort->Manipulator().ResetTransformation();
}

void ManipulatorApplication::onInitialized()
{
    connect (myMainWindow, SIGNAL (resetTransformation()),
             this,         SLOT (onResetTransformation()));

    myViewPort->Manipulator().Register (myManipulatorObserver);
}

void ManipulatorApplication::OnTransformationModeChanged (cadex::ModelPrs_ManipulatorMode theMode)
{
    if (theMode != ModelPrs_MM_None) {
        myMainWindow->setProperty ("transformationType",  theMode);
    }
}

void ManipulatorApplication::OnTransformationChanged (double theValue)
{
    myMainWindow->setProperty ("transformationValue", theValue);
}

void ManipulatorApplication::OnTransformationActiveChanged (bool theValue)
{
    myMainWindow->setProperty ("transformationActive", theValue);
}

void ManipulatorApplication::OnAttachedChanged (bool theValue)
{
    myMainWindow->setProperty ("isAttached", theValue);
    if (!theValue) {
        myMainWindow->setProperty ("transformationType",  ModelPrs_MM_None);
    }
}

void ManipulatorApplication::Clear()
{
    myViewPort->Manipulator().Detach();
    OnAttachedChanged (false);
    OnTransformationActiveChanged (false);
    BaseViewerApplication::Clear();
}
