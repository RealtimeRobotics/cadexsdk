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


#ifndef _ModelData_MaterialObject_HeaderFile
#define _ModelData_MaterialObject_HeaderFile

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
class ModelData_Color;
class ModelData_Material;

namespace internal {
class ModelData_MaterialObjectImpl;
}

class ModelData_MaterialObject : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_MaterialObjectImpl  ImplType;

    __CADEX_EXPORT ModelData_MaterialObject();
    __CADEX_EXPORT ModelData_MaterialObject (initialized);
    __CADEX_EXPORT ModelData_MaterialObject (ImplType* theImpl);
    __CADEX_EXPORT ModelData_MaterialObject (const ModelData_Material& theValue);

    __CADEX_EXPORT const ModelData_Material& Value() const;
    __CADEX_EXPORT ModelData_Material& Value();

#ifndef SWIG
    //the below methods are kept for for source compatibility
    __CADEX_EXPORT void SetAmbientColor (const ModelData_Color& theColor);
    __CADEX_EXPORT const ModelData_Color& AmbientColor() const;

    __CADEX_EXPORT void SetDiffuseColor (const ModelData_Color& theColor);
    __CADEX_EXPORT const ModelData_Color& DiffuseColor() const;

    __CADEX_EXPORT void SetSpecularColor (const ModelData_Color& theColor);
    __CADEX_EXPORT const ModelData_Color& SpecularColor() const;

    __CADEX_EXPORT void SetEmissionColor (const ModelData_Color& theColor);
    __CADEX_EXPORT const ModelData_Color& EmissionColor() const;

    //! Sets shininess.
    /*! \a theValue must be in the [0, 128] range.*/
    __CADEX_EXPORT void SetShininess (const float theValue);
    __CADEX_EXPORT float Shininess() const;
#endif

    __CADEX_MODELDATA_DEFINE_TYPEID
};

__CADEX_EXPORT bool operator== (const ModelData_MaterialObject& theO1, const ModelData_MaterialObject& theO2);

class ModelData_MaterialObjectHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_MaterialObject& theMaterial) const;
};

}

#endif
