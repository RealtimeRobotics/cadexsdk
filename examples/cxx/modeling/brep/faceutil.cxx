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
#include <cadex/ModelData_Axis3Placement.hxx>
#include <cadex/ModelData_BezierCurve.hxx>
#include <cadex/ModelData_BezierSurface.hxx>
#include <cadex/ModelData_BSplineSurface.hxx>
#include <cadex/ModelData_Circle.hxx>
#include <cadex/ModelData_ConicalSurface.hxx>
#include <cadex/ModelData_CylindricalSurface.hxx>
#include <cadex/ModelData_Direction.hxx>
#include <cadex/ModelData_Edge.hxx>
#include <cadex/ModelData_Face.hxx>
#include <cadex/ModelData_OffsetSurface.hxx>
#include <cadex/ModelData_Plane.hxx>
#include <cadex/ModelData_Point.hxx>
#include <cadex/ModelData_Shape.hxx>
#include <cadex/ModelData_SphericalSurface.hxx>
#include <cadex/ModelData_SurfaceOfLinearExtrusion.hxx>
#include <cadex/ModelData_SurfaceOfRevolution.hxx>
#include <cadex/ModelData_ToroidalSurface.hxx>
#include <cadex/ModelData_Wire.hxx>
#include <array>
#include <cmath>


using namespace std;
using namespace cadex;

static const ModelData_Axis3Placement a3Axis;

static ModelData_Face MakePlanarFace()
{
    ModelData_Plane aSurface (a3Axis);
    return ModelData_Face (aSurface, -2., 2., -2., 2.);
}

static ModelData_Face MakeSphericalFace()
{
    ModelData_SphericalSurface aSurface (a3Axis, 10.);
    return ModelData_Face (aSurface, 0., M_PI_2, 0., M_PI_2);
}

static ModelData_Face MakeCylindricalFace()
{
    ModelData_CylindricalSurface aSurface (a3Axis, 5.);
    return ModelData_Face (aSurface, 0., M_PI, -2., 2.);
}

static ModelData_Face MakeConicalFace()
{
    ModelData_ConicalSurface aSurface (a3Axis, 1., 7.);
    return ModelData_Face (aSurface, 0., M_PI, -2., 2.);
}

static ModelData_Face MakeToroidalFace()
{
    ModelData_ToroidalSurface aSurface (a3Axis, 7., 3.);
    return ModelData_Face (aSurface, 0., M_PI, 0., M_PI);
}

static ModelData_Face MakeFaceFromSurfaceOfLinearExtrusion()
{
    array<ModelData_Point, 5> aPoles = {{
        ModelData_Point (-2.,  1., 0.),
        ModelData_Point (-1., -1., 0.),
        ModelData_Point ( 0.,  1., 0.),
        ModelData_Point ( 1., -1., 0.),
        ModelData_Point ( 2.,  1., 0.)
    }};

    ModelData_BezierCurve aBasisCurve (aPoles.data(), static_cast<int> (aPoles.size()));

    ModelData_SurfaceOfLinearExtrusion aSurface (aBasisCurve, ModelData_Direction::ZDir());
    return ModelData_Face (aSurface, 0.1, 0.9, -10., 10.);
}

static ModelData_Face MakeFaceFromSurfaceOfRevolution()
{
    array<ModelData_Point, 5> aPoles = {{
        ModelData_Point (-2.,  1., 0.),
        ModelData_Point (-1.,  3., 0.),
        ModelData_Point ( 0.,  2., 0.),
        ModelData_Point ( 1.,  1., 0.),
        ModelData_Point ( 2.,  2., 0.)
    }};

    ModelData_BezierCurve aBasisCurve (aPoles.data(), static_cast<int> (aPoles.size()));

    ModelData_SurfaceOfRevolution aSurface (aBasisCurve, ModelData_Point (0., 0., 0.), ModelData_Direction::XDir());
    return ModelData_Face (aSurface, 0., M_PI + M_PI_2, 0.1, 0.9);
}

