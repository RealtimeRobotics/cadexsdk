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

public class faceutil {
    private static ModelData_Axis3Placement a3Axis = new ModelData_Axis3Placement();

    static ModelData_Face MakePlanarFace() {
        ModelData_Plane aSurface = new ModelData_Plane(a3Axis);
        return new ModelData_Face(aSurface, -2., 2., -2., 2.);
    }

    static ModelData_Face MakeSphericalFace() {
        ModelData_SphericalSurface aSurface = new ModelData_SphericalSurface(a3Axis, 10.);
        return new ModelData_Face(aSurface, 0., Math.PI / 2, 0., Math.PI / 2);
    }

    static ModelData_Face MakeCylindricalFace() {
        ModelData_CylindricalSurface aSurface = new ModelData_CylindricalSurface(a3Axis, 5.);
        return new ModelData_Face(aSurface, 0., Math.PI, -2., 2.);
    }

    static ModelData_Face MakeConicalFace() {
        ModelData_ConicalSurface aSurface = new ModelData_ConicalSurface(a3Axis, 1., 7.);
        return new ModelData_Face(aSurface, 0., Math.PI, -2., 2.);
    }

    static ModelData_Face MakeToroidalFace() {
        ModelData_ToroidalSurface aSurface = new ModelData_ToroidalSurface(a3Axis, 7., 3.);
        return new ModelData_Face(aSurface, 0., Math.PI, 0., Math.PI);
    }

    static ModelData_Face MakeFaceFromSurfaceOfLinearExtrusion() {
        ModelData_Point[] aPoles = {
            new ModelData_Point(-2., 1., 0.),
            new ModelData_Point(-1., -1., 0.),
            new ModelData_Point(0., 1., 0.),
            new ModelData_Point(1., -1., 0.),
            new ModelData_Point(2., 1., 0.)
        };

        ModelData_BezierCurve aBasisCurve = new ModelData_BezierCurve(aPoles);

        ModelData_SurfaceOfLinearExtrusion aSurface = new ModelData_SurfaceOfLinearExtrusion(aBasisCurve, ModelData_Direction.ZDir());
        return new ModelData_Face(aSurface, 0.1, 0.9, -10., 10.);
    }

    static ModelData_Face MakeFaceFromSurfaceOfRevolution() {
        ModelData_Point[] aPoles = {
            new ModelData_Point(-2., 1., 0.),
            new ModelData_Point(-1., 3., 0.),
            new ModelData_Point(0., 2., 0.),
            new ModelData_Point(1., 1., 0.),
            new ModelData_Point(2., 2., 0.)
        };

        ModelData_BezierCurve aBasisCurve = new ModelData_BezierCurve(aPoles);

        ModelData_SurfaceOfRevolution aSurface =
                new ModelData_SurfaceOfRevolution(aBasisCurve, new ModelData_Point(0., 0., 0.), ModelData_Direction.XDir());
        return new ModelData_Face(aSurface, 0., Math.PI * 3 / 4, 0.1, 0.9);
    }

    static ModelData_Face MakeFaceFromOffsetSurface() {
        ModelData_Point[] aPoles = {
            new ModelData_Point(0., 0., 1.),
            new ModelData_Point(0., 2., 1.),
            new ModelData_Point(2., 0., 1.),
            new ModelData_Point(2., 2., -1.)
        };

        ModelData_BezierSurface aBasisSurface = new ModelData_BezierSurface(aPoles, 2, 2);

        ModelData_OffsetSurface aSurface = new ModelData_OffsetSurface(aBasisSurface, 10.);
        return new ModelData_Face(aSurface, 0.1, 0.9, 0.1, 0.9);
    }

    static ModelData_Face MakeFaceFromBezier() {
        ModelData_Point[] aPoles = {
            new ModelData_Point(0., 0., 1.),
            new ModelData_Point(0., 2., 1.),
            new ModelData_Point(2., 0., 1.),
            new ModelData_Point(2., 2., -1.)
        };

        ModelData_BezierSurface aSurface = new ModelData_BezierSurface(aPoles, 2, 2);
        return new ModelData_Face(aSurface, 0.25, 0.75, 0.25, 0.75);
    }

    static ModelData_Face MakeFaceFromBSpline() {
        ModelData_Point[] aPoles = {
            new ModelData_Point(0., 0., 1.),
            new ModelData_Point(0., 2., 3.),
            new ModelData_Point(0., 6., 2.),
            new ModelData_Point(0., 8., 3.),
            new ModelData_Point(0., 10., 1.),
            new ModelData_Point(2., 0., 2.),
            new ModelData_Point(2., 2., 2.),
            new ModelData_Point(2., 6., 2.),
            new ModelData_Point(2., 8., 2.),
            new ModelData_Point(2., 10., 2.),
            new ModelData_Point(4., 0., 3.),
            new ModelData_Point(4., 2., 1.),
            new ModelData_Point(4., 6., 2.),
            new ModelData_Point(4., 8., 1.),
            new ModelData_Point(4., 10., 3.),
            new ModelData_Point(6., 0., 2.),
            new ModelData_Point(6., 2., 2.),
            new ModelData_Point(6., 6., 2.),
            new ModelData_Point(6., 8., 2.),
            new ModelData_Point(6., 10., 2.),
            new ModelData_Point(10., 0., 3.),
            new ModelData_Point(10., 2., 1.),
            new ModelData_Point(10., 6., 2.),
            new ModelData_Point(10., 8., 1.),
            new ModelData_Point(10., 10., 3.),
        };

        int aUPoles = 5, aVPoles = 5;

        double[] aUKnots = {0., 0.25, 0.75, 1.}, aVKnots = {0., 0.25, 0.75, 1.};

        int[] aUMultiplicities = {3, 1, 1, 3}, aVMultiplicities = {3, 1, 1, 3};

        int aUDegree = 2;
        int aVDegree = 2;

        ModelData_BSplineSurface aSurface =
                new ModelData_BSplineSurface(
                        aPoles, aUPoles, aVPoles, aUKnots, aVKnots, aUMultiplicities, aVMultiplicities, aUDegree, aVDegree);

        return new ModelData_Face(aSurface, 0.25, 0.75, 0.25, 0.75);
    }

    static ModelData_Face MakeFaceWithInnerWire() {
        ModelData_Axis2Placement anAxis2 = new ModelData_Axis2Placement();
        ModelData_Circle anInnerCircle = new ModelData_Circle(anAxis2, 10.);
        ModelData_Circle anOuterCircle = new ModelData_Circle(anAxis2, 20.);

        ModelData_Edge anOuterEdge = new ModelData_Edge(anOuterCircle);
        ModelData_Edge anInnerEdge = new ModelData_Edge(anInnerCircle);

        ModelData_Wire anOuterWire = new ModelData_Wire(anOuterEdge);
        ModelData_Wire anInnerWire = new ModelData_Wire(ModelData_Edge.Cast(anInnerEdge.Reversed()));

        ModelData_Axis3Placement anAxis3 = new ModelData_Axis3Placement(anAxis2);
        ModelData_Plane aPlane = new ModelData_Plane(anAxis3);
        ModelData_Face aFace = new ModelData_Face(aPlane);

        aFace.Append(anOuterWire);
        aFace.Append(anInnerWire);

        return aFace;
    }
}
