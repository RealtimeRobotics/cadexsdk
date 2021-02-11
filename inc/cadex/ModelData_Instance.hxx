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


#ifndef _ModelData_Instance_HeaderFile
#define _ModelData_Instance_HeaderFile

#include <cadex/Base_UTF16String.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>

namespace cadex {
class ModelData_Transformation;

namespace internal {
class ModelData_InstanceImpl;
}

class ModelData_Instance : public ModelData_SceneGraphElement
{
public:

    typedef cadex::internal::ModelData_InstanceImpl    ImplType;

    __CADEX_EXPORT ModelData_Instance();
    __CADEX_EXPORT explicit ModelData_Instance (initialized);
    __CADEX_EXPORT explicit ModelData_Instance (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_Instance (const Base_UTF16String& theName);

    __CADEX_EXPORT explicit ModelData_Instance (const ModelData_SceneGraphElement& theElement,
        const Base_UTF16String& theName = Base_UTF16String());

    __CADEX_EXPORT ModelData_Instance (const ModelData_SceneGraphElement& theElement,
        const ModelData_Transformation& theTrsf,
        const Base_UTF16String& theName = Base_UTF16String());

    //! Sets a referenced object.
    __CADEX_EXPORT void SetReference (const ModelData_SceneGraphElement& theElement);

    __CADEX_EXPORT ModelData_SceneGraphElement Reference() const;

    __CADEX_EXPORT void SetTransformation (const ModelData_Transformation& theTrsf);

    __CADEX_EXPORT bool HasTransformation() const;

    __CADEX_EXPORT const ModelData_Transformation& Transformation() const;

    __CADEX_MODELDATA_DEFINE_TYPEID

private:
    friend class internal::ModelData_InstanceImpl;
};

}

#endif
