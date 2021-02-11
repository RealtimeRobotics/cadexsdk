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

#ifndef _ModelPrs_View3dObject_HeaderFile
#define _ModelPrs_View3dObject_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION

#include <cadex/Base_Handle.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC (AIS_InteractiveObject)

namespace cadex {
class ModelData_Appearance;
class ModelData_Transformation;

namespace internal {
class ModelPrs_View3dObjectImpl;
}

class ModelPrs_View3dObject
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor (create null object)
    __CADEX_EXPORT ModelPrs_View3dObject();

    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE (ModelPrs_View3dObject, AIS_InteractiveObject);

    __CADEX_EXPORT void Nullify();

    __CADEX_EXPORT bool IsNull() const;

    __CADEX_EXPORT bool IsSame (const ModelPrs_View3dObject& theObject) const;

    __CADEX_EXPORT ModelData_Transformation LocalTransformation() const;
    __CADEX_EXPORT void SetLocalTransformation (const ModelData_Transformation& theTrsf);

    __CADEX_EXPORT void SetAppearance (const ModelData_Appearance& theAppearance);

    operator bool() const { return !IsNull(); }

    __CADEX_EXPORT internal::ModelPrs_View3dObjectImpl* Impl() const;

    const internal::Base_Handle& HImpl() const { return myImpl; }

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast<T*> (Impl()); }

protected:
    cadex::internal::Base_Handle    myImpl;
};

inline bool operator== (const ModelPrs_View3dObject& theO1, const ModelPrs_View3dObject& theO2)
{
    return theO1.HImpl() == theO2.HImpl();
}

inline bool operator!= (const ModelPrs_View3dObject& theO1, const ModelPrs_View3dObject& theO2)
{
    return theO1.HImpl() != theO2.HImpl();
}

class ModelPrs_View3dObjectHash
{
public:
    size_t operator() (const ModelPrs_View3dObject& theValue) const
    { return internal::Base_HandleHash() (theValue.HImpl()); }
};

}


#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExViewd.lib")
        #else
            #pragma comment(lib, "CadExView.lib")
        #endif
    #endif
#endif

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_View3dObject_HeaderFile
