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


#ifndef _ModelData_ShapeFactory_HeaderFile
#define _ModelData_ShapeFactory_HeaderFile

#include <cadex/Base_Macro.hxx>

class TopoDS_Shape;

namespace cadex {

class ModelData_BodyList;
class ModelData_Shape;

class ModelData_ShapeFactory
{
public:

    //! Creates a shape that corresponds to the source.
    __CADEX_EXPORT static ModelData_Shape Create (const TopoDS_Shape& theSource);

    //! Creates a body or body list that corresponds to the source.
    __CADEX_EXPORT static ModelData_Shape CreateRoot (const TopoDS_Shape& theSource);

    //! Creates a body list from the source.
    __CADEX_EXPORT static ModelData_BodyList CreateBodyList (const TopoDS_Shape& theSource);
};

}

#endif
