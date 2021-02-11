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


#ifndef _ModelData_TextureType_HeaderFile
#define _ModelData_TextureType_HeaderFile

namespace cadex {

enum ModelData_TextureType
{
    ModelData_TT_Unknown,
    ModelData_TT_DiffuseMap,
    ModelData_TT_SpecularMap,
    ModelData_TT_EmissiveMap,
    ModelData_TT_BumpMap,
    ModelData_TT_NormalMap,
    ModelData_TT_DisplacementMap,
    ModelData_TT_SphereEnvironmentMap
};

}

#endif // _ModelData_TextureType_HeaderFile
