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

public static class ModelExporter 
{
    public static bool ExportModel(ModelData_Model theModel, string thePath) 
    {
        string aModelExpansion = Path.GetExtension(thePath).ToLower();
        Base_Writer aWriter = null;

        switch (aModelExpansion) {
            case ".sat":
            case ".sab": aWriter = CreateACISWriter(); break;
            case ".brep": aWriter = CreateBRepWriter(); break;
            case ".dae": aWriter = CreateColladaWriter(); break;
            case ".dxf": aWriter = CreateDXFWriter(); break;
            case ".fbx": aWriter = CreateFBXWriter(); break;
            case ".glb":
            case ".gltf": aWriter = CreateGLTFWriter(); break;
            case ".ifc": aWriter = CreateIFCWriter(); break;
            case ".igs":
            case ".iges": aWriter = CreateIGESWriter(); break;
            case ".jt": aWriter = CreateJTWriter(); break;
            case ".obj": aWriter = CreateOBJWriter(); break;
            case ".x_t":
            case ".x_b":
            case ".xmt_txt":
            case ".xmt_bin":
            case ".xmp_txt":
            case ".xmp_bin": aWriter = CreateParaWriter(); break;
            case ".3dm": aWriter = CreateRhinoWriter(); break;
            case ".stp":
            case ".step": aWriter = CreateSTEPWriter(); break;
            case ".stl": aWriter = CreateSTLWriter(); break;
            case ".wrl": aWriter = CreateVRMLWriter(); break;
            case ".x3d": aWriter = CreateX3DWriter(); break;
            case ".xml":
            case ".cdx": return theModel.Save(new Base_UTF16String(thePath));
        }

        aWriter.Transfer(theModel);
        return aWriter.WriteFile(new Base_UTF16String(thePath));
    }
    static ACIS_Writer CreateACISWriter() 
    {
        ACIS_WriterParameters aParam = new ACIS_WriterParameters();
        var aTarget = new ACIS_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static BRep_Writer CreateBRepWriter() 
    {
        BRep_WriterParameters aParam = new BRep_WriterParameters();
        var aTarget = new BRep_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static Collada_Writer CreateColladaWriter() 
    {
        Collada_WriterParameters aParam = new Collada_WriterParameters();
        var aTarget = new Collada_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static DXF_Writer CreateDXFWriter() 
    {
        DXF_WriterParameters aParam = new DXF_WriterParameters();
        var aTarget = new DXF_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static FBX_Writer CreateFBXWriter() 
    {
        FBX_WriterParameters aParam = new FBX_WriterParameters();
        var aTarget = new FBX_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static GLTF_Writer CreateGLTFWriter() 
    {
        GLTF_WriterParameters aParam = new GLTF_WriterParameters();
        var aTarget = new GLTF_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static IFC_Writer CreateIFCWriter()
    {
        IFC_WriterParameters aParam = new IFC_WriterParameters();
        var aTarget = new IFC_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static IGES_Writer CreateIGESWriter() 
    {
        IGES_WriterParameters aParam = new IGES_WriterParameters();
        var aTarget = new IGES_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static JT_Writer CreateJTWriter() 
    {
        JT_WriterParameters aParam = new JT_WriterParameters();
        var aTarget = new JT_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static OBJ_Writer CreateOBJWriter() 
    {
        OBJ_WriterParameters aParam = new OBJ_WriterParameters();
        var aTarget = new OBJ_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static Para_Writer CreateParaWriter() 
    {
        Para_WriterParameters aParam = new Para_WriterParameters();
        var aTarget = new Para_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static Rhino_Writer CreateRhinoWriter() 
    {
        Rhino_WriterParameters aParam = new Rhino_WriterParameters();
        var aTarget = new Rhino_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static STEP_Writer CreateSTEPWriter() 
    {
        STEP_WriterParameters aParam = new STEP_WriterParameters();
        var aTarget = new STEP_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static STL_Writer CreateSTLWriter() 
    {
        STL_WriterParameters aParam = new STL_WriterParameters();
        var aTarget = new STL_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static VRML_Writer CreateVRMLWriter() 
    {
        VRML_WriterParameters aParam = new VRML_WriterParameters();
        var aTarget = new VRML_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
    static X3D_Writer CreateX3DWriter() 
    {
        X3D_WriterParameters aParam = new X3D_WriterParameters();
        var aTarget = new X3D_Writer();
        aTarget.SetParameters(aParam);
        return aTarget;
    }
}
