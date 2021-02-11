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

#ifndef _Base_String_HeaderFile
#define _Base_String_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/Base_TypeDef.hxx>
#include <string>
#include <ostream>

class TCollection_AsciiString;
class TCollection_ExtendedString;

namespace cadex {

class Base_UTF16String;

/*! \class Base_String
    \brief Wraps standard string.
*/
class Base_String
{
public:

    //! Defines a type of a standard string with CAD Exchanger allocator.
    typedef std::basic_string<char, std::char_traits<char>, Base_Allocator<char> > value_type;

    //! Constructor.
    /*! Creates an empty string.*/
    __CADEX_EXPORT Base_String();

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_String (const Base_String& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT explicit Base_String (const char* theOther);

    //! Constructor.
    /*! Converts the UTF16 string \a theOther to UTF8.*/
    __CADEX_EXPORT Base_String (const Base_UTF16String& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT explicit Base_String (const UTF16* theOther);

    //! Constructor.
    /*! Copies contents from another string. This syntax may only be used if the build
        environment (i.e. compiler versions and flags) of the customer fully matches one
        of CAD Exchanger. Otherwise syntax with plain pointers should be used.
    */
    __CADEX_EXPORT explicit Base_String (const value_type& theOther);

    //! Constructor.
    /*! Copies contents from another string. This syntax may only be used if the build
        environment (i.e. compiler versions and flags) of the customer fully matches one
        of CAD Exchanger. Otherwise syntax with plain pointers should be used.
    */
    __CADEX_EXPORT explicit Base_String (const std::string& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT explicit Base_String (const TCollection_AsciiString& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT explicit Base_String (const TCollection_ExtendedString& theOther);

    //! Destructor.
    /*! Destroys the object and frees all allocated resources.*/
    __CADEX_EXPORT ~Base_String();

    //! Returns an internal string representation.
    __CADEX_EXPORT const value_type& String() const;

    //! Returns an internal string representation.
    __CADEX_EXPORT value_type& String();

    __CADEX_EXPORT void Clear();

    //! Returns an internal string buffer.
    __CADEX_EXPORT const char* Data() const;

    //! Returns true if \a this equals \a theOther.
    __CADEX_EXPORT bool operator== (const Base_String& theOther) const;

    //! Returns true if \a this equals \a theOther.
    __CADEX_EXPORT bool operator== (const char* theOther) const;

    //! Returns true if \a this does equal \a theOther.
    bool operator!= (const Base_String& theOther) const { return !operator== (theOther); }

    //! Returns true if \a this does equal \a theOther.
    bool operator!= (const char* theOther) const { return !operator== (theOther); }

    //! Returns a string length in bytes.
    /*! As the string is in UTF-8 encoding the number of valuable characters can be smaller.*/
    __CADEX_EXPORT size_t Length() const;

    //! Returns true if the string is empty.
    /*! Returns true if the string length equals 0.*/
    __CADEX_EXPORT bool IsEmpty() const;

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_String& operator= (const Base_String& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_String& operator= (const char* theOther);

    //! Assignment operator.
    /*! Copies contents from another string. Converts the UTF16 string \a theOther to UTF8.*/
    __CADEX_EXPORT Base_String& operator= (const Base_UTF16String& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_String& operator= (const UTF16* theOther);

    //! Assignment operator.
    /*! Copies contents from another string. This syntax may only be used if the build
        environment (i.e. compiler versions and flags) of the customer fully matches one
        of CAD Exchanger. Otherwise syntax with plain pointers should be used.
    */
    __CADEX_EXPORT Base_String& operator= (const std::string& theOther);

    //! Assignment operator.
    /*! Copies contents from another string. This syntax may only be used if the build
        environment (i.e. compiler versions and flags) of the customer fully matches one
        of CAD Exchanger. Otherwise syntax with plain pointers should be used.
    */
    __CADEX_EXPORT Base_String& operator= (const value_type& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_String& operator= (const TCollection_AsciiString& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_String& operator= (const TCollection_ExtendedString& theOther);

private:
    void Assign (const UTF16* theOther);

#if _MSC_VER
#if _MSC_VER <= 1600
    static const size_t myBaseSize = 3;
#else
    static const size_t myBaseSize = 2;
#endif
#if _DEBUG
    __CADEX_DEFINE_ALIGNED_MEMBER (16 + (myBaseSize + 1) * sizeof(void*), void*)
#else
    __CADEX_DEFINE_ALIGNED_MEMBER (16 +  myBaseSize      * sizeof(void*), void*)
#endif
#elif __GNUC__
#if __apple_build_version__
    __CADEX_DEFINE_ALIGNED_MEMBER (24, void*)
#elif __ANDROID__ && _LIBCPP_VERSION
    __CADEX_DEFINE_ALIGNED_MEMBER (3 * sizeof(void*), void*)
#elif __GNUC__ > 4 || (__clang__ && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 8)))
    __CADEX_DEFINE_ALIGNED_MEMBER (16 + 2 * sizeof(void*), void*)
#else
    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof (void*), void*)
#endif
#endif
};

class Base_StringHash
{
public:
    __CADEX_EXPORT size_t operator() (const Base_String& theValue) const;
};

inline std::ostream& operator<< (std::ostream& theStream, const Base_String& theString)
{ return theStream << theString.Data(); }

}

inline unsigned int IsEqual (const cadex::Base_String& theS1,
                             const cadex::Base_String& theS2)
{ return theS1 == theS2; }

__CADEX_EXPORT int HashCode (const cadex::Base_String& theS1, const int theUpper);

#endif
