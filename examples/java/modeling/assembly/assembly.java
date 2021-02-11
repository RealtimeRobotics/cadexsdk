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

public class assembly {
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

        // Initial Parameters
        double aRadius = 0.8;

        ModelData_Vector aPos[] = {
            new ModelData_Vector(aRadius * -2, aRadius * 1.5, 0.),
            new ModelData_Vector(aRadius * 2, aRadius * 1.5, 0.),
            new ModelData_Vector(aRadius * 0, aRadius * 4.5, 0.),
        };

        // Create shapes
        ModelData_Part aNut = CreateNut(aRadius);
        ModelData_Part aBolt = CreateBolt(aRadius);

        // Create assemblis
        ModelData_Assembly aNutBoltAssembly = CreateNutBoltAssembly(aNut, aBolt, -aRadius * 4.5);

        // Create a model and fill its roots
        ModelData_Model aModel = new ModelData_Model();

        // Transformations
        for (int i = 0; i < aPos.length; ++i) {
            ModelData_Transformation anAssemblyTrsf = new ModelData_Transformation(aPos[i]);
            ModelData_Instance anInstance =
                    new ModelData_Instance(aNutBoltAssembly, anAssemblyTrsf, new Base_UTF16String("Nut-Bolt Assembly"));
            aModel.AddRoot(anInstance);
        }

