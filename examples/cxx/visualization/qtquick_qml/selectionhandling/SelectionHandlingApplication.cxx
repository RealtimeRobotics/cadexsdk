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


#include "SelectionHandlingApplication.hxx"

#include <cadex/Base_String.hxx>
#include <cadex/Base_UTF16String.hxx>
#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_Transformation.hxx>
#include <cadex/ModelPrs_Geometry.hxx>
#include <cadex/ModelPrs_SceneNode.hxx>
#include <cadex/ModelPrs_SceneNodeFactory.hxx>
#include <cadex/ModelPrs_Selection.hxx>
#include <cadex/ModelPrs_SelectionManager.hxx>
#include <cadex/ModelPrs_SelectionVisitor.hxx>

#include <QtCore/QDebug>
#include <QtQuick/QQuickWindow>

#include <memory>
#include <deque>

using namespace cadex;

namespace {

class SceneNodeSGEData : public cadex::ModelPrs_SceneNode::Data
{
public:
    SceneNodeSGEData (const cadex::ModelData_SceneGraphElement& theSGE);

    cadex::ModelData_SceneGraphElement mySGE;
};

template<typename T>
cadex::ModelPrs_SceneNode FindAncestorWithSGE (const cadex::ModelPrs_SceneNode& theNode)
{
    for (auto aParent = theNode.Parent(); aParent; aParent = aParent.Parent()) {
        auto anSGEData = std::static_pointer_cast<SceneNodeSGEData> (aParent.UserData());
        if (anSGEData && anSGEData->mySGE.IsOfType<T>()) {
            return aParent;
        }
    }

    return cadex::ModelPrs_SceneNode();
}

class ModelVisitor : public ModelData_Model::CombinedElementVisitor
{
public:
    ModelVisitor (const ModelPrs_SceneNode& theRoot, const ModelPrs_SceneNodeFactory& theFactory)
        : myFactory (theFactory)
    {
        myNodes.push_back (theRoot);
    }

    void VisitLeave (const ModelData_SceneGraphElement& /*theSGE*/) override
    {
        myNodes.pop_back();
    }

    bool VisitEnter (const ModelData_SceneGraphElement& theSGE) override
    {
        ModelPrs_SceneNode anSGENode;
        anSGENode.SetUserData (std::make_shared<SceneNodeSGEData> (theSGE));
        anSGENode.SetAppearance (theSGE.Appearance());

        if (theSGE.IsOfType<ModelData_Instance>()) {
            const auto& anInstance = static_cast<const ModelData_Instance&> (theSGE);
            anSGENode.SetTransformation (anInstance.Transformation());
        }

        myNodes.back().AddChildNode (anSGENode);
        myNodes.push_back (anSGENode);

        return true;
    }

    void operator() (const ModelData_Part& thePart) override
    {
        auto aPartNode = myFactory.Create (thePart);
        aPartNode.SetAppearance (thePart.Appearance());
        aPartNode.SetUserData (std::make_shared<SceneNodeSGEData> (thePart));
        myNodes.back().AddChildNode (aPartNode);
    }

private:
    std::deque<ModelPrs_SceneNode>    myNodes;
    ModelPrs_SceneNodeFactory         myFactory;
};

class SelectionVisitor : public ModelPrs_SelectionVisitor
{
public:
    Base_UTF16String PartOrInstanceName (const ModelPrs_SceneNode& theNode)
    {
        Base_UTF16String aName;

        auto aPartAncestor = FindAncestorWithSGE<ModelData_Part> (theNode);
        if (aPartAncestor) {
            auto anInstanceAncestor = FindAncestorWithSGE<ModelData_Instance> (theNode);
            if (anInstanceAncestor) {
                aName = GetSGEName (anInstanceAncestor);
            }

            if (aName.IsEmpty()) {
                aName = GetSGEName (aPartAncestor);
            }
        }

        return aName;
    }

    Base_UTF16String GetSGEName (const ModelPrs_SceneNode& theNode)
    {
        auto anSGEData = std::static_pointer_cast<SceneNodeSGEData> (theNode.UserData());
        if (anSGEData) {
            return anSGEData->mySGE.Name();
        }
        return Base_UTF16String();
    }

    void Visit (const ModelPrs_SceneNode& theNode) override
    {
        auto aName = PartOrInstanceName (theNode).ToUTF8().Data();
        qDebug() << "Part: " << aName;
    }

    void Visit (const ModelPrs_SceneNode& theNode, const std::vector<ModelData_Shape>& theShapes) override
    {
        auto aName = PartOrInstanceName (theNode).ToUTF8().Data();
        qDebug() << theShapes.size() << " shapes of part: " << aName;
    }
};

} // end of unnamed namespace


SceneNodeSGEData::SceneNodeSGEData (const ModelData_SceneGraphElement& theSGE)
    : mySGE (theSGE)
{

}

void SelectionChangesObserver::SelectionChangedByScene (const cadex::ModelPrs_Selection& /*theCurrent*/,
                                                        const cadex::ModelPrs_Selection& theSelected,
                                                        const cadex::ModelPrs_Selection& theDeselected)
{
    qDebug() << "====================";

    if (theSelected) {
        qDebug() << "Next items have been selected:";
        SelectionVisitor aVisitor1;
        theSelected.Accept (aVisitor1);
    }

    if (theDeselected) {
        qDebug() << "Next items have been deselected:";
        SelectionVisitor aVisitor2;
        theDeselected.Accept (aVisitor2);
    }
}

SelectionHandlingApplication::SelectionHandlingApplication()
{
    myScene.SelectionManager().Register (mySelectionObserver);

    connect (this, &BaseViewerApplication::initialized, this, &SelectionHandlingApplication::onInitialized);
}

void SelectionHandlingApplication::CreateSceneNodes()
{
    ModelPrs_SceneNodeFactory aFactory (myFactoryParameters);
    ModelVisitor aVisitor (myRoot, aFactory);
    myModel.Accept (aVisitor);
}

void SelectionHandlingApplication::onSelectionModeChanged (const QVariant& theMode)
{
    auto aMode = theMode.toInt();
    auto aSelectionMode = static_cast<ModelPrs_SelectionMode> (aMode);
    myRoot.SetSelectionMode (aSelectionMode);
    myScene.Update();
}

void SelectionHandlingApplication::onSelectionFilterChanged (const QVariant& theFilter)
{
    auto aFilter = theFilter.toInt();
    auto aSelectionFilter = static_cast<ModelPrs_SelectionFilterType> (aFilter);
    myScene.SelectionManager().SetFilter (aSelectionFilter);
    myScene.Update();
}

void SelectionHandlingApplication::onInitialized()
{
    connect (myMainWindow, SIGNAL (selectionModeChanged (const QVariant&)),
             this,         SLOT (onSelectionModeChanged (const QVariant&)));

    connect (myMainWindow, SIGNAL (selectionFilterChanged (const QVariant&)),
             this,         SLOT (onSelectionFilterChanged (const QVariant&)));
}
