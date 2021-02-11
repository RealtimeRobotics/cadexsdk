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

#include <cadex/ModelData_Axis2Placement.hxx>
#include <cadex/ModelData_BezierCurve.hxx>
#include <cadex/ModelData_BSplineCurve.hxx>
#include <cadex/ModelData_Circle.hxx>
#include <cadex/ModelData_Curve.hxx>
#include <cadex/ModelData_Direction.hxx>
#include <cadex/ModelData_Edge.hxx>
#include <cadex/ModelData_Ellipse.hxx>
#include <cadex/ModelData_Hyperbola.hxx>
#include <cadex/ModelData_Line.hxx>
#include <cadex/ModelData_OffsetCurve.hxx>
#include <cadex/ModelData_Parabola.hxx>
#include <cadex/ModelData_Point.hxx>
#include <array>
#include <cmath>


using namespace std;
using namespace cadex;

static const ModelData_Axis2Placement a2Axis;

static ModelData_Edge MakeEdgeFromLine()
{
    ModelData_Line aCurve (ModelData_Point (0., 0., 0.), ModelData_Direction::XDir());
    return ModelData_Edge (aCurve, -2., 2.);
}

static ModelData_Edge MakeEdgeFromCircle()
{
    ModelData_Circle aCurve (a2Axis, 5.);
    return ModelData_Edge (aCurve, 0., M_PI);
}

static ModelData_Edge MakeEdgeFromEllipse()
{
    ModelData_Ellipse aCurve (a2Axis, 7., 3.);
    return ModelData_Edge (aCurve, 0., M_PI);
}

static ModelData_Edge MakeEdgeFromParabola()
{
    ModelData_Parabola aCurve (a2Axis, 5.);
    return ModelData_Edge (aCurve, -2., 2.);
}

static ModelData_Edge MakeEdgeFromHyperbola()
{
    ModelData_Hyperbola aCurve (a2Axis, 7., 3.);
    return ModelData_Edge (aCurve, -2., 2.);
}

static ModelData_Edge MakeEdgeFromOffSetCurve()
{
    ModelData_Circle aBasisCurve (a2Axis, 5.);
    ModelData_OffsetCurve aCurve (aBasisCurve, 10., ModelData_Direction::ZDir());
    return ModelData_Edge (aCurve, 0., M_PI);
}

static ModelData_Edge MakeEdgeFromBezier()
{
    array<ModelData_Point, 4> aPoles = {{
        ModelData_Point (-2.,  1., 0.),
        ModelData_Point (-1., -1., 0.),
        ModelData_Point ( 0.,  1., 0.),
        ModelData_Point ( 1., -1., 0.)
    }};

    ModelData_BezierCurve aCurve (aPoles.data(), static_cast<int> (aPoles.size()));
    return ModelData_Edge (aCurve);
}

static ModelData_Edge MakeEdgeFromBSpline()
{
    const array<ModelData_Point, 5> aPoles = {{
        ModelData_Point (1., 1., 0.),
        ModelData_Point (2., 3., 0.),
        ModelData_Point (3., 2., 0.),
        ModelData_Point (4., 3., 0.),
        ModelData_Point (5., 1., 0.)
    }};

    const array<double, 4> aKnots = {{
        0., 0.25, 0.75, 1.,
    }};

    const array<int, 4> aMultiplicities = {{3, 1, 1, 3}};

    int aDegree = 2;
    ModelData_BSplineCurve aCurve (aPoles.data(), static_cast<int> (aPoles.size()),
                                   aKnots.data(), static_cast<int> (aKnots.size()),
                                   aMultiplicities.data(),
                                   aDegree);

    return ModelData_Edge (aCurve);
}
