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

using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEditor;
using cadex;

public class ModelLoaderWizard : EditorWindow
{
    string myPath = "";
    Shader myCustomShader = null;
    bool   myImportPMI = false;
    float  myScaleFactor = 1f;

    ModelData_Model myModel;

    [MenuItem ("CAD Exchanger/Import CAD file", false, 100)]
    public static void ShowWindow() 
    {
        GetWindow(typeof(ModelLoaderWizard));
    }

    private void OnGUI() {
        myPath = EditorGUILayout.TextField("File Path: ", myPath);
        if (GUILayout.Button("Browse")) 
        {
            myPath = EditorUtility.OpenFilePanelWithFilters("Open Model", "", new string[] {
                "All supported types", "3ds,sat,sab,brep,xml,cdx,dae,prt.*,asm.*,dxf,fbx,fbx,ifc,igs,iges,jt,prt,obj,x_t,x_b,xmt_txt,xmp_bin,xmp_txt,xmp_bin,3dm,sldprt,sldasm,stp,step,stl,wrl,x3d,3mf,CATPart,CARProduct,dwg,u3d",
                "3DS files", "3ds",
                "3MF files", "3mf",
                "ACIS files", "sat,sab",
                "Brep files", "brep",
                "CAD Exchanger native files", "xml,cdx",
                "CAT files", "CATPart,CATProduct",
                "Collada files", "dae",
                "Creo files", "prt.*,asm.*",
                "DWG files", "dwg",
                "DXF files", "dxf",
                "FBX files", "fbx",
                "IFC files", "ifc",
                "IGES files", "igs,iges",
                "JT files", "jt",
                "NX files", "prt",
                "OBJ files", "obj",
                "Parasolid files", "x_t,x_b,xmt_txt,xmt_bin,xmp_txt,xmp_bin",
                "Rhino files", "3dm",
                "STEP files", "stp,step",
                "STL files", "stl",
                "SolidWorks files", "sldprt,sldasm",
                "U3D files", "u3d",
                "VRML files", "wrl",
                "X3D files", "x3d"
            });
        }
        myScaleFactor  = EditorGUILayout.FloatField("Scale Factor: ", myScaleFactor);
        myImportPMI    = EditorGUILayout.Toggle("Import PMI: ", myImportPMI);
        myCustomShader = EditorGUILayout.ObjectField("Custom Shader", myCustomShader, typeof(Shader), true) as Shader;
        if (GUILayout.Button("Import")) 
        {
            LoadModel();
        }
    }

    private void LoadModel() 
    {
        string aKey = LicenseKey.Value();
        // Activate the license (aKey must be defined in cadex_license.cs)
        if (!LicenseManager.Activate(aKey)) 
        {
            Debug.LogError("Failed to activate CAD Exchanger license.");
        }

        ModelData_Model aModel;
        aModel = ModelImporter.ImportModel(myPath, myImportPMI);
        Unity_ObjectFactory aFactory = new Unity_ObjectFactory();
        aFactory.Parameters().SetImportPMI(myImportPMI);
        if (myCustomShader) 
        {
            aFactory.Parameters().SetShader(myCustomShader);
        }
        aFactory.Parameters().SetScaleFactor(myScaleFactor);
        string aModelName = Path.GetFileName(myPath);
        aFactory.Create(aModel, aModelName);
    }
}
