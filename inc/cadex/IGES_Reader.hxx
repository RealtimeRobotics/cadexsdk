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


#ifndef _IGES_Reader_HeaderFile
#define _IGES_Reader_HeaderFile

#include <cadex/Base_Reader.hxx>

namespace cadex {

class IGES_ReaderParameters;

class IGES_Reader : public Base_Reader
{
public:

    __CADEX_EXPORT IGES_Reader();

    __CADEX_EXPORT const IGES_ReaderParameters& Parameters() const;

    __CADEX_EXPORT IGES_ReaderParameters& Parameters();

protected:

    //! Constructor.
    /*! \internal
    */
    IGES_Reader (internal::Base_Reader_Private* theImpl) : Base_Reader (theImpl) {}
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_IGES_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_IGES_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_IGES_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExIGESd.lib")
        #else
            #pragma comment(lib, "CadExIGES.lib")
        #endif
    #endif
#endif

#endif
