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

#ifndef _ModelData_ColorObject_HeaderFile
#define _ModelData_ColorObject_HeaderFile

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
class ModelData_Color;

namespace internal {
class ModelData_ColorObjectImpl;
}

class ModelData_ColorObject : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_ColorObjectImpl ImplType;

    __CADEX_EXPORT ModelData_ColorObject();
    __CADEX_EXPORT ModelData_ColorObject (initialized);
    __CADEX_EXPORT ModelData_ColorObject (ImplType* theImpl);

    __CADEX_EXPORT ModelData_ColorObject (const ModelData_Color& theValue);

    __CADEX_EXPORT const ModelData_Color& Value() const;
    __CADEX_EXPORT ModelData_Color& Value();

#ifndef SWIG
    // kept for source compatibility reasons
    __CADEX_EXPORT void Set (const ModelData_Color& theColor);
    __CADEX_EXPORT const ModelData_Color& Get() const;
#endif
    __CADEX_MODELDATA_DEFINE_TYPEID

};

__CADEX_EXPORT bool operator== (const ModelData_ColorObject& theColor1, const ModelData_ColorObject& theColor2);

class ModelData_ColorObjectHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_ColorObject& theColor) const;
};

}

#endif
