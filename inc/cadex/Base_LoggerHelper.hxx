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

// ****************************************************************************
// Attribution:
// Design and implementation of Base_Logger has been inspired (among other
// factors) by the log4cxx library (http://logging.apache.org/log4cxx/)
// licensed under the Apache License Version 2.0
// (http://www.apache.org/licenses/LICENSE-2.0).
// However Base_Logger does not constitute the Derivative Work as defined in
// the above license.
// ****************************************************************************


#ifndef _Base_LoggerHelper_HeaderFile
#define _Base_LoggerHelper_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Logger.hxx>
#include <string>
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <iostream>

class TCollection_ExtendedString;

namespace cadex {

class Base_String;
class Base_UTF16String;

namespace internal {

class Base_LoggerLocationInfo
{
public:
    Base_LoggerLocationInfo (const char* theFileName, const char* theFunctionName,
        const int theLineNumber) : myFileName (theFileName),
        myFunctionName (theFunctionName), myLineNumber (theLineNumber) {}

    Base_LoggerLocationInfo (const Base_LoggerLocationInfo& theOther) :
        myFileName (theOther.myFileName), myFunctionName (theOther.myFunctionName),
        myLineNumber (theOther.myLineNumber) {}

    const char* myFileName;
    const char* myFunctionName;
    int         myLineNumber;
};

typedef std::ios_base& (*ios_base_manip)(std::ios_base&);

template<typename T>
class Base_LoggerTemplateMessageBuffer
{
public:
    typedef T                                                           value_type;
    typedef std::basic_string<value_type, std::char_traits<value_type>,
        Base_Allocator<value_type> >                                    StringType;
    typedef std::basic_ostream<value_type>                              StreamType;
    typedef std::basic_ostringstream<value_type,
        std::char_traits<value_type>, Base_Allocator<value_type> >      StringStreamType;
    typedef Base_LoggerTemplateMessageBuffer                            MyType;

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    Base_LoggerTemplateMessageBuffer() : myStream (0) {}

    ~Base_LoggerTemplateMessageBuffer() { delete myStream; }

    MyType& operator<< (const StringType& theMessage)
    {
        if (myStream == 0) {
            myBuf.append (theMessage);
        } else {
            *myStream << theMessage;
        }
        return *this;
    }

    MyType& operator<< (const value_type* theMessage)
    {
        if (theMessage == 0) {
            operator<< (StringType());
        } else {
            if (myStream == 0) {
                myBuf.append (theMessage);
            } else {
                *myStream << theMessage;
            }
        }
        return *this;
    }

    MyType& operator<< (value_type* theMessage)
    {
        if (theMessage == 0) {
            operator<< (StringType());
        } else {
            if (myStream == 0) {
                myBuf.append (theMessage);
            } else {
                *myStream << theMessage;
            }
        }
        return *this;
    }

    MyType& operator<< (const value_type theMessage)
    {
        if (myStream == 0) {
            myBuf.append (1, theMessage);
        } else {
            myBuf.assign (1, theMessage);
            *myStream << myBuf;
        }
        return *this;
    }

    StreamType& operator<< (ios_base_manip theManip)
    {
        StreamType& s = *this;
        (*theManip)(s);
        return s;
    }

    StreamType& operator<< (const boost::uuids::uuid& theVal)
    {
        const boost::uuids::uuid& v = theVal;
        StreamType& s = *this;
        s << std::hex;
        for (boost::uuids::uuid::const_iterator i = v.begin(); i != v.end(); ++i)
            s << static_cast<int> (*i);
        s << std::dec;
        return s;
    }

    template<typename V>
    StreamType& operator<< (const V& theVal)
    {
        return static_cast<StreamType&> (*this) << theVal;
    }

    // for stream manipulators (e.g. std::endl)
    StreamType& operator<< (StreamType& (*theManipulator)(StreamType&))
    {
        return static_cast<StreamType&> (*this) << theManipulator;
    }

    operator StreamType&()
    {
        if (myStream == 0) {
            myStream = new StringStreamType();
            if (!myBuf.empty()) {
                *myStream << myBuf;
            }
        }
        return *myStream;
    }

    const StringType& str (StreamType& /*theStream*/)
    {
        assert (myStream && "myStream is null");
        myBuf = myStream->str();
        return myBuf;
    }

    const StringType& str (MyType& /*theBuf*/) { return myBuf; }

    bool hasStream() const { return myStream != 0; }

private:
    Base_LoggerTemplateMessageBuffer (const Base_LoggerTemplateMessageBuffer&);
    Base_LoggerTemplateMessageBuffer& operator=(const Base_LoggerTemplateMessageBuffer&);

