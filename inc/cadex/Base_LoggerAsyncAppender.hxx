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


#ifndef _Base_LoggerAsyncAppender_HeaderFile
#define _Base_LoggerAsyncAppender_HeaderFile

#include <cadex/Base_LoggerAppender.hxx>

namespace cadex {

class Base_LoggerAsyncAppender : public Base_LoggerAppender
{
public:

    //! Constructor.
    __CADEX_EXPORT Base_LoggerAsyncAppender();

    //! Destructor.
    __CADEX_EXPORT ~Base_LoggerAsyncAppender();

    //! Adds an appender.
    __CADEX_EXPORT void Register (Base_LoggerAppender& theAppender,
        const Base_Logger::Level theMinLevel = Base_Logger::Trace,
        const Base_Logger::Level theMaxLevel = Base_Logger::Fatal);

    //! Removes an appender.
    __CADEX_EXPORT void Unregister (const Base_LoggerAppender& theAppender);

private:
    Base_LoggerAsyncAppender (const Base_LoggerAsyncAppender&);
    Base_LoggerAsyncAppender& operator= (const Base_LoggerAsyncAppender&);
    virtual void Append (CharPointerType theMessage);
};

}

#endif
