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

#ifndef _Base_Uuid_HeaderFile
#define _Base_Uuid_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_Allocator.hxx>

#include <array>
#include <cstdint>
#include <iosfwd>

namespace cadex {

class Base_String;

class Base_Uuid
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    typedef uint8_t                     ValueType;
    typedef std::array<ValueType, 16>   DataType;

    Base_Uuid() : myData ({{ 0 }}) {}

    __CADEX_EXPORT explicit Base_Uuid (const ValueType* theData);

    explicit Base_Uuid (DataType theData) : myData (std::move (theData)) {}

    const DataType& Data() const { return myData; }

    __CADEX_EXPORT bool IsNull() const;

    operator bool() const { return !IsNull(); }

    __CADEX_EXPORT bool operator== (const Base_Uuid& theOther) const;

    bool operator!= (const Base_Uuid& theOther) const { return !operator== (theOther); }

    __CADEX_EXPORT Base_String ToString() const;

    __CADEX_EXPORT static Base_Uuid FromString (const Base_String& theStr);

    __CADEX_EXPORT static Base_Uuid CreateRandom();

private:
    DataType myData;
};

class Base_UuidHash
{
public:
    __CADEX_EXPORT size_t operator() (const Base_Uuid& theValue) const;
};

__CADEX_EXPORT std::ostream& operator<< (std::ostream& theStream, const Base_Uuid& theUuid);
__CADEX_EXPORT std::wostream& operator<< (std::wostream& theStream, const Base_Uuid& theUuid);

}
#endif
