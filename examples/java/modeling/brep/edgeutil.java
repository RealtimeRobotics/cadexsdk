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

public class edgeutil {
    private static ModelData_Axis2Placement a2Axis = new ModelData_Axis2Placement();

    static ModelData_Edge MakeEdgeFromLine() {
        ModelData_Line aCurve = new ModelData_Line(new ModelData_Point(0., 0., 0.), ModelData_Direction.XDir());
        return new ModelData_Edge(aCurve, -2., 2.);
    }

    static ModelData_Edge MakeEdgeFromCircle() {
        ModelData_Circle aCurve = new ModelData_Circle(a2Axis, 5.);
        return new ModelData_Edge(aCurve, 0., Math.PI);
    }

    static ModelData_Edge MakeEdgeFromEllipse() {
        ModelData_Ellipse aCurve = new ModelData_Ellipse(a2Axis, 7., 3.);
        return new ModelData_Edge(aCurve, 0., Math.PI);
    }

    static ModelData_Edge MakeEdgeFromParabola() {
        ModelData_Parabola aCurve = new ModelData_Parabola(a2Axis, 5.);
        return new ModelData_Edge(aCurve, -2., 2.);
    }

    static ModelData_Edge MakeEdgeFromHyperbola() {
        ModelData_Hyperbola aCurve = new ModelData_Hyperbola(a2Axis, 7., 3.);
        return new ModelData_Edge(aCurve, -2., 2.);
    }

    static ModelData_Edge MakeEdgeFromOffSetCurve() {
        ModelData_Circle aBasisCurve = new ModelData_Circle(a2Axis, 5.);
        ModelData_OffsetCurve aCurve = new ModelData_OffsetCurve(aBasisCurve, 10., ModelData_Direction.ZDir());
        return new ModelData_Edge(aCurve, 0., Math.PI);
    }

    static ModelData_Edge MakeEdgeFromBezier() {
        ModelData_Point[] aPoles = {
            new ModelData_Point(-2., 1., 0.),
            new ModelData_Point(-1., -1., 0.),
            new ModelData_Point(0., 1., 0.),
            new ModelData_Point(1., -1., 0.)
        };

        ModelData_BezierCurve aCurve = new ModelData_BezierCurve(aPoles);
        return new ModelData_Edge(aCurve);
    }

    static ModelData_Edge MakeEdgeFromBSpline() {
        ModelData_Point[] aPoles = {
            new ModelData_Point(1., 1., 0.),
            new ModelData_Point(2., 3., 0.),
            new ModelData_Point(3., 2., 0.),
            new ModelData_Point(4., 3., 0.),
            new ModelData_Point(5., 1., 0.)
        };

        double[] aKnots = {0., 0.25, 0.75, 1.};
        int[] aMultiplicities = {3, 1, 1, 3};
        int aDegree = 2;

        ModelData_BSplineCurve aCurve = new ModelData_BSplineCurve(aPoles, aKnots, aMultiplicities, aDegree);

        return new ModelData_Edge(aCurve);
    }
}
