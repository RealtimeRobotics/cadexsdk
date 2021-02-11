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


using baseviewer;
using cadex;
using System.Collections.Generic;

namespace pmiviewer
{
    class ModelVisitor : ModelData_Model.CombinedElementVisitor
    {
        public ModelVisitor(ModelPrs_SceneNode theRoot, ModelPrs_SceneNodeFactory theFactory)
        {
            myFactory = theFactory;
            myNodes.Push(theRoot);
        }

        public override void VisitLeave(ModelData_SceneGraphElement theSGE)
        {
            myNodes.Pop();
        }

        public override bool VisitEnter(ModelData_SceneGraphElement theSGE)
        {
            var anSGENode = new ModelPrs_SceneNode();
            anSGENode.SetAppearance(theSGE.Appearance());

            if (theSGE.TypeId() == ModelData_Instance.GetTypeId())
            {
                var anInstance = ModelData_Instance.Cast(theSGE);
                anSGENode.SetTransformation(anInstance.Transformation());
            }

            myNodes.Peek().AddChildNode(anSGENode);
            myNodes.Push(anSGENode);
            AddPMINodes(theSGE);

            return true;
        }

        public override void Apply(ModelData_Part thePart)
        {
            var aPartNode = myFactory.Create(thePart);
            myNodes.Peek().AddChildNode(aPartNode);
            AddPMINodes(thePart);
        }

        private void AddPMINodes(ModelData_SceneGraphElement theSGE)
        {
            ModelData_Appearance anAppearance = new ModelData_Appearance(new ModelData_Color(0.0f, 0.0f, 0.0f, 1.0f));

            ModelPrs_SceneNode aRootNode = new ModelPrs_SceneNode();
            aRootNode.SetAppearance(anAppearance);

            ModelData_PMITable.PMIDataIterator anIt = new ModelData_PMITable.PMIDataIterator(theSGE.PMI());
            while (anIt.HasNext())
            {
                var anElement = anIt.Next();
                if (anElement != null)
                {
                    var aPMINode = myFactory.Create(anElement.GraphicalElement());
                    aRootNode.AddChildNode(aPMINode);
                }
            }

            myNodes.Peek().AddChildNode(aRootNode);
        }

        private Stack<ModelPrs_SceneNode> myNodes = new Stack<ModelPrs_SceneNode>();
        private ModelPrs_SceneNodeFactory myFactory = new ModelPrs_SceneNodeFactory();
    };

    class PMIViewerApplication : BaseViewerApplication
    {
        public PMIViewerApplication(BaseViewer theViewer) : base(theViewer)
        {
            myReaderParameters.SetReadPMI(true);
        }

        protected override void CreateSceneNodes()
        {
            ModelPrs_SceneNodeFactory aFactory = new ModelPrs_SceneNodeFactory(myFactoryParameters);
            ModelVisitor aVisitor = new ModelVisitor(myRoot, aFactory);
            myModel.Accept(aVisitor);
        }
    }
}
