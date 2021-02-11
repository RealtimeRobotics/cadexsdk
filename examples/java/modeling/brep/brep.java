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

public class brep {
    static {
        try {
            System.loadLibrary("CadExCore");
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

        ModelData_Edge aLine = edgeutil.MakeEdgeFromLine();
        SaveModel(aLine, "LineEdge");
        ModelData_Edge aCircle = edgeutil.MakeEdgeFromCircle();
        SaveModel(aCircle, "CircleEdge");
        ModelData_Edge anEllipse = edgeutil.MakeEdgeFromEllipse();
        SaveModel(anEllipse, "EllipseEdge");
        ModelData_Edge aParabola = edgeutil.MakeEdgeFromParabola();
        SaveModel(aParabola, "ParabolaEdge");
        ModelData_Edge aHyperbola = edgeutil.MakeEdgeFromHyperbola();
        SaveModel(aHyperbola, "HyperbolaEdge");
        ModelData_Edge anEdgeFromOffsetCurve = edgeutil.MakeEdgeFromOffSetCurve();
        SaveModel(anEdgeFromOffsetCurve, "OffsetEdge");
        ModelData_Edge aBezierEdge = edgeutil.MakeEdgeFromBezier();
        SaveModel(aBezierEdge, "BezierEdge");
        ModelData_Edge aBSplineEdge = edgeutil.MakeEdgeFromBSpline();
        SaveModel(aBSplineEdge, "BSplineEdge");

        ModelData_Face aPlane = faceutil.MakePlanarFace();
        SaveModel(aPlane, "PlaneFace");
        ModelData_Face aSphere = faceutil.MakeSphericalFace();
        SaveModel(aSphere, "SphereFace");
        ModelData_Face aCylinder = faceutil.MakeCylindricalFace();
        SaveModel(aCylinder, "CylinderFace");
        ModelData_Face aCone = faceutil.MakeConicalFace();
        SaveModel(aCone, "ConeFace");
        ModelData_Face aTorus = faceutil.MakeToroidalFace();
        SaveModel(aTorus, "TorusFace");
        ModelData_Face aFaceFromLESurface = faceutil.MakeFaceFromSurfaceOfLinearExtrusion();
        SaveModel(aFaceFromLESurface, "LEFace");
        ModelData_Face aFaceFromRevSurface = faceutil.MakeFaceFromSurfaceOfRevolution();
        SaveModel(aFaceFromRevSurface, "RevFace");
        ModelData_Face aFaceFromOffsetSurface = faceutil.MakeFaceFromOffsetSurface();
        SaveModel(aFaceFromOffsetSurface, "OffsetFace");
        ModelData_Face aBezierFace = faceutil.MakeFaceFromBezier();
        SaveModel(aBezierFace, "BezierFace");
        ModelData_Face aBSplineFace = faceutil.MakeFaceFromBSpline();
        SaveModel(aBSplineFace, "BSplineFace");
        ModelData_Face aFace = faceutil.MakeFaceWithInnerWire();
        SaveModel(aFace, "InnerWireFace");

        ModelData_Body aSolid = bodyutil.MakeSolidBody();
        SaveModel(aSolid, "SolidBody");
        ModelData_Body aSheet = bodyutil.MakeSheetBody();
        SaveModel(aSheet, "SheetBody");
        ModelData_Body aWireframe = bodyutil.MakeWireframeBody();
        SaveModel(aWireframe, "WireframeBody");
        ModelData_Body anAcorn = bodyutil.MakeAcornBody();
        SaveModel(anAcorn, "AcornBody");
    }

    static boolean SaveModel(ModelData_Shape theShape, String theName) {
        ModelData_Model aModel = new ModelData_Model();
        ModelData_Part aPart = new ModelData_Part(new ModelData_BRepRepresentation(theShape), new Base_UTF16String(theName));
        aModel.AddRoot(aPart);

        Base_UTF16String aPath = new Base_UTF16String(theName + ".xml");
        return aModel.Save(aPath);
    }
}
