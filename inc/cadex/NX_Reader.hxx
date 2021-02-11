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


#ifndef _NX_Reader_HeaderFile
#define _NX_Reader_HeaderFile

#include <cadex/Base_Reader.hxx>

namespace cadex {
class NX_ReaderParameters;

class NX_Reader : public Base_Reader
{
public:
    __CADEX_EXPORT NX_Reader();

    __CADEX_EXPORT const NX_ReaderParameters& Parameters() const;

    __CADEX_EXPORT NX_ReaderParameters& Parameters();
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_NX_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_NX_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_NX_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExNXd.lib")
        #else
            #pragma comment(lib, "CadExNX.lib")
        #endif
    #endif
#endif

#endif
