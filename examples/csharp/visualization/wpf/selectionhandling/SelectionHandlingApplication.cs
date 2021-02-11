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
using System.Windows;
using System.Windows.Controls;

namespace selectionhandling
{
    class ModelVisitor : ModelData_Model.CombinedElementVisitor
    {
        public ModelVisitor(ModelPrs_SceneNode theRoot,
                             ModelPrs_SceneNodeFactory theFactory,
                             ref Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement> theUserData)
        {
            myFactory = theFactory;
            myUserData = theUserData;
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

            return true;
        }

        public override void Apply(ModelData_Part thePart)
        {
            var aPartNode = myFactory.Create(thePart);
            myUserData[aPartNode] = thePart;
            myNodes.Peek().AddChildNode(aPartNode);
        }

        private Stack<ModelPrs_SceneNode> myNodes = new Stack<ModelPrs_SceneNode>();
        private ModelPrs_SceneNodeFactory myFactory = new ModelPrs_SceneNodeFactory();
        private readonly Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement> myUserData;
    };


    public class SelectionVisitor : ModelPrs_SelectionVisitor
    {
        public SelectionVisitor(Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement> theUserData)
        {
            myUserData   = theUserData;
        }

        public override void Visit(ModelPrs_SceneNode theNode)
        {
            var anSGE = myUserData[theNode.Parent()];
            if (anSGE != null)
            {
                System.Console.WriteLine("Part: " + anSGE.Name());
            }
        }

        public override void Visit(ModelPrs_SceneNode theNode, ModelData_ShapeList theShapes)
        {
            var anSGE = myUserData[theNode.Parent()];
            if (anSGE != null)
            {
                System.Console.WriteLine(theShapes.Count + " subshapes of part: " + anSGE.Name());
            }
        }

        private readonly Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement> myUserData;
    };


    public class SelectionChangesObserver : ModelPrs_SelectionChangesObserver
    {
        public SelectionChangesObserver(Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement> theUserData)
        {
            myUserData = theUserData;
        }

        public override void SelectionChangedByScene(ModelPrs_Selection theCurrent,
                                                     ModelPrs_Selection theSelected,
                                                     ModelPrs_Selection theDeselected)
        {
            System.Console.WriteLine("====================");

            if (theSelected != null)
            {
                System.Console.WriteLine("Next items have been selected:");
                SelectionVisitor aVisitor1 = new SelectionVisitor(myUserData);
                theSelected.Accept(aVisitor1);
            }

            if (theDeselected != null)
            {
                System.Console.WriteLine("Next items have been deselected:");
                SelectionVisitor aVisitor2 = new SelectionVisitor(myUserData);
                theDeselected.Accept(aVisitor2);
            }
        }

        public override void SelectionChangedByManager(ModelPrs_Selection theCurrent,
                                                       ModelPrs_Selection theSelected,
                                                       ModelPrs_Selection theDeselected)
        {}

        readonly Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement> myUserData;
    }

    public class Base_PublicObjectComparer<T> : IEqualityComparer<T> where T : Base_PublicObject
    {
        public bool Equals(T x, T y)
        {
            return x.IsEqual(y);
        }

        public int GetHashCode(T obj)
        {
            var aHash = new Base_PublicObjectHash();
            return (int)aHash.Apply(obj);
        }
    }

    public class SelectionHandlingApplication : baseviewer.BaseViewerApplication
    {
        public SelectionHandlingApplication(BaseViewer theViewer) : base(theViewer)
        {
            AddSelectionModeMenu();
            SetSelectionModeMenuItemChechecked("None", true);
            AddSelectionFilterMenu();
            SetSelectionFilterMenuItemChechecked("None", true);

            mySelectionObserver = new SelectionChangesObserver (myUserData);
            myScene.SelectionManager().Register (mySelectionObserver);

            myViewer.Viewport.HighlightEnabled = true;
        }

        void AddSelectionModeMenu()
        {
            MenuItem aSelectionModesMenu = new MenuItem();
            aSelectionModesMenu.Header = "Selection mode";

            MenuItem aNoneSMItem = new MenuItem();
            aNoneSMItem.Header = "None";
            aNoneSMItem.IsCheckable = true;
            aNoneSMItem.Click += onSelectionModeChanged;

            MenuItem aNodeSMItem = new MenuItem();
            aNodeSMItem.Header = "Node";
            aNodeSMItem.IsCheckable = true;
            aNodeSMItem.Click += onSelectionModeChanged;

            MenuItem aFaceSMItem = new MenuItem();
            aFaceSMItem.Header = "Face";
            aFaceSMItem.IsCheckable = true;
            aFaceSMItem.Click += onSelectionModeChanged;

            MenuItem aEdgeSMItem = new MenuItem();
            aEdgeSMItem.Header = "Edge";
            aEdgeSMItem.IsCheckable = true;
            aEdgeSMItem.Click += onSelectionModeChanged;

            aSelectionModesMenu.Items.Add(aNoneSMItem);
            aSelectionModesMenu.Items.Add(aNodeSMItem);
            aSelectionModesMenu.Items.Add(aFaceSMItem);
            aSelectionModesMenu.Items.Add(aEdgeSMItem);

            myViewer.myMenu.Items.Add(aSelectionModesMenu);
        }

        void AddSelectionFilterMenu()
        {
            MenuItem aSelectionFiltersMenu = new MenuItem();
            aSelectionFiltersMenu.Header = "Selection filters";

            MenuItem aNoneSFItem = new MenuItem();
            aNoneSFItem.Header = "None";
            aNoneSFItem.IsCheckable = true;
            aNoneSFItem.Click += onSelectionFilterTypeChanged;

            MenuItem aCircleEdgesSFItem = new MenuItem();
            aCircleEdgesSFItem.Header = "Circle edges only";
            aCircleEdgesSFItem.IsCheckable = true;
            aCircleEdgesSFItem.Click += onSelectionFilterTypeChanged;

            MenuItem aPlanarFacesSFItem = new MenuItem();
            aPlanarFacesSFItem.Header = "Planar faces only";
            aPlanarFacesSFItem.IsCheckable = true;
            aPlanarFacesSFItem.Click += onSelectionFilterTypeChanged;

            MenuItem aRevolFacesSFItem = new MenuItem();
            aRevolFacesSFItem.Header = "Revolution faces only";
            aRevolFacesSFItem.IsCheckable = true;
            aRevolFacesSFItem.Click += onSelectionFilterTypeChanged;

            aSelectionFiltersMenu.Items.Add(aNoneSFItem);
            aSelectionFiltersMenu.Items.Add(aCircleEdgesSFItem);
            aSelectionFiltersMenu.Items.Add(aPlanarFacesSFItem);
            aSelectionFiltersMenu.Items.Add(aRevolFacesSFItem);

            myViewer.myMenu.Items.Add(aSelectionFiltersMenu);
        }

        static MenuItem GetMenuItem(MenuItem theParent, string theMenuItemName)
        {
            foreach (var anItem in theParent.Items)
            {
                var aMenuItem = (MenuItem)anItem;
                var anItemName = (string)aMenuItem.Header;
                if (anItemName == theMenuItemName)
                {
                    return aMenuItem;
                }
            }
            return null;
        }

        static ModelPrs_SelectionMode ConvertToSelectionMode(string theMenuItemName)
        {
            if (theMenuItemName == "Node")
            {
                return ModelPrs_SelectionMode.ModelPrs_SM_Node;
            }
            if (theMenuItemName == "Face")
            {
                return ModelPrs_SelectionMode.ModelPrs_SM_Face;
            }
            if (theMenuItemName == "Edge")
            {
                return ModelPrs_SelectionMode.ModelPrs_SM_Edge;
            }
            return ModelPrs_SelectionMode.ModelPrs_SM_None;
        }

        void SetSelectionModeMenuItemChechecked(string theMenuItemName, bool theChecked)
        {
            var aSelectionModeMenu = (MenuItem)myViewer.myMenu.Items[1];
            foreach (var anItem in aSelectionModeMenu.Items)
            {
                var aMenuItem = (MenuItem)anItem;
                var anItemName = (string)aMenuItem.Header;
                if (anItemName == theMenuItemName)
                {
                    aMenuItem.IsChecked = theChecked;
                }
            }
            updateteMask(ref mySelectionModeMask, (int)ConvertToSelectionMode(theMenuItemName), theChecked);
        }

