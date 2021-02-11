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


#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelAlgo_TopoPrimitives.hxx>
#include <cadex/ModelAlgo_BRepFeatures.hxx>
#include <cadex/ModelCheck_BRepChecker.hxx>
#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_Assembly.hxx>
#include <cadex/ModelData_Axis2Placement.hxx>
#include <cadex/ModelData_Axis3Placement.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Circle.hxx>
#include <cadex/ModelData_Color.hxx>
#include <cadex/ModelData_CylindricalSurface.hxx>
#include <cadex/ModelData_Direction.hxx>
#include <cadex/ModelData_Edge.hxx>
#include <cadex/ModelData_Face.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Line.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_Plane.hxx>
#include <cadex/ModelData_Point.hxx>
#include <cadex/ModelData_RectangularTrimmedSurface.hxx>
#include <cadex/ModelData_Shape.hxx>
#include <cadex/ModelData_Shell.hxx>
#include <cadex/ModelData_Solid.hxx>
#include <cadex/ModelData_Transformation.hxx>
#include <cadex/ModelData_Vector.hxx>
#include <cadex/ModelData_Vertex.hxx>
#include <cadex/ModelData_Wire.hxx>
#include <array>
#include <cmath>
#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

static const ModelData_Direction XDir  = ModelData_Direction::XDir(),
                                 YDir  = ModelData_Direction::YDir(),
                                 ZDir  = ModelData_Direction::ZDir(),
                                 XDirR = ModelData_Direction (-1.,  0.,  0.),
                                 YDirR = ModelData_Direction ( 0., -1.,  0.),
                                 ZDirR = ModelData_Direction ( 0.,  0., -1.);

static ModelData_Face MakeCircularFace (const ModelData_Point& thePos, const ModelData_Direction& theDir, const ModelData_Edge& theBoundary)
{
    ModelData_Axis3Placement a3Axis (thePos, theDir, XDir);
    ModelData_Plane aPlane (a3Axis);
    ModelData_Face aFace (aPlane);

    ModelData_Wire aWire (theBoundary);
    aFace.Append (aWire);

    return aFace;
}

static ModelData_Face MakeCircularFaceWithInnerWire (const ModelData_Point& thePos, const ModelData_Direction& theDir,
                                                     const ModelData_Edge& theInner, const ModelData_Edge& theOuter)
{
    ModelData_Axis3Placement a3Axis (thePos, theDir, XDir);
    ModelData_Plane aPlane (a3Axis);
    ModelData_Face aFace (aPlane);

    ModelData_Wire anInner (theInner), anOuter (theOuter);
    aFace.Append (anInner);
    aFace.Append (anOuter);

    return aFace;
}

static ModelData_Face MakeCylindricalFace (const ModelData_Point& thePos, const ModelData_Direction& theDir, double theRadius, double theLength,
                                           ModelData_Edge& theTopEdge, ModelData_Edge& theBottomEdge,
                                           ModelData_Curve& theTopPCurve, ModelData_Curve& theBottomPCurve)
{
    ModelData_Axis3Placement a3Axis (thePos, theDir, XDir);
    ModelData_CylindricalSurface aSurface (a3Axis, theRadius);
    ModelData_Face aFace (aSurface, 0, M_PI * 2 , 0, theLength);

    // Get outer edges
    const ModelData_Wire& aWire = aFace.OuterWire();
    ModelData_Shape::Iterator anIt (aWire, ModelData_ST_Edge);
    while (anIt.HasNext()) {
        ModelData_Edge anEdge = ModelData_Edge::Cast (anIt.Next());
        ModelData_Point aP1 = anEdge.EndVertex().Point();
        ModelData_Point aP2 = anEdge.StartVertex().Point();
        if (aP1 == aP2) {
            // The edge is closed
            array<double, 2> aParameters = {{0., M_PI * 2}};
            enum {First, Last};
            if (aP1.Z() == (theLength * theDir.Z())) {
                theTopEdge = anEdge;
                theTopPCurve = anEdge.Curve (aParameters[First], aParameters[Last]);
            } else {
                theBottomEdge = anEdge;
                theBottomPCurve = anEdge.Curve (aParameters[First], aParameters[Last]);
            }
        };
    }

    return aFace;
}

static ModelData_Part CreateNut (double theRadius)
{
    double aNutA = theRadius * 2, aNutB = theRadius * 1.5, aHeight = theRadius / 2;

    ModelData_Point anInitPosition (0., 0., -aHeight / 2);
    ModelData_Axis2Placement a2Axis (anInitPosition, ZDir, XDir);
    ModelData_Axis3Placement a3Axis (a2Axis);

    ModelData_Plane aPlane (a3Axis);
    ModelData_Face aFace (aPlane, -aNutA, aNutA, -aNutB, aNutB);

    ModelData_Circle aCircle (a2Axis, theRadius);
    ModelData_Wire anInnerWire (aCircle);
    aFace.Append (ModelData_Wire::Cast (anInnerWire.Reversed()));

    ModelData_Shape aNutShape = ModelAlgo_BRepFeatures::CreateExtrusion (aFace, ModelData_Vector (0., 0., aHeight));

    // Add red color
    ModelData_Color aColor (255, 0, 0);
    ModelData_Appearance anApp (aColor);

    ModelData_BRepRepresentation aBRep (aNutShape);
    aBRep.SetAppearance (aNutShape, anApp);

    ModelData_Part aNut (aBRep, "Nut");
    return aNut;
}

