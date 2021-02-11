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

#ifndef _ModelData_TextureVisitor_HeaderFile
#define _ModelData_TextureVisitor_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_TEXTURES

namespace cadex {

class ModelData_FileTexture;
class ModelData_PixMapTexture;

class ModelData_TextureVisitor
{
public:
    __CADEX_EXPORT virtual ~ModelData_TextureVisitor();

    virtual void operator() (const ModelData_FileTexture& theTexture) = 0;
    virtual void operator() (const ModelData_PixMapTexture& theTexture) = 0;
};

}

#endif // __CADEX_PREVIEW_TEXTURES

#endif // _ModelData_TextureVisitor_HeaderFile