        // Save the result
        if (!aModel.Save(new Base_UTF16String("assembly.xml"))) {
            System.out.println("Unable to save the model!");
            System.exit(1);
        }
    }

    static ModelData_Direction XDir = ModelData_Direction.XDir(),
            YDir = ModelData_Direction.YDir(),
            ZDir = ModelData_Direction.ZDir(),
            XDirR = new ModelData_Direction(-1., 0., 0.),
            YDirR = new ModelData_Direction(0., -1., 0.),
            ZDirR = new ModelData_Direction(0., 0., -1.);

    static ModelData_Direction MakeDirection(ModelData_Vector theVector) {
        ModelData_Vectord aVector = theVector.Normalized();
        return new ModelData_Direction(aVector.X(), aVector.Y(), aVector.Z());
    }

    static ModelData_Face MakeCircularFace(ModelData_Point thePos, ModelData_Direction theDir, ModelData_Edge theBoundary) {
        ModelData_Axis3Placement a3Axis = new ModelData_Axis3Placement(thePos, theDir, XDir);
        ModelData_Plane aPlane = new ModelData_Plane(a3Axis);
        ModelData_Face aFace = new ModelData_Face(aPlane);

        ModelData_Wire aWire = new ModelData_Wire(theBoundary);
        aFace.Append(aWire);

        return aFace;
    }

    static ModelData_Face MakeCircularFaceWithInnerWire(
            ModelData_Point thePos, ModelData_Direction theDir, ModelData_Edge theInner, ModelData_Edge theOuter) {
        ModelData_Axis3Placement a3Axis = new ModelData_Axis3Placement(thePos, theDir, XDir);
        ModelData_Plane aPlane = new ModelData_Plane(a3Axis);
        ModelData_Face aFace = new ModelData_Face(aPlane);

        ModelData_Wire anInner = new ModelData_Wire(theInner), anOuter = new ModelData_Wire(theOuter);
        aFace.Append(anInner);
        aFace.Append(anOuter);

        return aFace;
    }

    static ModelData_Face MakeCylindricalFace(ModelData_Point thePos, ModelData_Direction theDir, double theRadius, double theLength) {
        ModelData_Axis3Placement a3Axis = new ModelData_Axis3Placement(thePos, theDir, XDir);
        ModelData_CylindricalSurface aSurface = new ModelData_CylindricalSurface(a3Axis, theRadius);
        ModelData_Face aFace = new ModelData_Face(aSurface, 0, Math.PI * 2, 0, theLength);

        return aFace;
    }

    static ModelData_Part CreateNut(double theRadius) {
        double aNutA = theRadius * 2, aNutB = theRadius * 1.5, aHeight = theRadius / 2;

        ModelData_Point anInitPosition = new ModelData_Point(0., 0., -aHeight / 2);
        ModelData_Axis2Placement a2Axis = new ModelData_Axis2Placement(anInitPosition, ZDir, XDir);
        ModelData_Axis3Placement a3Axis = new ModelData_Axis3Placement(a2Axis);

        ModelData_Plane aPlane = new ModelData_Plane(a3Axis);
        ModelData_Face aFace = new ModelData_Face(aPlane, -aNutA, aNutA, -aNutB, aNutB);

        ModelData_Circle aCircle = new ModelData_Circle(a2Axis, theRadius);
        ModelData_Wire anInnerWire = new ModelData_Wire(new ModelData_Edge(aCircle));
        aFace.Append(ModelData_Wire.Cast(anInnerWire.Reversed()));

        ModelData_Shape aNutShape = ModelAlgo_BRepFeatures.CreateExtrusion(aFace, new ModelData_Vector(0., 0., aHeight));

        // Add red color
        ModelData_Color aColor = new ModelData_Color(255, 0, 0);
        ModelData_Appearance anApp = new ModelData_Appearance(aColor);

        ModelData_BRepRepresentation aBRep = new ModelData_BRepRepresentation(aNutShape);
        aBRep.SetAppearance(aNutShape, anApp);

        ModelData_Part aNut = new ModelData_Part(aBRep, new Base_UTF16String("Nut"));
        return aNut;
    }

    static ModelData_Part CreateBolt(double theRadius) {
        double aMajorRadius = theRadius * 1.3;
        double aLongLength = theRadius * 6;
        double aShortLength = theRadius / 2;

        // Cylindrical faces and their edges
        ModelData_Edge aTopEdge = null, aMiddleOuterEdge = null, aMiddleInnerEdge = null, aBottomEdge = null;

        ModelData_Face aFace1 = MakeCylindricalFace(new ModelData_Point(0., 0., 0.), ZDir, aMajorRadius, aShortLength);

        // Get outer edges of aFace1
        ModelData_Wire aWire1 = aFace1.OuterWire();
        ModelData_Shape.Iterator anIt1 = new ModelData_Shape.Iterator(aWire1, ModelData_ShapeType.ModelData_ST_Edge);
        while (anIt1.HasNext()) {
            ModelData_Edge anEdge = ModelData_Edge.Cast(anIt1.Next());
            ModelData_Point aP1 = anEdge.EndVertex().Point();
            ModelData_Point aP2 = anEdge.StartVertex().Point();

            if (aP1.IsEqual(aP2, 0.0000001 /*standard tolerance value*/)) {
                // The edge is closed
                if (aP1.Z() == (aShortLength * ZDir.Z())) {
                    aTopEdge = anEdge;
                } else {
                    aMiddleOuterEdge = anEdge;
                }
            }
        }

        ModelData_Face aFace2 = MakeCylindricalFace(new ModelData_Point(0., 0., 0.), ZDirR, theRadius, aLongLength);

        // Get outer edges of aFace2
        ModelData_Wire aWire2 = aFace2.OuterWire();
        ModelData_Shape.Iterator anIt2 = new ModelData_Shape.Iterator(aWire2, ModelData_ShapeType.ModelData_ST_Edge);
        while (anIt2.HasNext()) {
            ModelData_Edge anEdge = ModelData_Edge.Cast(anIt2.Next());
            ModelData_Point aP1 = anEdge.EndVertex().Point();
            ModelData_Point aP2 = anEdge.StartVertex().Point();

            if (aP1.IsEqual(aP2, 0.0000001 /*standard tolerance value*/)) {
                // The edge is closed
                if (aP1.Z() == (aLongLength * ZDirR.Z())) {
                    aBottomEdge = anEdge;
                } else {
                    aMiddleInnerEdge = anEdge;
                }
            }
        }

        // Top circle
        ModelData_Face aFace3 = MakeCircularFace(new ModelData_Point(0., 0., aShortLength), ZDir, ModelData_Edge.Cast(aTopEdge.Reversed()));

        // Face 4 with inner wire
        ModelData_Face aFace4 =
                MakeCircularFaceWithInnerWire(
                        new ModelData_Point(0., 0., 0.),
                        ZDirR,
                        ModelData_Edge.Cast(aMiddleInnerEdge.Reversed()),
                        ModelData_Edge.Cast(aMiddleOuterEdge.Reversed()));

        // Bottom circle
        ModelData_Face aFace5 =
                MakeCircularFace(new ModelData_Point(0., 0., -aLongLength), ZDirR, ModelData_Edge.Cast(aBottomEdge.Reversed()));

        ModelData_Shell aShell = new ModelData_Shell(aFace1);
        aShell.Append(aFace2);
        aShell.Append(aFace3);
        aShell.Append(aFace4);
        aShell.Append(aFace5);

        ModelData_Solid aSolid = new ModelData_Solid(aShell);

        // Add blue color
        ModelData_Color aColor = new ModelData_Color(0, 0, 255);
        ModelData_Appearance anApp = new ModelData_Appearance(aColor);

        ModelData_BRepRepresentation aBRep = new ModelData_BRepRepresentation(aSolid);
        aBRep.SetAppearance(aSolid, anApp);

        ModelData_Part aBolt = new ModelData_Part(aBRep, new Base_UTF16String("Bolt"));
        return aBolt;
    }

    static ModelData_Assembly CreateNutBoltAssembly(ModelData_Part theNut, ModelData_Part theBolt, double theDistance) {
        ModelData_Transformation aNutTrsf = new ModelData_Transformation(new ModelData_Vector(0., 0., 0.));
        ModelData_Transformation aBoltTrsf = new ModelData_Transformation(new ModelData_Vector(0., 0., -theDistance));

        ModelData_Assembly aNutBoltAssembly = new ModelData_Assembly(new Base_UTF16String("nut-bolt assembly"));
        aNutBoltAssembly.AddInstance(theNut, aNutTrsf);
        aNutBoltAssembly.AddInstance(theBolt, aBoltTrsf);
        return aNutBoltAssembly;
    }
}
