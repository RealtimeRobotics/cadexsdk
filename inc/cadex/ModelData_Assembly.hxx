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


#ifndef _ModelData_Assembly_HeaderFile
#define _ModelData_Assembly_HeaderFile

#include <cadex/ModelData_SceneGraphElement.hxx>

namespace cadex {

class ModelData_Transformation;

namespace internal {
class ModelData_AssemblyImpl;
}

class ModelData_Assembly : public ModelData_SceneGraphElement
{
public:

    typedef cadex::internal::ModelData_AssemblyImpl    ImplType;

    __CADEX_EXPORT ModelData_Assembly();
    __CADEX_EXPORT explicit ModelData_Assembly (initialized);
    __CADEX_EXPORT explicit ModelData_Assembly (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_Assembly (const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT const ModelData_Instance& AddInstance (const ModelData_SceneGraphElement& theElement,
        const Base_UTF16String& theInstanceName = Base_UTF16String());
    __CADEX_EXPORT const ModelData_Instance& AddInstance (const ModelData_SceneGraphElement& theElement,
        const ModelData_Transformation& theTransformation,
        const Base_UTF16String& theInstanceName = Base_UTF16String());
    __CADEX_EXPORT void AddInstance (const ModelData_Instance& theInstance);

    __CADEX_EXPORT bool RemoveInstance (const ModelData_Instance& theInstance);

    __CADEX_EXPORT size_t NumberOfInstances() const;

private:
    friend class internal::ModelData_AssemblyImpl;
};

}

#endif
