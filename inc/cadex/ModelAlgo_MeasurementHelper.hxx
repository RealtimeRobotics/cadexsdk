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


#ifndef _ModelAlgo_MeasurementHelper_HeaderFile
#define _ModelAlgo_MeasurementHelper_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_Circle.hxx>
#include <cadex/ModelData_Point.hxx>

#include <array>

class TopoDS_Edge;
class TopoDS_Face;

namespace cadex {
class ModelData_Face;
class ModelData_Shape;
class ModelData_Vertex;

namespace internal {

class ModelAlgo_MeasurementHelper
{
public:
    typedef std::pair<double, double>                        RadiiType;
    typedef std::pair<ModelData_Point, ModelData_Point>      AnchorPointsType;
    typedef std::pair<ModelData_Circle, ModelData_Circle>    CirclesType;

    __CADEX_EXPORT static bool IsCircle (const TopoDS_Edge& theEdge);

    __CADEX_EXPORT static bool IsPlanar (const TopoDS_Face& theFace);

    __CADEX_EXPORT static bool IsRadialSurface (const TopoDS_Face& theFace);

    __CADEX_EXPORT static bool Angle (const ModelData_Vertex& theFirstVertex,
                                      const ModelData_Vertex& theSecondVertex,
                                      const ModelData_Vertex& theThirdVertex,
                                      double& theAngle);

    __CADEX_EXPORT static bool Angle (const ModelData_Face& theFirstFace,
                                      const ModelData_Face& theSecondFace,
                                      double& theAngle);

    __CADEX_EXPORT static bool Distance (const ModelData_Shape& theFirstShape,
                                         const ModelData_Shape& theSecondShape,
                                         double& theDistance,
                                         AnchorPointsType& theAnchorPoints);


    __CADEX_EXPORT static bool Diameter (const ModelData_Shape& theShape,
                                         RadiiType& theRadii,
                                         CirclesType& theCircles,
                                         AnchorPointsType& theAnchorPoints);

    __CADEX_EXPORT static bool Radius (const ModelData_Shape& theShape,
                                       RadiiType& theRadii,
                                       CirclesType& theCircles,
                                       AnchorPointsType& theAnchorPoints);

    __CADEX_EXPORT static bool Length (const ModelData_Shape& theShape, double& theLength);
};

}}

#endif // _ModelAlgo_MeasurementHelper_HeaderFile
