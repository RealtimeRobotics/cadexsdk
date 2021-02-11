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


#ifndef _JT_Reader_HeaderFile
#define _JT_Reader_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_Reader.hxx>

namespace cadex {

class JT_FileModelTools;
class JT_ReaderParameters;

class JT_Reader : public Base_Reader
{
public:

    __CADEX_EXPORT JT_Reader();

    __CADEX_EXPORT const JT_ReaderParameters& Parameters() const;

    __CADEX_EXPORT JT_ReaderParameters& Parameters();

#if __CADEX_PREVIEW_FILE_MODEL_TOOLS
    __CADEX_EXPORT JT_FileModelTools CreateFileModelTools() const;
#endif
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_JT_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_JT_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_JT_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExJTd.lib")
        #else
            #pragma comment(lib, "CadExJT.lib")
        #endif
    #endif
#endif

#endif
