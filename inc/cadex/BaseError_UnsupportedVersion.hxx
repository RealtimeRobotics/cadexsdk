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


#ifndef _BaseError_UnsupportedVersion_HeaderFile
#define _BaseError_UnsupportedVersion_HeaderFile

#include <cadex/Base_Exception.hxx>

#include <memory>

namespace cadex {

class BaseError_UnsupportedVersion : public Base_Exception
{
public:
    __CADEX_EXPORT BaseError_UnsupportedVersion (
        const Base_UTF16String& theFileVersion,
        const Base_UTF16String& theMinSupportedVersion,
        const Base_UTF16String& theMaxSupportedVersion);

    __CADEX_EXPORT BaseError_UnsupportedVersion (
        const Base_UTF16String& theFileVersion,
        const Base_UTF16String& theSupportedVersion);

    __CADEX_EXPORT const Base_UTF16String& FileVersion() const;
    __CADEX_EXPORT const Base_UTF16String& MinSupportedVersion() const;
    __CADEX_EXPORT const Base_UTF16String& MaxSupportedVersion() const;
};

}

#endif
