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


#ifndef _ModelData_Shell_HeaderFile
#define _ModelData_Shell_HeaderFile

#include <cadex/ModelData_Shape.hxx>

class TopoDS_Shell;

namespace cadex {

class ModelData_Face;

class ModelData_Shell : public ModelData_Shape
{
public:

    ModelData_Shell() {}

    __CADEX_EXPORT ModelData_Shell (const ModelData_Face& theFace);

    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(ModelData_Shell, TopoDS_Shell)

    __CADEX_EXPORT bool Append (const ModelData_Face& theFace);

    __CADEX_EXPORT static const ModelData_Shell& Cast (const ModelData_Shape& theShape);

    __CADEX_EXPORT static ModelData_Shell& Cast (ModelData_Shape& theShape);
};

}

#endif