    StringType          myBuf;
    StringStreamType*   myStream;
};

typedef Base_LoggerTemplateMessageBuffer<char>  Base_LoggerCharMessageBuffer;
typedef Base_LoggerTemplateMessageBuffer<wchar_t> Base_LoggerWCharMessageBuffer;


class Base_LoggerMessageBuffer
{
public:

#if 0
    typedef Base_LoggerString   String;
    typedef Base_LoggerWString  WString;
#else
    typedef Base_LoggerCharMessageBuffer::StringType    String;
    typedef Base_LoggerWCharMessageBuffer::StringType   WString;
#endif

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT Base_LoggerMessageBuffer();
    __CADEX_EXPORT ~Base_LoggerMessageBuffer();

    __CADEX_EXPORT operator std::ostream&();

    __CADEX_EXPORT Base_LoggerCharMessageBuffer& operator<< (const Base_String& theMessage);
    __CADEX_EXPORT Base_LoggerCharMessageBuffer& operator<< (const String& theMessage);
    __CADEX_EXPORT Base_LoggerCharMessageBuffer& operator<< (const char* theMessage);
    __CADEX_EXPORT Base_LoggerCharMessageBuffer& operator<< (const char theMessage);
    Base_LoggerCharMessageBuffer& operator<< (const unsigned char* theMessage)
    { return operator << (reinterpret_cast<const char*> (theMessage)); }
    Base_LoggerCharMessageBuffer& operator<< (const unsigned char theMessage)
    { return operator << (static_cast<char> (theMessage)); }
    __CADEX_EXPORT Base_LoggerCharMessageBuffer& Append (void* theBuffer, size_t theLength);
    __CADEX_EXPORT const String& str (Base_LoggerCharMessageBuffer& buf);
    __CADEX_EXPORT const String& str(std::ostream& os);

    __CADEX_EXPORT Base_LoggerWCharMessageBuffer& operator<< (const WString& msg);
    __CADEX_EXPORT Base_LoggerWCharMessageBuffer& operator<< (const wchar_t* msg);
    __CADEX_EXPORT Base_LoggerWCharMessageBuffer& operator<< (const UTF16* msg);
    __CADEX_EXPORT Base_LoggerWCharMessageBuffer& operator<< (const TCollection_ExtendedString& msg);
    __CADEX_EXPORT Base_LoggerWCharMessageBuffer& operator<< (const Base_UTF16String& msg);
    __CADEX_EXPORT std::ostream& operator<< (ios_base_manip manip);
    __CADEX_EXPORT std::ostream& operator<< (bool val);
    __CADEX_EXPORT std::ostream& operator<< (short val);
    __CADEX_EXPORT std::ostream& operator<< (int val);
    __CADEX_EXPORT std::ostream& operator<< (unsigned int val);
    __CADEX_EXPORT std::ostream& operator<< (long val);
    __CADEX_EXPORT std::ostream& operator<< (unsigned long val);
    __CADEX_EXPORT std::ostream& operator<< (float val);
    __CADEX_EXPORT std::ostream& operator<< (double val);
    __CADEX_EXPORT std::ostream& operator<< (long double val);
    __CADEX_EXPORT std::ostream& operator<< (void* val);
    __CADEX_EXPORT std::ostream& operator<< (const boost::uuids::uuid& val);
    __CADEX_EXPORT const WString& str (Base_LoggerWCharMessageBuffer& buf);
    __CADEX_EXPORT const WString& str (std::basic_ostream<wchar_t>& os);

    __CADEX_EXPORT bool hasStream() const;

private:
    Base_LoggerMessageBuffer(const Base_LoggerMessageBuffer&);
    Base_LoggerMessageBuffer& operator=(const Base_LoggerMessageBuffer&);

    Base_LoggerCharMessageBuffer   cbuf;
    Base_LoggerWCharMessageBuffer* wbuf;
};

/*! This operator is used when there is no overloaded method operator<< in
    Base_LoggerMessageBuffer.
*/
template<typename V>
inline std::ostream& operator<< (Base_LoggerMessageBuffer& theBuffer, const V& theVal)
{
    return static_cast<std::ostream&> (theBuffer) << theVal;
}

__CADEX_EXPORT std::ostream& operator<< (std::ostream& theStream, const boost::uuids::uuid& val);


#if 0
class Base_LoggerMessageConverter
{
public:

    typedef UTF8* CharPointerType;

    Base_LoggerMessageConverter (const Base_LoggerMessageBuffer::String& theString) :
        myBuf (const_cast<CharPointerType> (reinterpret_cast<const UTF8*> (
            theString.c_str()))),
        myIsAllocated (false) {}

    __CADEX_EXPORT Base_LoggerMessageConverter (
        const Base_LoggerMessageBuffer::WString& theString);

    //! Destructor.
    __CADEX_EXPORT ~Base_LoggerMessageConverter();

    const CharPointerType Str() const { return myBuf; }

protected:

