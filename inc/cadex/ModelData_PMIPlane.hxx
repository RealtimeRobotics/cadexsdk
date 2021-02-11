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


#ifndef _ModelData_PMIPlane_HeaderFile
#define _ModelData_PMIPlane_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/ModelData_BaseObject.hxx>


namespace cadex {
class ModelData_Plane;

namespace internal {
class ModelData_PMIPlaneImpl;
}

class ModelData_PMIPlane : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_PMIPlaneImpl ImplType;

    __CADEX_EXPORT ModelData_PMIPlane();
    __CADEX_EXPORT explicit ModelData_PMIPlane (initialized);
    __CADEX_EXPORT explicit ModelData_PMIPlane (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIPlane (const ModelData_Plane& thePlane);
    __CADEX_EXPORT ModelData_PMIPlane (const ModelData_Plane& thePlane, const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT ModelData_Plane Plane() const;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif
