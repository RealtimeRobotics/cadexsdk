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


using cadex;
using System.ComponentModel;

namespace baseviewer
{
    public class BaseViewerApplication
    {
        public delegate void LoadingDelegate(bool theLoading);
        public delegate void ErrorMessageDelegate(string theMessage);

        public event LoadingDelegate LoadingChanged;
        public event ErrorMessageDelegate ErrorMessage;

        public BaseViewerApplication(BaseViewer theViewer)
        {
            myViewer = theViewer;

            myFactoryParameters = new ModelPrs_SceneNodeFactoryParameters(ModelData_RepresentationMask.ModelData_RM_BRep, false);
            myViewer.Viewport.AttachToScene(myScene);
            myScene.AddRoot(myRoot);

            myWorker.DoWork += OnDoWork;
            myWorker.RunWorkerCompleted += OnImportCompleted;
        }

        public bool IsBusy
        {
            get { return myWorker.IsBusy; }
        }

        public void Import(string theFilename)
        {
            if (IsBusy)
            {
                return;
            }

            Clear();
            myWorker.RunWorkerAsync(theFilename);

            LoadingChanged (true);
        }

        private void OnDoWork(object sender, DoWorkEventArgs e)
        {
            var aFilename = e.Argument as string;

            Read(aFilename);
            DisplayModel();

            e.Result = true;
        }

        private void Read(string theFilename)
        {
            STEP_Reader aReader = new STEP_Reader();
            aReader.SetParameters(myReaderParameters);
            if (!aReader.ReadFile(new Base_UTF16String(theFilename)) || !aReader.Transfer(myModel))
            {
                return;
            }
        }

        private void DisplayModel()
        {
            CreateSceneNodes();

            myScene.Update();
            myScene.Wait();
        }

        private void Clear()
        {
            myRoot.RemoveChildrenNodes();
            myScene.Update();
            myModel.Clear();
        }

        protected virtual void CreateSceneNodes()
        {
            ModelPrs_SceneNodeFactory aFactory = new ModelPrs_SceneNodeFactory(myFactoryParameters);
            var aRoot = aFactory.Create(myModel);
            myRoot.AddChildNode(aRoot);
        }

        private void OnImportCompleted(object theSender, RunWorkerCompletedEventArgs theEvent)
        {
            if (!theEvent.Cancelled && !(bool)theEvent.Result)
            {
                ErrorMessage(theEvent.Error.Message);
            }

            LoadingChanged(false);

            myViewer.Viewport.AnimatedFitAll();
        }

        protected ModelPrs_SceneNode myRoot = new ModelPrs_SceneNode();
        protected ModelData_Model myModel = new ModelData_Model();
        protected ModelPrs_Scene myScene = new ModelPrs_Scene();
        protected ModelPrs_SceneNodeFactoryParameters myFactoryParameters = new ModelPrs_SceneNodeFactoryParameters();
        protected STEP_ReaderParameters myReaderParameters = new STEP_ReaderParameters();
        protected BaseViewer myViewer;
        private BackgroundWorker myWorker = new BackgroundWorker();
    }
}
