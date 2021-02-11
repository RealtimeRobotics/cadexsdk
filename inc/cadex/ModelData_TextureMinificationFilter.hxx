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


#ifndef _ModelData_TextureMinificationFilter_HeaderFile
#define _ModelData_TextureMinificationFilter_HeaderFile

namespace cadex {

enum ModelData_TextureMinificationFilter
{
    ModelData_TMinF_Nearest,
    ModelData_TMinF_NearestMipMapNearest,
    ModelData_TMinF_NearestMipMapLinear,
    ModelData_TMinF_Linear,
    ModelData_TMinF_LinearMipMapNearest,
    ModelData_TMinF_LinearMipMapLinear
};

}

#endif // _ModelData_TextureMinificationFilter_HeaderFile
