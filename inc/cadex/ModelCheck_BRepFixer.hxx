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


#ifndef _ModelCheck_BRepFixer_HeaderFile
#define _ModelCheck_BRepFixer_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <memory>


namespace cadex {

class ModelData_BRepRepresentation;
class ModelData_Shape;

namespace internal {
class ModelCheck_BRepFixerImpl;
}

class ModelCheck_BRepFixer
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelCheck_BRepFixer();

    __CADEX_EXPORT bool Fix (ModelData_Shape& theShape);
    __CADEX_EXPORT bool Fix (ModelData_BRepRepresentation& theRep);

    __CADEX_DEFINE_IMPL (ModelCheck_BRepFixer)
};

}

#endif
