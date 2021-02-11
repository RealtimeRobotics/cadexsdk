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


#ifndef _ModelData_Vertex_HeaderFile
#define _ModelData_Vertex_HeaderFile

#include <cadex/ModelData_Shape.hxx>

class TopoDS_Vertex;

namespace cadex {

class ModelData_Point;

class ModelData_Vertex : public ModelData_Shape
{
public:

    ModelData_Vertex() {}

    __CADEX_EXPORT explicit ModelData_Vertex (const ModelData_Point& thePoint);

    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(ModelData_Vertex, TopoDS_Vertex)

    __CADEX_EXPORT ModelData_Point Point() const;

    __CADEX_EXPORT void SetTolerance (double theTolerance);

    __CADEX_EXPORT double Tolerance() const;

    __CADEX_EXPORT static const ModelData_Vertex& Cast (const ModelData_Shape& theShape);

    __CADEX_EXPORT static ModelData_Vertex& Cast (ModelData_Shape& theShape);
};

}

#endif
