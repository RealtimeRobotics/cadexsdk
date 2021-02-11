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


#ifndef _USD_Writer_HeaderFile
#define _USD_Writer_HeaderFile

#include <cadex/Base_Writer.hxx>

namespace cadex {

class USD_WriterParameters;

class USD_Writer : public Base_Writer
{
public:
    __CADEX_EXPORT USD_Writer();

    __CADEX_EXPORT const USD_WriterParameters& Parameters() const;

    __CADEX_EXPORT USD_WriterParameters& Parameters();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_USD_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_USD_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_USD_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExUSDd.lib")
        #else
            #pragma comment(lib, "CadExUSD.lib")
        #endif
    #endif
#endif

#endif
