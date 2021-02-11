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

#ifndef _Base_UTF16String_HeaderFile
#define _Base_UTF16String_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/Base_String.hxx>
#include <cadex/Base_TypeDef.hxx>
#include <string>
#include <ostream>

class TCollection_AsciiString;
class TCollection_ExtendedString;

namespace cadex {

class Base_UTF16String
{
public:

    //! Defines a type of a standard string with CAD Exchanger allocator.
    typedef UTF16   ValueType;

    //! Defines a type of a standard string with CAD Exchanger allocator.
    typedef std::basic_string<ValueType,
        std::char_traits<ValueType>,
        Base_Allocator<ValueType> >    value_type;

    //! Constructor.
    /*! Creates an empty string.*/
    __CADEX_EXPORT Base_UTF16String();

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const Base_UTF16String& theOther);

    //! Constructor.
    /*! Moves contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (Base_UTF16String&& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const char* theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const UTF16* theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const UTF16* theOther, size_t theLength);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const wchar_t* theOther);

    //! Constructor.
    /*! Copies contents from another string. This syntax may only be used if the build
        environment (i.e. compiler versions and flags) of the customer fully matches one
        of CAD Exchanger. Otherwise syntax with plain pointers should be used.
    */
    __CADEX_EXPORT Base_UTF16String (const value_type& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const TCollection_AsciiString& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const TCollection_ExtendedString& theOther);

    __CADEX_EXPORT Base_UTF16String (const std::wstring& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const Base_String& theOther);

    //! Constructor.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String (const std::basic_string<char, std::char_traits<char>,
        Base_Allocator<char> >& theOther);

    //! Destructor.
    /*! Destroys the object and frees all allocated resources.*/
    __CADEX_EXPORT ~Base_UTF16String();

    //! Returns an internal string representation.
    __CADEX_EXPORT const value_type& String() const;

    //! Returns an internal string representation.
    __CADEX_EXPORT value_type& String();

    //! Returns an internal string buffer.
    __CADEX_EXPORT const UTF16* Data() const;

    //! Converts to another Unicode representation.
    __CADEX_EXPORT TCollection_ExtendedString ToExtendedString() const;

    __CADEX_EXPORT void Clear();

    //! Converts to UTF-8 string.
    __CADEX_EXPORT Base_String ToUTF8() const;

    __CADEX_EXPORT std::wstring ToWString() const;

    //! Returns true if \a this equals \a theOther.
    __CADEX_EXPORT bool operator== (const Base_UTF16String& theOther) const;

    //! Returns true if \a this does equal \a theOther.
    bool operator!= (const Base_UTF16String& theOther) const { return !operator== (theOther); }

    //! Returns a string length in UTF16 characters.
    /*! */
    __CADEX_EXPORT size_t Length() const;

    //! Returns true if the string is empty.
    /*! Returns true if the string length equals 0.*/
    __CADEX_EXPORT bool IsEmpty() const;

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String& operator= (const Base_UTF16String& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String& operator= (Base_UTF16String&& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String& operator= (const char* theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String& operator= (const UTF16* theOther);

    //! Assignment operator.
    /*! Copies contents from another string. This syntax may only be used if the build
        environment (i.e. compiler versions and flags) of the customer fully matches one
        of CAD Exchanger. Otherwise syntax with plain pointers should be used.
    */
    __CADEX_EXPORT Base_UTF16String& operator= (const value_type& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String& operator= (const TCollection_AsciiString& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String& operator= (const TCollection_ExtendedString& theOther);

    //! Assignment operator.
    /*! Copies contents from another string. This syntax may only be used if the build
        environment (i.e. compiler versions and flags) of the customer fully matches one
        of CAD Exchanger. Otherwise syntax with plain pointers should be used.
    */
    __CADEX_EXPORT Base_UTF16String& operator= (const std::wstring& theOther);

    //! Assignment operator.
    /*! Copies contents from another string.*/
    __CADEX_EXPORT Base_UTF16String& operator= (const Base_String& theOther);

    //! '+' operator.
    __CADEX_EXPORT Base_UTF16String operator+ (const Base_UTF16String& theOther) const;

    //! Concatenate operator.
    __CADEX_EXPORT Base_UTF16String& operator+= (const Base_UTF16String& theOther);

    //! Converts to another Unicode representation.
    __CADEX_EXPORT operator TCollection_ExtendedString() const;

private:
    void Construct (const char* theOther);
    void Construct (const wchar_t* theOther);
    void Assign (const char* theOther);
    void Assign (const wchar_t* theOther);
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

class Base_UTF16StringHash
{
public:
    __CADEX_EXPORT size_t operator() (const Base_UTF16String& theValue) const;
};

inline std::ostream& operator<< (std::ostream& theStream, const Base_UTF16String& theString)
{ return theStream << theString.ToUTF8(); }

inline std::wostream& operator<< (std::wostream& theStream, const Base_UTF16String& theString)
{ return theStream << theString.ToWString(); }

}

#endif
