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


#ifndef _Base_SharedPtr_HeaderFile
#define _Base_SharedPtr_HeaderFile

#if __GNUC__ && (!__GXX_EXPERIMENTAL_CXX0X__ && __cplusplus < 201103L)
/* __GXX_EXPERIMENTAL_CXX0X__ is defined when using -std=c++0x or -std=c++11.
   So the above test works for compiler which supports both std::shared_ptr and
   std::tr1::shared_ptr, for instance gcc4.4.7.
*/
#include <tr1/memory>
namespace std
{
using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
}

#else

#include <memory>
#if defined(_MSC_VER) && _MSC_VER == 1500
namespace std
{
using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
}
#endif
#endif

#endif
