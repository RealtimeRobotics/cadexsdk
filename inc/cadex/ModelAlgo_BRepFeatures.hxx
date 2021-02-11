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


#ifndef _ModelAlgo_BRepFeatures_HeaderFile
#define _ModelAlgo_BRepFeatures_HeaderFile

#include <cadex/Base_Macro.hxx>

#ifndef _MATH_DEFINES_DEFINED
# ifndef _USE_MATH_DEFINES
#  define _USE_MATH_DEFINES
#  define __CADEX_DISABLE_MATH
# endif
#include <math.h>
#endif

#ifdef __CADEX_DISABLE_MATH
#undef __CADEX_DISABLE_MATH
#undef _USE_MATH_DEFINES
#endif


namespace cadex {
class ModelData_Axis1Placement;
class ModelData_Shape;
class ModelData_Vector;

class ModelAlgo_BRepFeatures
{
public:
    __CADEX_EXPORT static ModelData_Shape CreateExtrusion (const ModelData_Shape& theShape,
        const ModelData_Vector& theVec);


    __CADEX_EXPORT static ModelData_Shape CreateRevolution (const ModelData_Shape& theShape,
        const ModelData_Axis1Placement& theAxis,
        double theAngle = 2 * M_PI);
};


}

#endif
