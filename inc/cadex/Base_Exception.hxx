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

#ifndef _Base_Exception_HeaderFile
#define _Base_Exception_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>

#include <memory>

namespace cadex {
class Base_UTF16String;

namespace internal {
class Base_ExceptionImpl;
}

class Base_Exception
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT explicit Base_Exception (const Base_UTF16String& theWhat);

    __CADEX_EXPORT ~Base_Exception();

    __CADEX_EXPORT const Base_UTF16String& What() const;

protected:
    //! Reserved for internal use.
    __CADEX_EXPORT Base_Exception (std::shared_ptr <internal::Base_ExceptionImpl> theImpl);

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast <T*> (myImpl.get()); }

    std::shared_ptr <internal::Base_ExceptionImpl> myImpl;
};

}

#endif
