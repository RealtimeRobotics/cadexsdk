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


#ifndef _ModelAlgo_TopoPrimitives_HeaderFile
#define _ModelAlgo_TopoPrimitives_HeaderFile

#include <cadex/ModelData_Axis2Placement.hxx>
#include <cadex/ModelData_Point.hxx>
#include <cadex/ModelData_Solid.hxx>

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

class ModelAlgo_TopoPrimitives
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT


    __CADEX_EXPORT static ModelData_Solid CreateBox (double theDx, double theDy, double theDz);
    
    __CADEX_EXPORT static ModelData_Solid CreateBox (const ModelData_Point& theMinPoint,
        double theDx,
        double theDy,
        double theDz);
    
    __CADEX_EXPORT static ModelData_Solid CreateBox (const ModelData_Point& theMinPoint,
        const ModelData_Point& theMaxPoint);

    __CADEX_EXPORT static ModelData_Solid CreateBox (const ModelData_Axis2Placement& theAxis,
        double theDx,
        double theDy,
        double theDz);


    __CADEX_EXPORT static ModelData_Solid CreateSphere (double theRadius,
        double theU = 2 * M_PI,
        double theVmin = -M_PI_2,
        double theVmax = M_PI_2);

    __CADEX_EXPORT static ModelData_Solid CreateSphere (const ModelData_Point& theCenter, 
        double theRadius,
        double theU = 2 * M_PI,
        double theVmin = -M_PI_2,
        double theVmax = M_PI_2);

    __CADEX_EXPORT static ModelData_Solid CreateSphere (const ModelData_Axis2Placement& theAxis, 
        double theRadius,
        double theU = 2 * M_PI,
        double theVmin = -M_PI_2,
        double theVmax = M_PI_2);


    __CADEX_EXPORT static ModelData_Solid CreateCylinder (double theRadius,
        double theHeight,
        double theAngle = 2 * M_PI);

    __CADEX_EXPORT static ModelData_Solid CreateCylinder (const ModelData_Axis2Placement& theAxis,
        double theRadius,
        double theHeight,
        double theAngle = 2 * M_PI);


    __CADEX_EXPORT static ModelData_Solid CreateCone (double theRadius1,
        double theRadius2,
        double theHeight,
        double theAngle = 2 * M_PI);
 
    __CADEX_EXPORT static ModelData_Solid CreateCone (const ModelData_Axis2Placement& theAxis,
        double theRadius1,
        double theRadius2,
        double theHeight,
        double theAngle = 2 * M_PI);


    __CADEX_EXPORT static ModelData_Solid CreateTorus (double theRadius1,
        double theRadius2,
        double theU = 2 * M_PI,
        double theVmin = 0.,
        double theVmax = 2 * M_PI);

    __CADEX_EXPORT static ModelData_Solid CreateTorus (const ModelData_Axis2Placement& theAxis,
        double theRadius1,
        double theRadius2,
        double theU = 2 * M_PI,
        double theVmin = 0.,
        double theVmax = 2 * M_PI);
};


}

#endif
