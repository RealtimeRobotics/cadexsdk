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


#include <cadex/Base_UTF16String.hxx>
#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_Shape.hxx>
#include <iostream>

#include "../../cadex_license.cxx"
#include "bodyutil.cxx"
#include "edgeutil.cxx"
#include "faceutil.cxx"


using namespace std;
using namespace cadex;

static bool SaveModel (const ModelData_Shape& theShape, Base_UTF16String theName)
{
    ModelData_Model aModel;
    ModelData_Part aPart (ModelData_BRepRepresentation (theShape), theName);
    aModel.AddRoot (aPart);

    Base_UTF16String aPath = theName + ".xml";
    return aModel.Save (aPath);
}

int main()
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    ModelData_Edge aLine = MakeEdgeFromLine();
    SaveModel (aLine, "LineEdge");
    ModelData_Edge aCircle = MakeEdgeFromCircle();
    SaveModel (aCircle, "CircleEdge");
    ModelData_Edge anEllipse = MakeEdgeFromEllipse();
    SaveModel (anEllipse, "EllipseEdge");
    ModelData_Edge aParabola = MakeEdgeFromParabola();
    SaveModel (aParabola, "ParabolaEdge");
    ModelData_Edge aHyperbola = MakeEdgeFromHyperbola();
    SaveModel (aHyperbola, "HyperbolaEdge");
    ModelData_Edge anEdgeFromOffsetCurve = MakeEdgeFromOffSetCurve();
    SaveModel (anEdgeFromOffsetCurve, "OffsetEdge");
    ModelData_Edge aBezierEdge = MakeEdgeFromBezier();
    SaveModel (aBezierEdge, "BezierEdge");
    ModelData_Edge aBSplineEdge = MakeEdgeFromBSpline();
    SaveModel (aBSplineEdge, "BSplineEdge");

    ModelData_Face aPlane = MakePlanarFace();
    SaveModel (aPlane, "PlaneFace");
    ModelData_Face aSphere = MakeSphericalFace();
    SaveModel (aSphere, "SphereFace");
    ModelData_Face aCylinder = MakeCylindricalFace();
    SaveModel (aCylinder, "CylinderFace");
    ModelData_Face aCone = MakeConicalFace();
    SaveModel (aCone, "ConeFace");
    ModelData_Face aTorus = MakeToroidalFace();
    SaveModel (aTorus, "TorusFace");
    ModelData_Face aFaceFromLESurface = MakeFaceFromSurfaceOfLinearExtrusion();
    SaveModel (aFaceFromLESurface, "LEFace");
    ModelData_Face aFaceFromRevSurface = MakeFaceFromSurfaceOfRevolution();
    SaveModel (aFaceFromRevSurface, "RevFace");
    ModelData_Face aFaceFromOffsetSurface = MakeFaceFromOffsetSurface();
    SaveModel (aFaceFromOffsetSurface, "OffsetFace");
    ModelData_Face aBezierFace = MakeFaceFromBezier();
    SaveModel (aBezierFace, "BezierFace");
    ModelData_Face aBSplineFace = MakeFaceFromBSpline();
    SaveModel (aBSplineFace, "BSplineFace");
    ModelData_Face aFace = MakeFaceWithInnerWire();
    SaveModel (aFace, "InnerWireFace");

    ModelData_Body aSolid = MakeSolidBody();
    SaveModel (aSolid, "SolidBody");
    ModelData_Body aSheet = MakeSheetBody();
    SaveModel (aSheet, "SheetBody");
    ModelData_Body aWireframe = MakeWireframeBody();
    SaveModel (aWireframe, "WireframeBody");
    ModelData_Body anAcorn = MakeAcornBody();
    SaveModel (anAcorn, "AcornBody");

    return 0;
}