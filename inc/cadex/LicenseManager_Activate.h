// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2019, CADEX. All rights reserved.
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

#ifndef _LicenseManager_Activate_HeaderFile
#define _LicenseManager_Activate_HeaderFile

#include <cadex/LicenseManager_LicenseError.hxx> //for users' convenience

#ifndef __CADEX_EXPORT
#if _WIN32
#define __CADEX_EXPORT __declspec (dllexport)
#else
#define __CADEX_EXPORT
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

__CADEX_EXPORT bool CADExLicense_Activate (const char* theKey);

__CADEX_EXPORT bool CADExLicense_Activate_Verbose (const char* theKey);

#ifdef __cplusplus
}
#endif

#endif
