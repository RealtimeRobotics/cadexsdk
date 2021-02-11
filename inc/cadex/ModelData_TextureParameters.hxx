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


#ifndef _ModelData_TextureParameters_HeaderFile
#define _ModelData_TextureParameters_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_TEXTURES
#include <cadex/ModelData_BaseObject.hxx>
#include <cadex/ModelData_TextureBlendMode.hxx>
#include <cadex/ModelData_TextureMagnificationFilter.hxx>
#include <cadex/ModelData_TextureMappingMode.hxx>
#include <cadex/ModelData_TextureMinificationFilter.hxx>
#include <cadex/ModelData_TextureWrapMode.hxx>


namespace cadex {

namespace internal {
class ModelData_TextureParametersImpl;
}

class ModelData_TextureParameters : public ModelData_BaseObject
{
public:
    typedef cadex::internal::ModelData_TextureParametersImpl  ImplType;

    __CADEX_EXPORT ModelData_TextureParameters();
    __CADEX_EXPORT ModelData_TextureParameters (initialized);
    __CADEX_EXPORT ModelData_TextureParameters (ImplType* theImpl);

    __CADEX_EXPORT void SetGenerateMipmaps (bool theEnabled);
    __CADEX_EXPORT bool GenerateMipmaps() const;

    __CADEX_EXPORT void SetMagnificationFilter (ModelData_TextureMagnificationFilter theFilter);
    __CADEX_EXPORT ModelData_TextureMagnificationFilter MagnificationFilter() const;

    __CADEX_EXPORT void SetMinificationFilter (ModelData_TextureMinificationFilter theFilter);
    __CADEX_EXPORT ModelData_TextureMinificationFilter MinificationFilter() const;

    __CADEX_EXPORT void SetWrapMode (ModelData_TextureWrapMode theModeU, ModelData_TextureWrapMode theModeV);
    __CADEX_EXPORT ModelData_TextureWrapMode WrapModeU() const;
    __CADEX_EXPORT ModelData_TextureWrapMode WrapModeV() const;

    __CADEX_EXPORT void SetBlendMode (ModelData_TextureBlendMode theMode);
    __CADEX_EXPORT ModelData_TextureBlendMode BlendMode() const;

    __CADEX_EXPORT void SetMappingMode (ModelData_TextureMappingMode theMode);
    __CADEX_EXPORT ModelData_TextureMappingMode MappingMode() const;

    __CADEX_EXPORT void SetRotation (float theAngle);
    __CADEX_EXPORT float Rotation() const;

    __CADEX_EXPORT void SetScale (double theScaleU, double theScaleV);
    __CADEX_EXPORT double ScaleU() const;
    __CADEX_EXPORT double ScaleV() const;

    __CADEX_EXPORT void SetTranslation (double theTranslationU, double theTranslationV);
    __CADEX_EXPORT double TranslationU() const;
    __CADEX_EXPORT double TranslationV() const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};

__CADEX_EXPORT bool operator== (const ModelData_TextureParameters& theTP1, const ModelData_TextureParameters& theTP2);

}

#endif // __CADEX_PREVIEW_TEXTURES

#endif // _ModelData_TextureParameters_HeaderFile
