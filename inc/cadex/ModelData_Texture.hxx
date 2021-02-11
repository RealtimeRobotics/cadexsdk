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


#ifndef _ModelData_Texture_HeaderFile
#define _ModelData_Texture_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_TEXTURES
#include <cadex/ModelData_BaseObject.hxx>
#include <cadex/ModelData_TextureType.hxx>

namespace cadex {

class ModelData_TextureVisitor;
class ModelData_TextureParameters;

namespace internal {
class ModelData_TextureImpl;
}

class ModelData_Texture : public ModelData_BaseObject
{
public:
    typedef cadex::internal::ModelData_TextureImpl ImplType;

    __CADEX_EXPORT ModelData_Texture();

    __CADEX_EXPORT ModelData_TextureType Type() const;
    __CADEX_EXPORT void SetType (ModelData_TextureType theType);

    __CADEX_EXPORT ModelData_TextureParameters Parameters() const;
    __CADEX_EXPORT void SetParameters (const ModelData_TextureParameters& theParameters);

    __CADEX_EXPORT void Accept (ModelData_TextureVisitor& theVisitor) const;

protected:
    ModelData_Texture (ImplType* theImpl);
};

}

#endif // __CADEX_PREVIEW_TEXTURES

#endif // _ModelData_Texture_HeaderFile
