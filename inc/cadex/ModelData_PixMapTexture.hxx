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


#ifndef _ModelData_PixMapTexture_HeaderFile
#define _ModelData_PixMapTexture_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_TEXTURES
#include <cadex/ModelData_Texture.hxx>

namespace cadex {

class ModelData_PixMap;

namespace internal {
class ModelData_PixMapTextureImpl;
}

class ModelData_PixMapTexture : public ModelData_Texture
{
public:

    typedef cadex::internal::ModelData_PixMapTextureImpl ImplType;

    __CADEX_EXPORT ModelData_PixMapTexture();
    __CADEX_EXPORT ModelData_PixMapTexture (initialized);
    __CADEX_EXPORT ModelData_PixMapTexture (ImplType* theImpl);

    __CADEX_EXPORT ModelData_PixMapTexture (const ModelData_PixMap& thePixMap);

    __CADEX_EXPORT ModelData_PixMapTexture (const ModelData_PixMap& thePixMap,
                                            ModelData_TextureType theTextureType);

    __CADEX_EXPORT ModelData_PixMapTexture (const ModelData_PixMap& thePixMap,
                                            ModelData_TextureType theTextureType,
                                            const ModelData_TextureParameters& theParameters);

    __CADEX_EXPORT ModelData_PixMap PixMap() const;
    __CADEX_EXPORT void SetPixMap (const ModelData_PixMap& thePixMap);

    __CADEX_MODELDATA_DEFINE_TYPEID
};

__CADEX_EXPORT bool operator== (const ModelData_PixMapTexture& thePT1, const ModelData_PixMapTexture& thePT2);

}

#endif // __CADEX_PREVIEW_TEXTURES

#endif // _ModelData_PixMapTexture_HeaderFile
