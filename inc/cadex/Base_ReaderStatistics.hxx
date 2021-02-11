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


#ifndef _Base_ReaderStatistics_HeaderFile
#define _Base_ReaderStatistics_HeaderFile

#if __CADEX_PREVIEW_READER_STATISTICS

#include <memory>

namespace cadex {
class Base_MissingExternalReference;

namespace internal {
class Base_ReaderStatisticsImpl;
}

class Base_ReaderStatistics
{
public:
    __CADEX_EXPORT Base_ReaderStatistics();

    __CADEX_EXPORT explicit Base_ReaderStatistics (
        const std::shared_ptr <internal::Base_ReaderStatisticsImpl>& theImpl);

    class MissingExternalReferencesIterator
    {
    public:
        __CADEX_EXPORT explicit MissingExternalReferencesIterator (const Base_ReaderStatistics& theReaderStats);

        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT Base_MissingExternalReference Next();

    private:
        class Impl;
        std::shared_ptr <Impl> myImpl;
    };

private:
    std::shared_ptr <internal::Base_ReaderStatisticsImpl> myImpl;
};

}

#endif
#endif