        void onSelectionModeChanged(object sender, RoutedEventArgs e)
        {
            var aMenuItem = (MenuItem)sender;
            var anItemName = (string)aMenuItem.Header;

            SetSelectionModeMenuItemChechecked(anItemName, aMenuItem.IsChecked);

            if (anItemName == "Node")
            {
                SetSelectionModeMenuItemChechecked("Face", false);
                SetSelectionModeMenuItemChechecked("Edge", false);
            }
            if (anItemName == "Face")
            {
                SetSelectionModeMenuItemChechecked("Node", false);
            }
            if (anItemName == "Edge")
            {
                SetSelectionModeMenuItemChechecked("Node", false);
            }

            bool aNoneSM = mySelectionModeMask == (int)ModelPrs_SelectionMode.ModelPrs_SM_None;

            if (aNoneSM)
            {
                SetSelectionModeMenuItemChechecked("Node", false);
                SetSelectionModeMenuItemChechecked("Face", false);
                SetSelectionModeMenuItemChechecked("Edge", false);
            }

            SetSelectionModeMenuItemChechecked("None", aNoneSM);

            myRoot.SetSelectionMode((ModelPrs_SelectionMode)mySelectionModeMask);
            myScene.Update();
        }

        static ModelPrs_SelectionFilterType ConvertToSelectionFilterType(string theMenuItemName)
        {
            if (theMenuItemName == "Circle edges only")
            {
                return ModelPrs_SelectionFilterType.ModelPrs_SFT_CircleEdgeFilter;
            }
            if (theMenuItemName == "Planar faces only")
            {
                return ModelPrs_SelectionFilterType.ModelPrs_SFT_PlanarFaceFilter;
            }
            if (theMenuItemName == "Revolution faces only")
            {
                return ModelPrs_SelectionFilterType.ModelPrs_SFT_RevolFaceFilter;
            }
            return ModelPrs_SelectionFilterType.ModelPrs_SFT_None;
        }

        void SetSelectionFilterMenuItemChechecked(string theMenuItemName, bool theChecked)
        {
            var aSelectionFilterMenu = (MenuItem)myViewer.myMenu.Items[2];
            foreach (var anItem in aSelectionFilterMenu.Items)
            {
                var aMenuItem = (MenuItem)anItem;
                var anItemName = (string)aMenuItem.Header;
                if (anItemName == theMenuItemName)
                {
                    aMenuItem.IsChecked = theChecked;
                }
            }
            updateteMask(ref mySelectionFilterMask, (int)ConvertToSelectionFilterType(theMenuItemName), theChecked);
        }

        void onSelectionFilterTypeChanged(object sender, RoutedEventArgs e)
        {
            var aMenuItem = (MenuItem)sender;
            var anItemName = (string)aMenuItem.Header;

            SetSelectionFilterMenuItemChechecked(anItemName, aMenuItem.IsChecked);

            bool aNoneSF = mySelectionFilterMask == (int)ModelPrs_SelectionFilterType.ModelPrs_SFT_None;

            if (aNoneSF)
            {
                SetSelectionFilterMenuItemChechecked("Circle edges only", false);
                SetSelectionFilterMenuItemChechecked("Planar faces only", false);
                SetSelectionFilterMenuItemChechecked("Revolution faces only", false);
            }

            SetSelectionFilterMenuItemChechecked("None", aNoneSF);

            myScene.SelectionManager().SetFilter((ModelPrs_SelectionFilterType)mySelectionFilterMask);
            myScene.Update();
        }

        protected override void CreateSceneNodes()
        {
            var aFactory = new ModelPrs_SceneNodeFactory(myFactoryParameters);
            var aVisitor = new ModelVisitor(myRoot, aFactory, ref myUserData);
            myModel.Accept(aVisitor);
        }

        void updateteMask(ref int theMask, int theValue, bool theChecked)
        {
            if (theChecked && theValue == 0)
            {
                theMask = theValue;
            }
            else
            {
                theMask = theChecked ? theMask | theValue : theMask & ~theValue;
            }
        }

        int mySelectionModeMask = 0;
        int mySelectionFilterMask = 0;
        Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement> myUserData = new Dictionary<ModelPrs_SceneNode, ModelData_SceneGraphElement>(new Base_PublicObjectComparer<ModelPrs_SceneNode>());
        readonly SelectionChangesObserver mySelectionObserver;
    }
}
