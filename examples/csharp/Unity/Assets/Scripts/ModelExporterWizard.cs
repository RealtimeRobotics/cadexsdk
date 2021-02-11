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

public class ModelExporterWizard : EditorWindow 
{
    public enum ExportFormat { ACIS, BRep, XML, Collada, DXF, FBX, GLTF, IFC, IGES, JT, OBJ, Para, Rhino, STEP, STL, VRML, X3D };

    GameObject myGameObject = null;
    ExportFormat myExportFormat;
    string myFilePath = "";

    ModelData_Model myModel;

    [MenuItem("CAD Exchanger/Export to CAD file")]
    public static void ShowWindow() 
    {
        GetWindow(typeof(ModelExporterWizard));
    }

    private void OnGUI() 
    {
        myGameObject = EditorGUILayout.ObjectField("Game Object: ", myGameObject, typeof(GameObject), true) as GameObject;
        myExportFormat = (ExportFormat)EditorGUILayout.EnumPopup("Export Format: ", myExportFormat);
        if (GUILayout.Button("Export")) 
        {
            string anExtension = "xml";
            switch (myExportFormat) {
                case ExportFormat.ACIS: anExtension = "sat"; break;
                case ExportFormat.BRep: anExtension = "brep"; break;
                case ExportFormat.Collada: anExtension = "dae"; break;
                case ExportFormat.DXF: anExtension = "dxf"; break;
                case ExportFormat.FBX: anExtension = "fbx"; break;
                case ExportFormat.GLTF: anExtension = "gltf"; break;
                case ExportFormat.IFC: anExtension = "ifc"; break;
                case ExportFormat.IGES: anExtension = "igs"; break;
                case ExportFormat.JT: anExtension = "jt"; break;
                case ExportFormat.OBJ: anExtension = "obj"; break;
                case ExportFormat.Para: anExtension = "x_t"; break;
                case ExportFormat.Rhino: anExtension = "3dm"; break;
                case ExportFormat.STEP: anExtension = "stp"; break;
                case ExportFormat.STL: anExtension = "stl"; break;
                case ExportFormat.VRML: anExtension = "wrl"; break;
                case ExportFormat.X3D: anExtension = "x3d"; break;
            }
            myFilePath = EditorUtility.SaveFilePanel("Export", "", Path.GetFileNameWithoutExtension(myFilePath), anExtension);
            if (myFilePath != "" && myGameObject != null) 
            {
                ExportModel();
            }
        }
    }

    private void ExportModel() {
        string aKey = LicenseKey.Value();
        // Activate the license (aKey must be defined in cadex_license.cs)
        if (!LicenseManager.Activate(aKey)) 
        {
            Debug.LogError("Failed to activate CAD Exchanger license.");
        }

        Unity_ModelFactory aModelFactory = new Unity_ModelFactory();
        ModelData_Model aModel = aModelFactory.Create(myGameObject, myGameObject.name);

        string aFileName = Path.GetFileName(myFilePath);
        if (ModelExporter.ExportModel(aModel, myFilePath)) 
        {
            Debug.Log("Export to " + aFileName + " is completed!");
        }
        else 
        {
            Debug.LogError("An error occurred while exporting " + myGameObject.name + " to " + myExportFormat.ToString());
        }
    }
}
