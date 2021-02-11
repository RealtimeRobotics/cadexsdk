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


#ifndef _BaseError_UnexpectedFormat_HeaderFile
#define _BaseError_UnexpectedFormat_HeaderFile

#include <cadex/Base_Exception.hxx>

#include <memory>

namespace cadex {

class BaseError_UnexpectedFormat : public Base_Exception
{
public:
    __CADEX_EXPORT explicit BaseError_UnexpectedFormat (const Base_UTF16String& theFormatName);

    __CADEX_EXPORT const Base_UTF16String& FormatName() const;
};

}

#endif
