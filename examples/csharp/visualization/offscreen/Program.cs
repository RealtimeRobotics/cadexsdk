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
using System;
using System.Runtime.InteropServices;

namespace offscreen
{
    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        static int Main(string[] args)
        {
            // Add runtime path to CAD Exchanger libraries (e.g. compiled with Visual Studio 2015)
            SetDllDirectory("../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                Console.WriteLine("Failed to activate CAD Exchanger license.");
                return 1;
            }

            if (args.Length != 2)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file> <output_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the STEP file to be read");
                Console.WriteLine("    <output_file> is a name of the PNG  file to be written");
                return 1;
            }

            string aSource = args[0];
            string aDest = args[1];

            STEP_Reader aReader = new STEP_Reader();

            // Read the file
            if (!aReader.ReadFile(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            ModelData_Model aModel = new ModelData_Model();

            // Converting into inner format
            if (!aReader.Transfer(aModel))
            {
                Console.WriteLine("Failed to transfer the file into inner format.");
                return 1;
            }

            // Setup parameters to display one of available representation
            ModelPrs_SceneNodeFactoryParameters aParameters = new ModelPrs_SceneNodeFactoryParameters(
                    ModelData_RepresentationMask.ModelData_RM_Any);

            // Convert model into visualisation entities
            ModelPrs_SceneNodeFactory aFactory = new ModelPrs_SceneNodeFactory(aParameters);
            ModelPrs_SceneNode aRootNode = aFactory.Create(aModel);
            aRootNode.SetDisplayMode(ModelPrs_DisplayMode.ModelPrs_DM_ShadedWithBoundaries);

            // Create scene and display all entities
            ModelPrs_Scene aScene = new ModelPrs_Scene();
            aScene.AddRoot(aRootNode);

            // Setup offscreen viewport with transparent background and perspective camera
            ModelPrs_OffscreenViewPort aViewPort = new ModelPrs_OffscreenViewPort();
            aViewPort.Resize(800, 600);
            aViewPort.SetCameraProjectionType(ModelPrs_CameraProjectionType.ModelPrs_CPT_Perspective);
            aViewPort.SetCameraPositionType(ModelPrs_CameraPositionType.ModelPrs_CMT_Default);
            ModelData_Color aBackgroundColor = new ModelData_Color(0x00000000);
            ModelPrs_BackgroundStyle aStyle = new ModelPrs_BackgroundStyle(aBackgroundColor);
            aViewPort.SetBackgroundStyle(aStyle);

            // Attach viewport to the scene.
            if (!aViewPort.AttachToScene(aScene)) {
                Console.WriteLine("Unable to attach viewport to scene");
                return 1;
            }

            // Apply scene changes to viewport and wait until all async operations will be finished
            aScene.Update();
            aScene.Wait();

            // Fit and center model on the image
            aViewPort.FitAll();

            // Grab rendered frame into image
            if (!aViewPort.GrabToImage(new Base_UTF16String(aDest))) {
                Console.WriteLine("Failed to write the file " + aDest);
                return 1;
            }

            return 0;
        }
    }
}
