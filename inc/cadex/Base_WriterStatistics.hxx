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


#ifndef _Base_WriterStatistics_HeaderFile
#define _Base_WriterStatistics_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_WRITER_STATISTICS
#include <cadex/Base_ExportError.hxx>
#include <memory>

namespace cadex {
namespace internal {
class Base_WriterStatisticsImpl;
}

class Base_WriterStatistics
{
public:
    class ErrorIterator
    {
    public:
        __CADEX_EXPORT ErrorIterator (const Base_WriterStatistics& theStatistics);

        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const Base_ExportError& Next();

    private:
        class Impl;
        std::shared_ptr <Impl> myImpl;
    };

    Base_WriterStatistics (const std::shared_ptr <internal::Base_WriterStatisticsImpl>& theImpl);

private:
    std::shared_ptr <internal::Base_WriterStatisticsImpl> myImpl;
};

}

#endif
#endif
