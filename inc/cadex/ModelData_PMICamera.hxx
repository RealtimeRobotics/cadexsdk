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


#ifndef _ModelData_PMICamera_HeaderFile
#define _ModelData_PMICamera_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/ModelData_BaseObject.hxx>


namespace cadex {
class ModelData_Direction;
class ModelData_Point;

namespace internal {
class ModelData_PMICameraImpl;
}

class ModelData_PMICamera : public ModelData_BaseObject
{
public:
    typedef cadex::internal::ModelData_PMICameraImpl    ImplType;

    __CADEX_EXPORT ModelData_PMICamera();
    __CADEX_EXPORT explicit ModelData_PMICamera (initialized);
    __CADEX_EXPORT ModelData_PMICamera (const ModelData_Point& theLocation,
        const ModelData_Point& theTargetPoint,
        const ModelData_Direction& theUpDirection);
    __CADEX_EXPORT ModelData_PMICamera (const ModelData_Point& theLocation,
        const ModelData_Point& theTargetPoint,
        const ModelData_Direction& theUpDirection,
        const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetLocation (const ModelData_Point& theLocation);
    __CADEX_EXPORT const ModelData_Point& Location() const;

    __CADEX_EXPORT void SetTargetPoint (const ModelData_Point& theTargetPoint);
    __CADEX_EXPORT const ModelData_Point& TargetPoint() const;

    __CADEX_EXPORT void SetUpDirection (const ModelData_Direction& theUpDirection);
    __CADEX_EXPORT const ModelData_Direction& UpDirection() const;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif
