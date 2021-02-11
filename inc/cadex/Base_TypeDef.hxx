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

#ifndef _Base_TypeDef_HeaderFile
#define _Base_TypeDef_HeaderFile

#include <stdint.h>

namespace cadex {

//! Defines an unsigned 8-bit integer.
typedef unsigned char       U8;

//! Defines an unsigned 16-bit integer.
typedef unsigned short      U16;

//! Defines an unsigned 32-bit integer.
typedef unsigned int        U32;

#if _MSC_VER
//! Defines an unsigned 64-bit integer.
typedef unsigned __int64    U64;
#else
//! Defines an unsigned 64-bit integer.
typedef uint64_t            U64;
#endif


//! Defines a signed 8-bit integer.
typedef char                I8;

//! Defines a signed 16-bit integer.
typedef short               I16;

//! Defines a signed 32-bit integer.
typedef int                 I32;

#if _MSC_VER
//! Defines a signed 64-bit integer.
typedef __int64             I64;
#else
//! Defines a signed 64-bit integer.
typedef int64_t             I64;
#endif

//! Defines a type of character when using UTF-8 encoding.
typedef U8                   UTF8;

//! Defines a type of character when using UTF-16 encoding.
typedef U16                  UTF16;

//! Defines a type of character when using UTF-32 encoding.
typedef U32                  UTF32;

}

#endif
