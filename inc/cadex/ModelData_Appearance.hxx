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


#ifndef _ModelData_Appearance_HeaderFile
#define _ModelData_Appearance_HeaderFile

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {

class ModelData_Color;
class ModelData_LineProperties;
class ModelData_Material;
class ModelData_ColorObject;
class ModelData_MaterialObject;
class ModelData_TextureSet;
class ModelData_Texture;

namespace internal {
class ModelData_AppearanceImpl;
}

class ModelData_Appearance : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_AppearanceImpl  ImplType;

    __CADEX_EXPORT ModelData_Appearance();
    __CADEX_EXPORT ModelData_Appearance (initialized);
    __CADEX_EXPORT ModelData_Appearance (ImplType* theImpl);

    __CADEX_EXPORT ModelData_Appearance (const ModelData_Color& theGenericColor);
    __CADEX_EXPORT ModelData_Appearance (const ModelData_ColorObject& theGenericColor);

    __CADEX_EXPORT ModelData_Appearance (const ModelData_Material& theMaterial);
    __CADEX_EXPORT ModelData_Appearance (const ModelData_MaterialObject& theMaterial);

    __CADEX_EXPORT void Set (const ModelData_Color& theGenericColor);
    __CADEX_EXPORT void Set (const ModelData_ColorObject& theGenericColor);
    __CADEX_EXPORT ModelData_ColorObject GenericColor() const;

    __CADEX_EXPORT void Set (const ModelData_Material& theMaterial);
    __CADEX_EXPORT void Set (const ModelData_MaterialObject& theMaterial);
    __CADEX_EXPORT ModelData_MaterialObject Material() const;

    __CADEX_EXPORT bool ToColor (ModelData_Color& theColor) const;
    __CADEX_EXPORT bool ToMaterial (ModelData_Material& theMaterial) const;

    __CADEX_EXPORT bool HasLineProperties() const;
    __CADEX_EXPORT void Set (const ModelData_LineProperties& theValue);
    __CADEX_EXPORT const ModelData_LineProperties& LineProperties() const;

#if __CADEX_PREVIEW_TEXTURES
    __CADEX_EXPORT void SetTextureSet (const ModelData_TextureSet& theTextureSet);
    __CADEX_EXPORT void Add (const ModelData_Texture& theTexture);
    __CADEX_EXPORT ModelData_TextureSet TextureSet() const;
#endif

    __CADEX_EXPORT void CopyAndOverrideWith (const ModelData_Appearance& theOther);
    __CADEX_EXPORT void CopyAndCombineWith (const ModelData_Appearance& theOther);

    __CADEX_MODELDATA_DEFINE_TYPEID
};

__CADEX_EXPORT bool operator== (const ModelData_Appearance& theA1, const ModelData_Appearance& theA2);

class ModelData_AppearanceHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Appearance& theAppearance) const;
};

}

#endif
