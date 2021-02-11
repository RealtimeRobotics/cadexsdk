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


#ifndef _Base_Logger_HeaderFile
#define _Base_Logger_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_TypeDef.hxx>

namespace cadex {

class Base_LoggerAppender;

namespace internal {
class Base_LoggerImpl;
class Base_LoggerLocationInfo;
}

class Base_Logger
{
public:

    enum Level {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal};

    //! Returns a global logger.
    __CADEX_EXPORT static Base_Logger& GlobalInstance();

    //! Destructor.
    __CADEX_EXPORT ~Base_Logger();

    //! Sets message severity level.
    __CADEX_EXPORT void SetLevel (const Level theLevel);

    //! Returns a message severity level.
    __CADEX_EXPORT Level GetLevel () const;

    //! Returns true if the logger accepts a message of the level \a theLevel.
    __CADEX_EXPORT bool CanAccept (const Level theLevel) const;

    //! Logs a message with respective level and location information.
    __CADEX_EXPORT void ForcedLog (const Level theLevel,
        const UTF8* theMessage,
        const internal::Base_LoggerLocationInfo& theLocation);

    //! Logs a message with respective level and location information.
    __CADEX_EXPORT void ForcedLog (const Level theLevel,
        const UTF16* theMessage,
        const internal::Base_LoggerLocationInfo& theLocation);

    //! Adds an appender to the logger.
    __CADEX_EXPORT void Register (Base_LoggerAppender& theAppender,
        const Level theMinLevel = Trace, const Level theMaxLevel = Fatal);

    //! Removes an appender from the logger.
    __CADEX_EXPORT void Unregister (const Base_LoggerAppender& theAppender);

protected:

    //! Constructor.
    Base_Logger();

private:
    Base_Logger (const Base_Logger&);
    Base_Logger& operator= (const Base_Logger&);

    internal::Base_LoggerImpl*  myImpl;
};

}

#endif
