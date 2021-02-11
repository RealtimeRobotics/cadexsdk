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


#ifndef _IGESXDE_Reader_HeaderFile
#define _IGESXDE_Reader_HeaderFile

#include <cadex/IGES_Reader.hxx>

namespace cadex {

class IGESXDE_Reader : public IGES_Reader
{
public:

    //! Creates an object.
    /*! Empty constructor.*/
    __CADEX_EXPORT IGESXDE_Reader();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_IGESXDE_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_IGESXDE_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_IGESXDE_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExIGESXDEd.lib")
        #else
            #pragma comment(lib, "CadExIGESXDE.lib")
        #endif
    #endif
#endif

#endif
