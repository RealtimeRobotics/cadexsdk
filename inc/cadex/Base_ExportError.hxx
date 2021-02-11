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


#ifndef _Base_ExportError_HeaderFile
#define _Base_ExportError_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_WRITER_STATISTICS
#include <cadex/Base_Allocator.hxx>

#include <memory>

namespace cadex {
class ModelData_Shape;
class Base_UTF16String;
namespace internal {
class Base_ExportErrorImpl;
}

class Base_ExportError
{
 public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT
    __CADEX_EXPORT Base_ExportError (const std::shared_ptr <internal::Base_ExportErrorImpl>& theImpl);

    __CADEX_EXPORT const Base_UTF16String& Message() const;
    __CADEX_EXPORT const Base_UTF16String& Context() const;
    __CADEX_EXPORT const ModelData_Shape& Shape() const;

private:
    std::shared_ptr <internal::Base_ExportErrorImpl> myImpl;
};

}

#endif
#endif
