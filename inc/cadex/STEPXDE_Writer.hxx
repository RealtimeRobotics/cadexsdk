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


#ifndef _STEPXDE_Writer_HeaderFile
#define _STEPXDE_Writer_HeaderFile

#include <cadex/STEP_Writer.hxx>

namespace cadex {

class STEPXDE_Writer : public STEP_Writer
{
public:

    //! Creates an object.
    /*! Empty constructor.*/
    __CADEX_EXPORT STEPXDE_Writer();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_STEPXDE_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_STEPXDE_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_STEPXDE_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExSTEPXDEd.lib")
        #else
            #pragma comment(lib, "CadExSTEPXDE.lib")
        #endif
    #endif
#endif

#endif
