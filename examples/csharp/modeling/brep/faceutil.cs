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

namespace brep
{
    class faceutil
    {
        static public ModelData_Axis3Placement a3Axis = new ModelData_Axis3Placement();

        static public ModelData_Face MakePlanarFace()
        {
            ModelData_Plane aSurface = new ModelData_Plane(a3Axis);
            return new ModelData_Face(aSurface, -2.0, 2.0, -2.0, 2.0);
        }

        static public ModelData_Face MakeSphericalFace()
        {
            ModelData_SphericalSurface aSurface = new ModelData_SphericalSurface(a3Axis, 10.0);
            return new ModelData_Face(aSurface, 0.0, Math.PI / 2, 0.0, Math.PI / 2);
        }

        static public ModelData_Face MakeCylindricalFace()
        {
            ModelData_CylindricalSurface aSurface = new ModelData_CylindricalSurface(a3Axis, 10.0);
            return new ModelData_Face(aSurface, 0.0, Math.PI, -2.0, 2.0);
        }

        static public ModelData_Face MakeConicalFace()
        {
            ModelData_ConicalSurface aSurface = new ModelData_ConicalSurface(a3Axis, 1.0, 7.0);
            return new ModelData_Face(aSurface, 0.0, Math.PI, 0.0, Math.PI);
        }

        static public ModelData_Face MakeToroidalFace()
        {
            ModelData_ToroidalSurface aSurface = new ModelData_ToroidalSurface(a3Axis, 7.0, 3.0);
            return new ModelData_Face(aSurface, 0.0, Math.PI, 0.0, Math.PI);
        }

        static public ModelData_Face MakeFaceFromSurfaceOfLinearExtrusion()
        {
            ModelData_Point[] aPoles = {
                new ModelData_Point (-2.0,  1.0, 0.0),
                new ModelData_Point (-1.0, -1.0, 0.0),
                new ModelData_Point ( 0.0,  1.0, 0.0),
                new ModelData_Point ( 1.0, -1.0, 0.0),
                new ModelData_Point ( 2.0,  1.0, 0.0)
            };

            ModelData_BezierCurve aBasisCurve = new ModelData_BezierCurve(aPoles);

            ModelData_SurfaceOfLinearExtrusion aSurface = new ModelData_SurfaceOfLinearExtrusion(aBasisCurve, ModelData_Direction.ZDir());
            return new ModelData_Face(aSurface, 0.1, 0.9, -10.0, 10.0);
        }

        static public ModelData_Face MakeFaceFromSurfaceOfRevolution()
        {
            ModelData_Point[] aPoles = {
                new ModelData_Point (-2.0, 1.0, 0.0),
                new ModelData_Point (-1.0, 3.0, 0.0),
                new ModelData_Point ( 0.0, 2.0, 0.0),
                new ModelData_Point ( 1.0, 1.0, 0.0),
                new ModelData_Point ( 2.0, 2.0, 0.0)
            };

            ModelData_BezierCurve aBasisCurve = new ModelData_BezierCurve(aPoles);

            ModelData_SurfaceOfRevolution aSurface = new ModelData_SurfaceOfRevolution(aBasisCurve, new ModelData_Point(0.0, 0.0, 0.0), ModelData_Direction.XDir());
            return new ModelData_Face(aSurface, 0.0, Math.PI + Math.PI / 2, 0.1, 0.9);
        }

        static public ModelData_Face MakeFaceFromOffsetSurface()
        {
            ModelData_Point[] aPoles = {
                new ModelData_Point (0.0, 0.0,  1.0),
                new ModelData_Point (0.0, 2.0,  1.0),
                new ModelData_Point (2.0, 0.0,  1.0),
                new ModelData_Point (2.0, 2.0, -1.0)
            };

            ModelData_BezierSurface aBasisSurface = new ModelData_BezierSurface(aPoles, 2, 2);
            ModelData_OffsetSurface aSurface = new ModelData_OffsetSurface(aBasisSurface, 10.0);
            return new ModelData_Face(aSurface, 0.1, 0.9, 0.1, 0.9);
        }

        static public ModelData_Face MakeFaceFromBezier()
        {
            ModelData_Point[] aPoles = {
                new ModelData_Point (0.0, 0.0,  1.0),
                new ModelData_Point (0.0, 2.0,  1.0),
                new ModelData_Point (2.0, 0.0,  1.0),
                new ModelData_Point (2.0, 2.0, -1.0)
            };

            ModelData_BezierSurface aSurface = new ModelData_BezierSurface(aPoles, 2, 2);
            return new ModelData_Face(aSurface, 0.25, 0.75, 0.25, 0.75);
        }

        static public ModelData_Face MakeFaceFromBSpline()
        {
            ModelData_Point[] aPoles = {
                new ModelData_Point ( 0.0,  0.0, 1.0),
                new ModelData_Point ( 0.0,  2.0, 3.0),
                new ModelData_Point ( 0.0,  6.0, 2.0),
                new ModelData_Point ( 0.0,  8.0, 3.0),
                new ModelData_Point ( 0.0, 10.0, 1.0),

                new ModelData_Point ( 2.0,  0.0, 2.0),
                new ModelData_Point ( 2.0,  2.0, 2.0),
                new ModelData_Point ( 2.0,  6.0, 2.0),
                new ModelData_Point ( 2.0,  8.0, 2.0),
                new ModelData_Point ( 2.0, 10.0, 2.0),

                new ModelData_Point ( 4.0,  0.0, 3.0),
                new ModelData_Point ( 4.0,  2.0, 1.0),
                new ModelData_Point ( 4.0,  6.0, 2.0),
                new ModelData_Point ( 4.0,  8.0, 1.0),
                new ModelData_Point ( 4.0, 10.0, 3.0),

                new ModelData_Point ( 6.0,  0.0, 2.0),
                new ModelData_Point ( 6.0,  2.0, 2.0),
                new ModelData_Point ( 6.0,  6.0, 2.0),
                new ModelData_Point ( 6.0,  8.0, 2.0),
                new ModelData_Point ( 6.0, 10.0, 2.0),

                new ModelData_Point (10.0,  0.0, 3.0),
                new ModelData_Point (10.0,  2.0, 1.0),
                new ModelData_Point (10.0,  6.0, 2.0),
                new ModelData_Point (10.0,  8.0, 1.0),
                new ModelData_Point (10.0, 10.0, 3.0)
            };

            int aUPoles = 5;
            int aVPoles = 5;

            double[] aUKnots = { 0.0, 0.25, 0.75, 1.0 };
            double[] aVKnots = { 0.0, 0.25, 0.75, 1.0 };

            int[] aVMultiplicities = { 3, 1, 1, 3 };
            int[] aUMultiplicities = { 3, 1, 1, 3 };

            int aUDegree = 2;
            int aVDegree = 2;

            ModelData_BSplineSurface aSurface = new ModelData_BSplineSurface(aPoles, aUPoles, aVPoles, aUKnots, aVKnots,
                                                                              aUMultiplicities, aVMultiplicities,
                                                                              aUDegree, aVDegree);
            return new ModelData_Face(aSurface, 0.25, 0.75, 0.25, 0.75);
        }

        static public ModelData_Face MakeFaceWithInnerWire()
        {
            ModelData_Axis2Placement anAxis2 = new ModelData_Axis2Placement();
            ModelData_Circle anInnerCircle = new ModelData_Circle(anAxis2, 10.0);
            ModelData_Circle anOuterCircle = new ModelData_Circle(anAxis2, 20.0);

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
}
