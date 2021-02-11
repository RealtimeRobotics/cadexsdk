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


#ifndef _A3DS_Reader_HeaderFile
#define _A3DS_Reader_HeaderFile

#include <cadex/Base_Reader.hxx>

namespace cadex {
class A3DS_ReaderParameters;

class A3DS_Reader : public Base_Reader
{
public:

    __CADEX_EXPORT A3DS_Reader();

    __CADEX_EXPORT const A3DS_ReaderParameters& Parameters() const;

    __CADEX_EXPORT A3DS_ReaderParameters& Parameters();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_A3DS_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_A3DS_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_A3DS_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExA3DSd.lib")
        #else
            #pragma comment(lib, "CadExA3DS.lib")
        #endif
    #endif
#endif

#endif
