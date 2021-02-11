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


#ifndef _ModelCheck_ErrorLevel_HeaderFile
#define _ModelCheck_ErrorLevel_HeaderFile

namespace cadex {

enum ModelCheck_ErrorLevel
{
    ModelCheck_EL_Error      = 0x01,
    ModelCheck_EL_Warning1   = 0x10, //high
    ModelCheck_EL_Warning2   = 0x20, //medium
    ModelCheck_EL_Warning3   = 0x40, //low
    ModelCheck_EL_Warning4   = 0x80, //cosmetic
    ModelCheck_EL_WarningAll = ModelCheck_EL_Warning1 | ModelCheck_EL_Warning2 |
                               ModelCheck_EL_Warning3 | ModelCheck_EL_Warning4,
    ModelCheck_EL_NoError    = 0x100,
};
}

#endif
