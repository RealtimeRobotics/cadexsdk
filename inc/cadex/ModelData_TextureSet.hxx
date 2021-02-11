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


#ifndef _ModelData_TextureSet_HeaderFile
#define _ModelData_TextureSet_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_TEXTURES
#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
class ModelData_Texture;
class ModelData_TextureVisitor;

namespace internal {
class ModelData_TextureSetImpl;
}

class ModelData_TextureSet : public ModelData_BaseObject
{
public:
    typedef cadex::internal::ModelData_TextureSetImpl ImplType;

    __CADEX_EXPORT ModelData_TextureSet();
    __CADEX_EXPORT ModelData_TextureSet (initialized);
    __CADEX_EXPORT ModelData_TextureSet (ImplType* theImpl);

    __CADEX_EXPORT bool IsEmpty() const;

    __CADEX_EXPORT size_t NumberOfTextures() const;

    __CADEX_EXPORT bool Add (const ModelData_Texture& theTexture);

    __CADEX_EXPORT bool Remove (const ModelData_Texture& theTexture);

    __CADEX_EXPORT bool Contains (const ModelData_Texture& theTexture);

    __CADEX_EXPORT void Accept (ModelData_TextureVisitor& theVisitor) const;

    class TextureIterator
    {
    public:
        __CADEX_EXPORT explicit TextureIterator (const ModelData_TextureSet& theSet);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_Texture& Next() const;
        __CADEX_EXPORT ModelData_Texture& Next();
    private:
        internal::Base_Handle myImpl;
    };

    __CADEX_MODELDATA_DEFINE_TYPEID
};

__CADEX_EXPORT bool operator== (const ModelData_TextureSet& theTS1, const ModelData_TextureSet& theTS2);

class ModelData_TextureSetHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_TextureSet& theSet) const;
};

}

#endif // __CADEX_PREVIEW_TEXTURES

#endif // _ModelData_TextureSet_HeaderFile
