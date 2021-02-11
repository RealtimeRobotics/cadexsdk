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


#ifndef _ModelData_Axis2Placement2d_HeaderFile
#define _ModelData_Axis2Placement2d_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>

class gp_Ax22d;

namespace cadex {

class ModelData_Direction2d;
class ModelData_Point2d;

class ModelData_Axis2Placement2d
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelData_Axis2Placement2d ();

    __CADEX_EXPORT ModelData_Axis2Placement2d (const ModelData_Point2d& theLocation,
        const ModelData_Direction2d& theRefDirection,
        bool theCCW = true);

    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(ModelData_Axis2Placement2d, gp_Ax22d)

    __CADEX_EXPORT const ModelData_Point2d& Location() const;
    __CADEX_EXPORT const ModelData_Direction2d& XDirection() const;
    __CADEX_EXPORT const ModelData_Direction2d& YDirection() const;

protected:
    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof (double) * 6, double)
};

}

#endif