static ModelData_Part CreateBolt (double theRadius)
{
    double aMajorRadius = theRadius * 1.3;
    double aLongLength  = theRadius * 6;
    double aShortLength = theRadius / 2;

    // Cylindrical faces and their edges
    ModelData_Edge aTopEdge, aMiddleOuterEdge, aMiddleInnerEdge, aBottomEdge;
    ModelData_Curve aTopPCurve, aMiddleOuterPcurve, aMiddleInnerPCurve, aBottomPCurve;
    ModelData_Face aFace1 = MakeCylindricalFace (ModelData_Point (0., 0., 0.), ZDir, aMajorRadius, aShortLength,
        aTopEdge, aMiddleOuterEdge,
        aTopPCurve, aMiddleOuterPcurve);
    ModelData_Face aFace2 = MakeCylindricalFace (ModelData_Point (0., 0., 0.), ZDirR, theRadius, aLongLength,
        aBottomEdge, aMiddleInnerEdge,
        aBottomPCurve, aMiddleOuterPcurve);

    // Top circle
    ModelData_Face aFace3 = MakeCircularFace (ModelData_Point (0., 0., aShortLength), ZDir, ModelData_Edge::Cast (aTopEdge.Reversed()));

    // Face 4 with inner wire
    ModelData_Face aFace4 = MakeCircularFaceWithInnerWire (ModelData_Point (0., 0., 0.), ZDirR,
                                                           ModelData_Edge::Cast (aMiddleInnerEdge.Reversed()),
                                                           ModelData_Edge::Cast (aMiddleOuterEdge.Reversed()));

    // Bottom circle
    ModelData_Face aFace5 = MakeCircularFace (ModelData_Point (0., 0., -aLongLength), ZDirR, ModelData_Edge::Cast (aBottomEdge.Reversed()));

    ModelData_Shell aShell;
    aShell.Append (aFace1);
    aShell.Append (aFace2);
    aShell.Append (aFace3);
    aShell.Append (aFace4);
    aShell.Append (aFace5);

    ModelData_Solid aSolid (aShell);

    // Check our solid
    ModelCheck_BRepChecker aChecker;
    aChecker.Check (aSolid);
    if (!aChecker.HasProblems()) {
        cout << "a bolt is valid" << endl;
    } else {
        cout << "a bolt is invalid" << endl;
    }

    // Add blue color
    ModelData_Color aColor (0, 0, 255);
    ModelData_Appearance anApp (aColor);

    ModelData_BRepRepresentation aBRep (aSolid);
    aBRep.SetAppearance (aSolid, anApp);

    ModelData_Part aBolt (aBRep, "Bolt");
    return aBolt;
}

static ModelData_Assembly CreateNutBoltAssembly (const ModelData_Part& theNut, const ModelData_Part& theBolt, double theDistance) {
    ModelData_Transformation aNutTrsf  (ModelData_Vector (0., 0., 0.));
    ModelData_Transformation aBoltTrsf (ModelData_Vector (0., 0., -theDistance));

    ModelData_Assembly aNutBoltAssembly ("nut-bolt assembly");
    aNutBoltAssembly.AddInstance (theNut, aNutTrsf);
    aNutBoltAssembly.AddInstance (theBolt, aBoltTrsf);
    return aNutBoltAssembly;
}

int main()
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    // Initial Parameters
    double aRadius = 0.8;

    array<ModelData_Vector, 3> aPos = {{
        ModelData_Vector (aRadius * -2, aRadius * 1.5, 0.),
        ModelData_Vector (aRadius *  2, aRadius * 1.5, 0.),
        ModelData_Vector (aRadius *  0, aRadius * 4.5, 0.),
    }};

    // Create shapes
    ModelData_Part aNut  = CreateNut (aRadius);
    ModelData_Part aBolt = CreateBolt (aRadius);

    // Create assemblies
    ModelData_Assembly aNutBoltAssembly = CreateNutBoltAssembly (aNut, aBolt, -aRadius * 4.5);

    // Create a model and fill its roots
    ModelData_Model aModel;

    // Transformations
    for (size_t i = 0; i < aPos.size(); ++i) {
        ModelData_Transformation anAssemblyTrsf (aPos[i]);
        ModelData_Instance anInstance (aNutBoltAssembly, anAssemblyTrsf, "Nut-Bolt Assembly");
        aModel.AddRoot (anInstance);
    }

    aModel.Save ("assembly.xml");

    return 0;
}