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


#ifndef _ModelData_PixMap_HeaderFile
#define _ModelData_PixMap_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_TEXTURES
#include <cadex/ModelData_BaseObject.hxx>
#include <cadex/ModelData_PixelFormat.hxx>

namespace cadex {

namespace internal {
class ModelData_PixMapImpl;
}

class ModelData_PixMap : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_PixMapImpl ImplType;

    __CADEX_EXPORT ModelData_PixMap();
    __CADEX_EXPORT ModelData_PixMap (initialized);
    __CADEX_EXPORT ModelData_PixMap (ImplType* theImpl);

    __CADEX_EXPORT ModelData_PixMap (const unsigned char* thePixelData,
                                     size_t theWidth,
                                     size_t theHeight,
                                     ModelData_PixelFormat thePixelFormat);

    __CADEX_EXPORT ModelData_PixelFormat PixelFormat() const;

    __CADEX_EXPORT size_t Width() const;
    __CADEX_EXPORT size_t Height() const;

    __CADEX_EXPORT const unsigned char* PixelData() const;

    __CADEX_EXPORT size_t PixelDataSize() const;

    __CADEX_MODELDATA_DEFINE_TYPEID
};

__CADEX_EXPORT bool operator== (const ModelData_PixMap& thePM1, const ModelData_PixMap& thePM2);

}

#endif // __CADEX_PREVIEW_TEXTURES

#endif // _ModelData_PixMap_HeaderFile
