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


#ifndef _Base_LoggerAppender_HeaderFile
#define _Base_LoggerAppender_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Logger.hxx>
#include <cadex/Base_SharedPtr.hxx>

namespace cadex {

namespace internal {
class Base_LoggerAppenderImpl;
}

class Base_LoggerAppender
{
public:

    //! Defines a character type of user-visible strings.
    typedef UTF16           CharType;

    //! Defines a type of the pointer to the character type.
    typedef const UTF16*    CharPointerType;

    class Sentry
    {
    public:
        //! Constructor.
        Sentry (Base_Logger& theLogger, Base_LoggerAppender& theAppender) :
            myLogger (theLogger), myAppender (theAppender)
        { theLogger.Register (theAppender); }

        //! Destructor.
        ~Sentry() { myLogger.Unregister (myAppender); }
    private:
        Sentry (const Sentry&);
        Sentry& operator= (const Sentry&);
        Base_Logger&    myLogger;
        Base_LoggerAppender&       myAppender;
    };

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Destructor.
    __CADEX_EXPORT virtual ~Base_LoggerAppender();

    //! Assignment operator.
    __CADEX_EXPORT Base_LoggerAppender& operator= (const Base_LoggerAppender& theAppender);

    //! Appends a message.
    virtual void Append (CharPointerType theMessage) = 0;

    //! Returns internal implementation object.
    /*! \internal*/
    const std::shared_ptr<internal::Base_LoggerAppenderImpl>& Impl() const
    { return myImpl; }

protected:

#if 1
    //TODO - replace this with constructor with some tag (e.g. int) to make sure
    // that subclasses never call it by mistake instead of calling ctor with
    //Impl
    //! Constructor.
    __CADEX_EXPORT Base_LoggerAppender();
#endif

    //! Constructor.
    __CADEX_EXPORT Base_LoggerAppender (
        const std::shared_ptr<internal::Base_LoggerAppenderImpl>& theImpl);

    //! Constructor.
    __CADEX_EXPORT Base_LoggerAppender (const Base_LoggerAppender& theAppender);

    //! Delayed constructor.
    __CADEX_EXPORT void Construct (
        const std::shared_ptr<internal::Base_LoggerAppenderImpl>& theImpl);

    //! Returns a pointer to this object.
    /*! \internal*/
    Base_LoggerAppender* This() { return this; }

private:
    std::shared_ptr<internal::Base_LoggerAppenderImpl>    myImpl;
};

}

#endif
