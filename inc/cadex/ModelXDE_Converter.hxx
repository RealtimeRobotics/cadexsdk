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


#ifndef _ModelXDE_Converter_HeaderFile
#define _ModelXDE_Converter_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_Macro.hxx>
#if OCC_VERSION_HEX >= 0x070000
#include <Standard_Handle.hxx>
#endif

__CADEX_DEFINE_HANDLE_TYPE_FWD_PUBLIC
__CADEX_DEFINE_HANDLE_FWD_PUBLIC(TDocStd_Document)

namespace cadex {

class ModelData_Model;

class ModelXDE_Converter
{
public:

    __CADEX_EXPORT static bool Convert (const ModelData_Model& theSource,
        const Handle(TDocStd_Document)& theTarget);

    __CADEX_EXPORT static bool Convert (const Handle(TDocStd_Document)& theSource,
        ModelData_Model& theTarget);
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_PARA_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_PARA_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_PARA_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExXDEd.lib")
        #else
            #pragma comment(lib, "CadExXDE.lib")
        #endif
    #endif
#endif

#endif
