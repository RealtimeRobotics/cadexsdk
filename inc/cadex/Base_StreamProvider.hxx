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


#ifndef _Base_StreamProvider_HeaderFile
#define _Base_StreamProvider_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <iostream>
#include <memory>

namespace cadex {

class Base_UTF16String;

template<typename T>
class Base_StreamProvider
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT
    virtual ~Base_StreamProvider() {}
    virtual bool IsOpen() const = 0;
    virtual T& Stream() = 0;
    virtual void Open (const Base_UTF16String& theFileName) = 0;
    virtual void Close() = 0;
};

template<typename T>
class Base_StreamProviderFactory
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT
    virtual ~Base_StreamProviderFactory() {}
    virtual std::shared_ptr<Base_StreamProvider<T>> Create (const Base_UTF16String& theFileName) = 0;
    virtual std::shared_ptr<Base_StreamProvider<T>> Create() = 0;
};


typedef Base_StreamProvider<std::istream>           Base_IStreamProvider;
typedef Base_StreamProviderFactory<std::istream>    Base_IStreamProviderFactory;

}

#endif