    CharPointerType myBuf;
    bool            myIsAllocated;
};
#else
class Base_LoggerMessageConverter
{
public:

    typedef UTF16           CharType;
    typedef CharType*       CharPointerType;
    typedef const CharType* ConstCharPointerType;

    __CADEX_EXPORT Base_LoggerMessageConverter (
        const Base_LoggerMessageBuffer::String& theString);

    __CADEX_EXPORT Base_LoggerMessageConverter (
        const Base_LoggerMessageBuffer::WString& theString);

    //! Destructor.
    __CADEX_EXPORT ~Base_LoggerMessageConverter();

    ConstCharPointerType Str() const { return myBuf; }

protected:

    CharPointerType myBuf;
    bool            myIsAllocated;
};
#endif
}}

#if _MSC_VER
#define __CADEX_LOG_UNLIKELY(expr) expr
#define __CADEX_LOG_FUNC __FUNCSIG__
#else
#define __CADEX_LOG_UNLIKELY(expr) __builtin_expect(expr, 0)
#define __CADEX_LOG_FUNC __PRETTY_FUNCTION__
#endif

#define __CADEX_LOG_LOCATION \
    cadex::internal::Base_LoggerLocationInfo(__FILE__, __CADEX_LOG_FUNC, __LINE__)

#define __CADEX_LOG_MESSAGE(LOGGER,LEVEL,MESSAGE) \
    { \
        if (__CADEX_LOG_UNLIKELY(LOGGER.CanAccept (LEVEL))) { \
            cadex::internal::Base_LoggerMessageBuffer _aB; \
            cadex::internal::Base_LoggerMessageConverter _aMessage (_aB.str (_aB << MESSAGE)); \
            LOGGER.ForcedLog (LEVEL, _aMessage.Str(), __CADEX_LOG_LOCATION); \
        } \
    }

#define __CADEX_LOG_FATAL(LOGGER,MESSAGE)   __CADEX_LOG_MESSAGE(LOGGER, cadex::Base_Logger::Fatal,   MESSAGE)
#define __CADEX_LOG_ERROR(LOGGER,MESSAGE)   __CADEX_LOG_MESSAGE(LOGGER, cadex::Base_Logger::Error,   MESSAGE)
#define __CADEX_LOG_WARNING(LOGGER,MESSAGE) __CADEX_LOG_MESSAGE(LOGGER, cadex::Base_Logger::Warning, MESSAGE)
#define __CADEX_LOG_INFO(LOGGER,MESSAGE)    __CADEX_LOG_MESSAGE(LOGGER, cadex::Base_Logger::Info,    MESSAGE)
#define __CADEX_LOG_DEBUG(LOGGER,MESSAGE)   __CADEX_LOG_MESSAGE(LOGGER, cadex::Base_Logger::Debug,   MESSAGE)
#define __CADEX_LOG_TRACE(LOGGER,MESSAGE)   __CADEX_LOG_MESSAGE(LOGGER, cadex::Base_Logger::Trace,   MESSAGE)

#define __CADEX_LOG_FATAL_DEFAULT(MESSAGE)   __CADEX_LOG_FATAL   (cadex::Base_Logger::GlobalInstance(), MESSAGE)
#define __CADEX_LOG_ERROR_DEFAULT(MESSAGE)   __CADEX_LOG_ERROR   (cadex::Base_Logger::GlobalInstance(), MESSAGE)
#define __CADEX_LOG_WARNING_DEFAULT(MESSAGE) __CADEX_LOG_WARNING (cadex::Base_Logger::GlobalInstance(), MESSAGE)
#define __CADEX_LOG_INFO_DEFAULT(MESSAGE)    __CADEX_LOG_INFO    (cadex::Base_Logger::GlobalInstance(), MESSAGE)
#define __CADEX_LOG_DEBUG_DEFAULT(MESSAGE)   __CADEX_LOG_DEBUG   (cadex::Base_Logger::GlobalInstance(), MESSAGE)
#define __CADEX_LOG_TRACE_DEFAULT(MESSAGE)   __CADEX_LOG_TRACE   (cadex::Base_Logger::GlobalInstance(), MESSAGE)

/*! Logs contents of the void* buffer.*/
#define __CADEX_LOG_BUFFER(LOGGER,LEVEL,BUFFER,LENGTH) \
    { \
        if (__CADEX_LOG_UNLIKELY(LOGGER.CanAccept (LEVEL))) { \
            cadex::internal::Base_LoggerMessageBuffer _aB; \
            cadex::internal::Base_LoggerMessageConverter _aMessage (_aB.str \
                (_aB.Append ((BUFFER), (LENGTH)))); \
            LOGGER.ForcedLog (LEVEL, _aMessage.Str(), __CADEX_LOG_LOCATION); \
        } \
    }


#endif
