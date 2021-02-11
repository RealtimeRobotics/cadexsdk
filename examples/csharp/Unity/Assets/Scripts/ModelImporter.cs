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


using System.IO;
using System.Text.RegularExpressions;
using cadex;

public static class ModelImporter
{
    public static ModelData_Model ImportModel(string thePath, bool theImportPMI = false)
    {
        string aModelExpansion = Path.GetExtension(thePath).ToLower();
        Base_Reader aReader = null;
        ModelData_Model aLoadedModel = new ModelData_Model();

        if (Regex.Match(Path.GetFileName(thePath), "^.*\\.((asm)|(prt))\\.[0-9]+$").Success) // Creo format
        {
            aReader = CreateCreoReader(theImportPMI);
        }
        else 
        {
            switch (aModelExpansion) {
                case ".3ds": aReader = CreateA3DSReader(theImportPMI); break;
                case ".3mf": aReader = CreateX3MFReader(theImportPMI); break;
                case ".sat":
                case ".sab": aReader = CreateACISReader(theImportPMI); break;
                case ".brep": aReader = CreateBRepReader(theImportPMI); break;
                case ".catpart":
                case ".carproduct": aReader = CreateCATReader(theImportPMI); break;
                case ".dae": aReader = CreateColladaReader(theImportPMI); break;
                case ".dwg": aReader = CreateDWGReader(theImportPMI); break;
                case ".dxf": aReader = CreateDXFReader(theImportPMI); break;
                case ".fbx": aReader = CreateFBXReader(theImportPMI); break;
                case ".ifc": aReader = CreateIFCReader(theImportPMI); break;
                case ".igs":
                case ".iges": aReader = CreateIGESReader(theImportPMI); break;
                case ".jt": aReader = CreateJTReader(theImportPMI); break;
                case ".prt": aReader = CreateNXReader(theImportPMI); break;
                case ".obj": aReader = CreateOBJReader(theImportPMI); break;
                case ".x_t":
                case ".x_b":
                case ".xmt_txt":
                case ".xmt_bin":
                case ".xmp_txt":
                case ".xmp_bin": aReader = CreateParaReader(theImportPMI); break;
                case ".3dm": aReader = CreateRhinoReader(theImportPMI); break;
                case ".stp":
                case ".step": aReader = CreateSTEPReader(theImportPMI); break;
                case ".stl": aReader = CreateSTLReader(theImportPMI); break;
                case ".sldprt":
                case ".sldasm": aReader = CreateSLDReader(theImportPMI); break;
                case ".u3d": aReader = CreateU3DReader(theImportPMI); break;
                case ".wrl": aReader = CreateVRMLReader(theImportPMI); break;
                case ".x3d": aReader = CreateX3DReader(theImportPMI); break;
                case ".xml":
                case ".cdx": 
                    {
                        aLoadedModel.Open(new Base_UTF16String(thePath));
                        return aLoadedModel;
                    }
            }
        }
        aReader.ReadFile(new Base_UTF16String(thePath));

        aReader.Transfer(aLoadedModel);
        return aLoadedModel;
    }
    static A3DS_Reader CreateA3DSReader(bool theImportPMI) {
        A3DS_ReaderParameters aParam = new A3DS_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new A3DS_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static ACIS_Reader CreateACISReader(bool theImportPMI) {
        ACIS_ReaderParameters aParam = new ACIS_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new ACIS_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static BRep_Reader CreateBRepReader(bool theImportPMI) {
        BRep_ReaderParameters aParam = new BRep_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new BRep_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static CAT_Reader CreateCATReader(bool theImportPMI) {
        CAT_ReaderParameters aParam = new CAT_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new CAT_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static Collada_Reader CreateColladaReader(bool theImportPMI) {
        Collada_ReaderParameters aParam = new Collada_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new Collada_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static Creo_Reader CreateCreoReader(bool theImportPMI) {
        Creo_ReaderParameters aParam = new Creo_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new Creo_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static DWG_Reader CreateDWGReader(bool theImportPMI) {
        DWG_ReaderParameters aParam = new DWG_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new DWG_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static DXF_Reader CreateDXFReader(bool theImportPMI) {
        DXF_ReaderParameters aParam = new DXF_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new DXF_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static FBX_Reader CreateFBXReader(bool theImportPMI) {
        FBX_ReaderParameters aParam = new FBX_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new FBX_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static IFC_Reader CreateIFCReader(bool theImportPMI) {
        IFC_ReaderParameters aParam = new IFC_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new IFC_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static IGES_Reader CreateIGESReader(bool theImportPMI) {
        IGES_ReaderParameters aParam = new IGES_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new IGES_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static JT_Reader CreateJTReader(bool theImportPMI) {
        JT_ReaderParameters aParam = new JT_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new JT_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static NX_Reader CreateNXReader(bool theImportPMI) {
        NX_ReaderParameters aParam = new NX_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new NX_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static OBJ_Reader CreateOBJReader(bool theImportPMI) {
        OBJ_ReaderParameters aParam = new OBJ_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new OBJ_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static Para_Reader CreateParaReader(bool theImportPMI) {
        Para_ReaderParameters aParam = new Para_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new Para_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static Rhino_Reader CreateRhinoReader(bool theImportPMI) {
        Rhino_ReaderParameters aParam = new Rhino_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new Rhino_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static SLD_Reader CreateSLDReader(bool theImportPMI) {
        SLD_ReaderParameters aParam = new SLD_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new SLD_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static STEP_Reader CreateSTEPReader(bool theImportPMI) {
        STEP_ReaderParameters aParam = new STEP_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new STEP_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static STL_Reader CreateSTLReader(bool theImportPMI) {
        STL_ReaderParameters aParam = new STL_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new STL_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static U3D_Reader CreateU3DReader(bool theImportPMI) {
        U3D_ReaderParameters aParam = new U3D_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new U3D_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static VRML_Reader CreateVRMLReader(bool theImportPMI) {
        VRML_ReaderParameters aParam = new VRML_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new VRML_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static X3D_Reader CreateX3DReader(bool theImportPMI) {
        X3D_ReaderParameters aParam = new X3D_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new X3D_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static X3MF_Reader CreateX3MFReader(bool theImportPMI) {
        X3MF_ReaderParameters aParam = new X3MF_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        var aTarget = new X3MF_Reader();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
}