static ModelData_Face MakeFaceFromOffsetSurface()
{
    array<ModelData_Point, 4> aPoles = {{
        ModelData_Point (0., 0.,  1.),
        ModelData_Point (0., 2.,  1.),
        ModelData_Point (2., 0.,  1.),
        ModelData_Point (2., 2., -1.)
    }};

    ModelData_BezierSurface aBasisSurface (aPoles.data(), 2, 2);

    ModelData_OffsetSurface aSurface (aBasisSurface, 10.);
    return ModelData_Face (aSurface, 0.1, 0.9, 0.1, 0.9);
}

static ModelData_Face MakeFaceFromBezier()
{
    array<ModelData_Point, 4> aPoles = {{
        ModelData_Point (0., 0.,  1.),
        ModelData_Point (0., 2.,  1.),
        ModelData_Point (2., 0.,  1.),
        ModelData_Point (2., 2., -1.)
    }};

    ModelData_BezierSurface aSurface (aPoles.data(), 2, 2);
    return ModelData_Face (aSurface, 0.25, 0.75, 0.25, 0.75);
}

static ModelData_Face MakeFaceFromBSpline()
{
    array<ModelData_Point, 25> aPoles = {{
        ModelData_Point ( 0.,  0., 1.),
        ModelData_Point ( 0.,  2., 3.),
        ModelData_Point ( 0.,  6., 2.),
        ModelData_Point ( 0.,  8., 3.),
        ModelData_Point ( 0., 10., 1.),

        ModelData_Point ( 2.,  0., 2.),
        ModelData_Point ( 2.,  2., 2.),
        ModelData_Point ( 2.,  6., 2.),
        ModelData_Point ( 2.,  8., 2.),
        ModelData_Point ( 2., 10., 2.),

        ModelData_Point ( 4.,  0., 3.),
        ModelData_Point ( 4.,  2., 1.),
        ModelData_Point ( 4.,  6., 2.),
        ModelData_Point ( 4.,  8., 1.),
        ModelData_Point ( 4., 10., 3.),

        ModelData_Point ( 6.,  0., 2.),
        ModelData_Point ( 6.,  2., 2.),
        ModelData_Point ( 6.,  6., 2.),
        ModelData_Point ( 6.,  8., 2.),
        ModelData_Point ( 6., 10., 2.),

        ModelData_Point ( 10.,  0., 3.),
        ModelData_Point ( 10.,  2., 1.),
        ModelData_Point ( 10.,  6., 2.),
        ModelData_Point ( 10.,  8., 1.),
        ModelData_Point ( 10., 10., 3.),
    }};

    int aUPoles = 5,
        aVPoles = 5;

    array<double, 4> aUKnots = {{0., 0.25, 0.75, 1.}},
                     aVKnots = {{0., 0.25, 0.75, 1.}};

    array<int, 4> aUMultiplicities = {{3, 1, 1, 3}},
                  aVMultiplicities = {{3, 1, 1, 3}};

    int aUDegree = 2;
    int aVDegree = 2;

    ModelData_BSplineSurface aSurface (aPoles.data(),
                                       aUPoles,                           aVPoles,
                                       aUKnots.data(),                    aVKnots.data(),
                                       static_cast<int> (aUKnots.size()), static_cast<int> (aVKnots.size()),
                                       aUMultiplicities.data(),           aVMultiplicities.data(),
                                       aUDegree,                          aVDegree);

    return ModelData_Face (aSurface, 0.25, 0.75, 0.25, 0.75);
}

static ModelData_Face MakeFaceWithInnerWire()
{
    ModelData_Axis2Placement anAxis2;
    ModelData_Circle anInnerCircle (anAxis2, 10.);
    ModelData_Circle anOuterCircle (anAxis2, 20.);

    ModelData_Wire anOuterWire, anInnerWire;
    ModelData_Edge anOuterEdge (anOuterCircle);
    ModelData_Edge anInnerEdge (anInnerCircle);

    anOuterWire.Append (anOuterEdge);
    anInnerWire.Append (ModelData_Edge::Cast (anInnerEdge.Reversed()));

    ModelData_Axis3Placement anAxis3 (anAxis2);
    ModelData_Plane aPlane (anAxis3);
    ModelData_Face aFace (aPlane);

    aFace.Append (anOuterWire);
    aFace.Append (anInnerWire);

    return aFace;
}
