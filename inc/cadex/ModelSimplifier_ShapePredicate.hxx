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


#ifndef _ModelSimplifier_ShapePredicate_HeaderFile
#define _ModelSimplifier_ShapePredicate_HeaderFile

#include <cadex/ModelData_Shape.hxx>

namespace cadex {

class ModelSimplifier_ShapePredicate
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    virtual bool CanSimplifyShape (const ModelData_Shape& theShape) = 0;
    virtual bool CanSplitShape (const ModelData_Shape& theShape) = 0;
    virtual ~ModelSimplifier_ShapePredicate();

};

}
#endif
