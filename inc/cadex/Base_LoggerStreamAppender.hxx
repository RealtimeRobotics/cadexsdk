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


#ifndef _Base_LoggerStreamAppender_HeaderFile
#define _Base_LoggerStreamAppender_HeaderFile

#include <cadex/Base_LoggerAppender.hxx>
#if __CADEX_CHECK_BUILD_ENVIRONMENT
#include <cadex/Base_EnvironmentChecker.hxx>
#endif

namespace cadex {

class Base_LoggerStreamAppender : public Base_LoggerAppender
{
public:

    //! Defines a stream type.
    /*! Uses UTF-8 encoding when writing.*/
    typedef std::ostream    StreamType;

    //! Constructor.
    Base_LoggerStreamAppender (StreamType& theStream)
    {
#if __CADEX_CHECK_BUILD_ENVIRONMENT
        Base_EnvironmentChecker::CheckEnvironment();
#endif
        Construct (theStream);
    }

    //! Returns true if the end-of-line symbol is to be added after each message.
    __CADEX_EXPORT bool AppendEOL() const;

    //! Returns true if the end-of-line symbol is to be added after each message.
    __CADEX_EXPORT bool& AppendEOL();

    //! Returns true if each message must be flushed into the stream.
    __CADEX_EXPORT bool ImmediateFlush() const;

    //! Returns true if each message must be flushed into the stream.
    __CADEX_EXPORT bool& ImmediateFlush();

    //! Outputs a message into the stream.
    __CADEX_EXPORT virtual void Append (CharPointerType theMessage);

private:
    __CADEX_EXPORT void Construct (StreamType& theStream);
    Base_LoggerStreamAppender (const Base_LoggerStreamAppender&);
    Base_LoggerStreamAppender& operator= (const Base_LoggerStreamAppender&);
};

}

#endif
