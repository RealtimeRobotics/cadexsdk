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


#define __CADEX_PREVIEW_PMI 1

#include "PMIViewerApplication.hxx"

#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_Color.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_PMIData.hxx>
#include <cadex/ModelData_PMIGraphicalElement.hxx>
#include <cadex/ModelData_PMITable.hxx>
#include <cadex/ModelPrs_SceneNodeFactory.hxx>

#include <deque>
#include <iostream>

using namespace cadex;

namespace {

class ModelVisitor : public ModelData_Model::CombinedElementVisitor
{
public:
    ModelVisitor (const ModelPrs_SceneNode& theRoot, const ModelPrs_SceneNodeFactory& theFactory) :
        myFactory (theFactory)
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
        anSGENode.SetAppearance (theSGE.Appearance());

        if (theSGE.IsOfType<ModelData_Instance>()) {
            const auto& anInstance = static_cast<const ModelData_Instance&> (theSGE);
            anSGENode.SetTransformation (anInstance.Transformation());
        }

        myNodes.back().AddChildNode (anSGENode);
        myNodes.push_back (anSGENode);
        AddPMINodes (theSGE);

        return true;
    }

    void operator() (const ModelData_Part& thePart) override
    {
        auto aPartNode = myFactory.Create (thePart);
        aPartNode.SetAppearance (thePart.Appearance());
        myNodes.back().AddChildNode (aPartNode);
        AddPMINodes (thePart);
    }

    void AddPMINodes (const ModelData_SceneGraphElement& theSGE)
    {
        ModelData_Appearance anAppearance (ModelData_Color (0.0f, 0.0f, 0.0f, 1.0f));

        ModelPrs_SceneNode aPMIRootNode;
        aPMIRootNode.SetAppearance (anAppearance);

        for (ModelData_PMITable::PMIDataIterator anIt (theSGE.PMI()); anIt.HasNext();) {
            auto anElement = anIt.Next();
            if (anElement) {
                auto aPMINode = myFactory.Create (anElement.GraphicalElement());
                aPMIRootNode.AddChildNode (aPMINode);
            }
        }

        myNodes.back().AddChildNode (aPMIRootNode);
    }

private:
    std::deque<ModelPrs_SceneNode>    myNodes;
    ModelPrs_SceneNodeFactory         myFactory;
};

}


PMIViewerApplication::PMIViewerApplication()
{
    myReaderParameters.ReadPMI() = true;
}

void PMIViewerApplication::CreateSceneNodes()
{
    ModelPrs_SceneNodeFactory aFactory (myFactoryParameters);
    ModelVisitor aVisitor (myRoot, aFactory);
    myModel.Accept (aVisitor);
}
