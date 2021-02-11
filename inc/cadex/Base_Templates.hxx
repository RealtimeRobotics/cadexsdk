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


#ifndef _Base_Templates_HeaderFile
#define _Base_Templates_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>
#include <cadex/Base_String.hxx>
#include <cadex/Base_UTF16String.hxx>
#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_BaseObject.hxx>

#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


/* This file contains a collection of STL redefinitions with forced use of CAD Exchanger's memory allocator.
   Using them in conjunction with CAD Exchanger's code may improve performance.
   Usage examples:

       cadex_vector<int>::type aCadexIntVector;
       cadex_string aCadexString = "Hello, World!";
*/

namespace cadex {
namespace internal {

template <typename T, typename = void>
struct CadexHash
{
    size_t operator() (const T& theVal) const
    { return std::hash<T>() (theVal); }
};

#if __GNUC__ && __CADEX_GCC_VER <= 50400 /* GCC 5.4.0 */
template <typename T>
struct CadexHash <T, typename std::enable_if <std::is_enum<T>::value>::type>
{
    size_t operator() (T theVal) const
    { return CadexHash <typename std::underlying_type<T>::type>() (theVal); }
};
#endif

#if _MSC_VER && _MSC_VER <= 1600 /* Visual Studio 2010 */
template <typename T>
struct CadexHash <std::shared_ptr<T> >
{
    size_t operator() (const std::shared_ptr<T>& thePtr) const
    { return CadexHash<T*>() (thePtr.get()); }
};
#endif

template<>
struct CadexHash <ModelData_BaseObject>
{
    size_t operator() (const ModelData_BaseObject& theObj) const
    { return ModelData_BaseObjectHash() (theObj); }
};

template<>
struct CadexHash <ModelData_Appearance>
{
    size_t operator() (const ModelData_Appearance& theAppearance) const
    { return ModelData_AppearanceHash() (theAppearance); }
};

template<>
struct CadexHash <Base_String>
{
    size_t operator() (const Base_String& theValue) const
    { return Base_StringHash() (theValue); }
};

template<>
struct CadexHash <Base_UTF16String>
{
    size_t operator() (const Base_UTF16String& theValue) const
    { return Base_UTF16StringHash() (theValue); }
};

template <typename T, typename = void>
struct CadexEqual
{
    bool operator() (const T& theVal1, const T& theVal2) const
    { return std::equal_to<T>() (theVal1, theVal2); }
};

template <typename Key,
    typename Val,
    typename Comp = std::less<Key> >
struct cadex_map
{
    typedef std::map <Key, Val, Comp, Base_Allocator <std::pair <const Key, Val> > >    type;
};

// std::unordered_map with CAD Exchanger's allocator.
template <typename Key,
    typename Val,
    typename Hash = CadexHash<Key>,
    typename Comp = CadexEqual<Key> >
struct cadex_unordered_map
{
    typedef std::unordered_map <Key, Val, Hash, Comp, Base_Allocator <std::pair <const Key, Val> > >    type;
};

// std::unordered_multimap with CAD Exchanger's allocator.
template <typename Key,
    typename Val,
    typename Hash = CadexHash<Key>,
    typename Comp = CadexEqual<Key> >
struct cadex_unordered_multimap
{
    typedef std::unordered_multimap <Key, Val, Hash, Comp, Base_Allocator <std::pair <const Key, Val> > >   type;
};

// std::unordered_set with CAD Exchanger's allocator.
template <typename Key,
    typename Hash = CadexHash<Key>,
    typename Comp = CadexEqual<Key> >
struct cadex_unordered_set
{
    typedef std::unordered_set <Key, Hash, Comp, Base_Allocator <Key> > type;
};

// std::unordered_multiset with CAD Exchanger's allocator.
template <typename Key,
    typename Hash = CadexHash<Key>,
    typename Comp = CadexEqual<Key> >
struct cadex_unordered_multiset
{
    typedef std::unordered_multiset <Key, Hash, Comp, Base_Allocator <Key> > type;
};

// std::set with CAD Exchanger's allocator
template <typename T, typename Comp = std::less<T>>
struct cadex_set
{
    typedef std::set <T, Comp, Base_Allocator<T> >    type;
};

// std::multimap with CAD Exchanger's allocator.
template <typename Key, typename Val>
struct cadex_multimap
{
    typedef std::multimap <Key, Val, std::less<Key>, Base_Allocator <std::pair <const Key, Val> > >    type;
};

// std::vector with CAD Exchanger's allocator.
template <typename T>
struct cadex_vector
{
    typedef std::vector <T, Base_Allocator<T> >    type;
};

// std::list with CAD Exchanger's allocator.
template <typename T>
struct cadex_list
{
    typedef std::list <T, Base_Allocator<T> >    type;
};

// std::basic_string with CAD Exchanger's allocator.
template <typename T>
struct cadex_basic_string
{
    typedef std::basic_string <T, std::char_traits<T>, Base_Allocator<T> >    type;
};

// std::string with CAD Exchanger's allocator.
typedef cadex_basic_string<char>::type  cadex_string;

struct cadex_stringstream
{
    typedef std::basic_stringstream<
        cadex_string::value_type,
        cadex_string::traits_type,
        cadex_string::allocator_type>     type;
};

}}

#endif
