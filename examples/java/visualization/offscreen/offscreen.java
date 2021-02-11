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

import cadex.*;

public class offscreen {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExView");
            System.loadLibrary("CadExSTEP");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
        }
    }

    public static void main(String[] args) {
        String aKey = LicenseKey.Value();

        // Activate the license (aKey must be defined in LicenseKey.java)
        if (!LicenseManager.Activate(aKey)) {
            System.out.println("Failed to activate CAD Exchanger license.");
            System.exit(1);
        }

        if (args.length != 2) {
            System.out.println("Usage: " + " <input_file> <output_file>, where:");
            System.out.println("    <input_file>  is a name of the STEP file to be read");
            System.out.println("    <output_file> is a name of the PNG  file to be written");
            System.exit(1);
        }

        String aSource = args[0];
        String aDest = args[1];

        STEP_Reader aReader = new STEP_Reader();

        // Read the file
        if (!aReader.ReadFile(new Base_UTF16String(aSource))) {
            System.out.println("Failed to read the file " + aSource);
            System.exit(1);
        }

        ModelData_Model aModel = new ModelData_Model();

        // Make model data
        if (!aReader.Transfer(aModel)) {
            System.out.println("Failed to transfer the file into inner format.");
            System.exit(1);
        }

        // Use exceptions to get human-readable errors on fail
        Base_Settings.Default().SetValue (Base_Settings.Id.UseExceptions, true);

        try {

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
                System.out.println("Unable to attach viewport to scene");
                System.exit(1);
            }

            // Apply scene changes to viewport and wait until all async operations will be finished
            aScene.Update();
            aScene.Wait();

            // Fit and center model on the image
            aViewPort.FitAll();

            // Grab rendered frame into image
            if (!aViewPort.GrabToImage(new Base_UTF16String(aDest))) {
                System.out.println("Failed to write the file " + aDest);
                System.exit(1);
            }

        } catch(Base_Exception theErr) {
            System.out.println(theErr.What());
            System.exit(1);
        }
    }
}
