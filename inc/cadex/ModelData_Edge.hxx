// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// This file may be used under the terms and conditions of the License
// Agreement supplied with the software.
//
// This file is provided "AS IS" WITH NO WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE WARRANTY OF DESIGN,
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// ****************************************************************************


#ifndef _ModelData_Edge_HeaderFile
#define _ModelData_Edge_HeaderFile

#include <cadex/ModelData_Shape.hxx>

class TopoDS_Edge;

namespace cadex {

class ModelData_Curve;
class ModelData_Curve2d;
class ModelData_Point;

class ModelData_Face;
class ModelData_Vertex;

class ModelData_Edge : public ModelData_Shape
{
public:

    ModelData_Edge() {}

#ifndef __CADEX_DOXYGEN
    __CADEX_EXPORT ModelData_Edge (const ModelData_Curve& theCurve);

    __CADEX_EXPORT ModelData_Edge (const ModelData_Curve& theCurve, double theFirstParameter, double theLastParameter);

    __CADEX_EXPORT ModelData_Edge (const ModelData_Curve& theCurve,
        const ModelData_Vertex& theStartVertex,
        const ModelData_Vertex& theEndVertex);

    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(ModelData_Edge, TopoDS_Edge)
#endif

    __CADEX_EXPORT ModelData_Edge (const ModelData_Vertex& theStartVertex, const ModelData_Vertex& theEndVertex);

    __CADEX_EXPORT void SetCurve (const ModelData_Curve& theCurve,
        double theFirstParameter,
        double theLastParameter);

    __CADEX_EXPORT bool SetCurve (const ModelData_Curve& theCurve);

    __CADEX_EXPORT void SetPCurve (const ModelData_Curve2d& thePCurve,
        const ModelData_Face& theFace,
        double theFirstParameter,
        double theLastParameter);

    __CADEX_EXPORT bool SetPCurve (const ModelData_Curve2d& thePCurve, const ModelData_Face& theFace);

    __CADEX_EXPORT void SetPCurve (const ModelData_Curve2d& thePCurveForward,
        const ModelData_Curve2d& thePCurveReversed,
        const ModelData_Face& theFace,
        double theFirstParameter,
        double theLastParameter);

    __CADEX_EXPORT bool SetPCurve (const ModelData_Curve2d& thePCurveForward,
        const ModelData_Curve2d& thePCurveReversed,
        const ModelData_Face& theFace);

    __CADEX_EXPORT ModelData_Vertex StartVertex() const;

    __CADEX_EXPORT ModelData_Vertex EndVertex() const;

    __CADEX_EXPORT ModelData_Curve Curve (double& theFirstParameter, double& theLastParameter) const;

    __CADEX_EXPORT ModelData_Curve2d PCurve (const ModelData_Face& theFace,
        double& theFirstParameter,
        double& theLastParameter) const;

    __CADEX_EXPORT void SetTolerance (double theTolerance);

    __CADEX_EXPORT double Tolerance() const;
    
    __CADEX_EXPORT bool IsDegenerated() const;
    __CADEX_EXPORT bool IsSeam (const ModelData_Face& theFace) const;

    __CADEX_EXPORT static const ModelData_Edge& Cast (const ModelData_Shape& theShape);

    __CADEX_EXPORT static ModelData_Edge& Cast (ModelData_Shape& theShape);
};

}

#endif
