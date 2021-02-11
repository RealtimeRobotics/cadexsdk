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

namespace brep
{
    partial class Program
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

            ModelData_Edge aLine = edgeutil.MakeEdgeFromLine();
            SaveModel(aLine, new Base_UTF16String("LineEdge"));
            ModelData_Edge aCircle = edgeutil.MakeEdgeFromCircle();
            SaveModel(aCircle, new Base_UTF16String("CircleEdge"));
            ModelData_Edge anEllipse = edgeutil.MakeEdgeFromEllipse();
            SaveModel(anEllipse, new Base_UTF16String("EllipseEdge"));
            ModelData_Edge aParabola = edgeutil.MakeEdgeFromParabola();
            SaveModel(aParabola, new Base_UTF16String("ParabolaEdge"));
            ModelData_Edge aHyperbola = edgeutil.MakeEdgeFromHyperbola();
            SaveModel(aHyperbola, new Base_UTF16String("HyperbolaEdge"));
            ModelData_Edge anEdgeFromOffsetCurve = edgeutil.MakeEdgeFromOffSetCurve();
            SaveModel(anEdgeFromOffsetCurve, new Base_UTF16String("OffsetEdge"));
            ModelData_Edge aBezierEdge = edgeutil.MakeEdgeFromBezier();
            SaveModel(aBezierEdge, new Base_UTF16String("BezierEdge"));
            ModelData_Edge aBSplineEdge = edgeutil.MakeEdgeFromBSpline();
            SaveModel(aBSplineEdge, new Base_UTF16String("BSplineEdge"));

            ModelData_Face aPlane = faceutil.MakePlanarFace();
            SaveModel(aPlane, new Base_UTF16String("PlaneFace"));
            ModelData_Face aSphere = faceutil.MakeSphericalFace();
            SaveModel(aSphere, new Base_UTF16String("SphereFace"));
            ModelData_Face aCylinder = faceutil.MakeCylindricalFace();
            SaveModel(aCylinder, new Base_UTF16String("CylinderFace"));
            ModelData_Face aCone = faceutil.MakeConicalFace();
            SaveModel(aCone, new Base_UTF16String("ConeFace"));
            ModelData_Face aTorus = faceutil.MakeToroidalFace();
            SaveModel(aTorus, new Base_UTF16String("TorusFace"));
            ModelData_Face aFaceFromLESurface = faceutil.MakeFaceFromSurfaceOfLinearExtrusion();
            SaveModel(aFaceFromLESurface, new Base_UTF16String("LEFace"));
            ModelData_Face aFaceFromRevSurface = faceutil.MakeFaceFromSurfaceOfRevolution();
            SaveModel(aFaceFromRevSurface, new Base_UTF16String("RevFace"));
            ModelData_Face aFaceFromOffsetSurface = faceutil.MakeFaceFromOffsetSurface();
            SaveModel(aFaceFromOffsetSurface, new Base_UTF16String("OffsetFace"));
            ModelData_Face aBezierFace = faceutil.MakeFaceFromBezier();
            SaveModel(aBezierFace, new Base_UTF16String("BezierFace"));
            ModelData_Face aBSplineFace = faceutil.MakeFaceFromBSpline();
            SaveModel(aBSplineFace, new Base_UTF16String("BSplineFace"));
            ModelData_Face aFace = faceutil.MakeFaceWithInnerWire();
            SaveModel(aFace, new Base_UTF16String("InnerWireFace"));

            ModelData_Body aSolid = bodyutil.MakeSolidBody();
            SaveModel(aSolid, new Base_UTF16String("SolidBody"));
            ModelData_Body aSheet = bodyutil.MakeSheetBody();
            SaveModel(aSheet, new Base_UTF16String("SheetBody"));
            ModelData_Body aWireframe = bodyutil.MakeWireframeBody();
            SaveModel(aWireframe, new Base_UTF16String("WireframeBody"));
            ModelData_Body anAcorn = bodyutil.MakeAcornBody();
            SaveModel(anAcorn, new Base_UTF16String("AcornBody"));

            return 0;
        }

        static bool SaveModel(ModelData_Shape theShape, Base_UTF16String theName)
        {
            ModelData_Model aModel = new ModelData_Model();
            ModelData_BRepRepresentation aBRep = new ModelData_BRepRepresentation(theShape);
            ModelData_Part aPart = new ModelData_Part(aBRep, new Base_UTF16String(theName));
            aModel.AddRoot(aPart);

            Base_UTF16String aPath = new Base_UTF16String(theName.ToString() + ".xml");
            return aModel.Save(aPath);
        }
    }
}
