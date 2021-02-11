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


#ifndef _ModelData_Wire_HeaderFile
#define _ModelData_Wire_HeaderFile

#include <cadex/ModelData_Shape.hxx>

class TopoDS_Wire;

namespace cadex {

class ModelData_Edge;

class ModelData_Wire : public ModelData_Shape
{
public:

    ModelData_Wire() {}

    __CADEX_EXPORT ModelData_Wire (const ModelData_Edge& theEdge);

    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(ModelData_Wire, TopoDS_Wire)

    __CADEX_EXPORT bool Append (const ModelData_Edge& theEdge);

    __CADEX_EXPORT static const ModelData_Wire& Cast (const ModelData_Shape& theShape);

    __CADEX_EXPORT static ModelData_Wire& Cast (ModelData_Shape& theShape);
};

}

#endif
