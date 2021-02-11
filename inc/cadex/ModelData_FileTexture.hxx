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


#ifndef _ModelData_FileTexture_HeaderFile
#define _ModelData_FileTexture_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_TEXTURES
#include <cadex/ModelData_Texture.hxx>

namespace cadex {

namespace internal {
class ModelData_FileTextureImpl;
}

class ModelData_FileTexture : public ModelData_Texture
{
public:

    typedef cadex::internal::ModelData_FileTextureImpl ImplType;

    __CADEX_EXPORT ModelData_FileTexture();
    __CADEX_EXPORT ModelData_FileTexture (initialized);
    __CADEX_EXPORT ModelData_FileTexture (ImplType* theImpl);
    __CADEX_EXPORT ModelData_FileTexture (const Base_UTF16String& theFilePath);

    __CADEX_EXPORT ModelData_FileTexture (const Base_UTF16String& theFilePath,
                                          ModelData_TextureType theTextureType);

    __CADEX_EXPORT ModelData_FileTexture (const Base_UTF16String& theFilePath,
                                          ModelData_TextureType theTextureType,
                                          const ModelData_TextureParameters& theParameters);

    __CADEX_EXPORT Base_UTF16String FilePath() const;
    __CADEX_EXPORT void SetFilePath (const Base_UTF16String& theFilePath);

    __CADEX_MODELDATA_DEFINE_TYPEID
};

__CADEX_EXPORT bool operator== (const ModelData_FileTexture& theFT1, const ModelData_FileTexture& theFT2);

}

#endif // __CADEX_PREVIEW_TEXTURES

#endif // _ModelData_FileTexture_HeaderFile
