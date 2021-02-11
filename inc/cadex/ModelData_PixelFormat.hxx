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


#ifndef _ModelData_PixelFormat_HeaderFile
#define _ModelData_PixelFormat_HeaderFile

namespace cadex {

enum ModelData_PixelFormat {
    ModelData_PF_None,
    ModelData_PF_RGB,
    ModelData_PF_RGBA,
    ModelData_PF_Alpha,
    ModelData_PF_Luminance,
    ModelData_PF_LuminanceAlpha
};

}

#endif // _ModelData_PixelFormat_HeaderFile
