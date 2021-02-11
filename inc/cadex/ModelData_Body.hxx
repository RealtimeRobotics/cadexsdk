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


#ifndef _ModelData_Body_HeaderFile
#define _ModelData_Body_HeaderFile

#include <cadex/ModelData_BodyType.hxx>
#include <cadex/ModelData_Shape.hxx>

namespace cadex {

class ModelData_Body : public ModelData_Shape
{
public:
    ModelData_Body() {}

    __CADEX_EXPORT ModelData_BodyType BodyType() const;

    __CADEX_EXPORT static ModelData_Body Create (const ModelData_Shape& theShape);

    __CADEX_EXPORT bool Append (const ModelData_Shape& theShape);

    __CADEX_EXPORT static const ModelData_Body& Cast (const ModelData_Shape& theShape);

    __CADEX_EXPORT static ModelData_Body& Cast (ModelData_Shape& theShape);

private:

    __CADEX_EXPORT ModelData_Body (const TopoDS_Shape& theOther, ModelData_BodyType theBodyType);

    friend class ModelData_ShapeFactory;
};

}

#endif
