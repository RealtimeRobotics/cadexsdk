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


#ifndef _Base_Handle_HeaderFile
#define _Base_Handle_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <algorithm>
#include <assert.h>


namespace cadex {
namespace internal {

class Base_HandledObject;

class Base_Handle
{
public:

    typedef const Base_HandledObject*   ConstPointerType;
    typedef const Base_HandledObject&   ConstReferenceType;
    typedef Base_HandledObject*         PointerType;
    typedef Base_HandledObject&         ReferenceType;

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    Base_Handle() : myObject (nullptr)
    {}

    //! Constructor.
    Base_Handle (const Base_Handle& theOther) :
        myObject (theOther.myObject)
    {
        Increment();
    }

    //! Constructor.
    Base_Handle (Base_Handle&& theOther) :
        myObject (theOther.myObject)
    {
        theOther.myObject = nullptr;
    }

    //! Constructor.
    explicit Base_Handle (ConstPointerType theObject) :
        myObject (const_cast<PointerType> (theObject))
    {
        Increment();
    }

    //! Destructor
    ~Base_Handle()
    {
        reset();
    }

    //! Assignment operator.
    Base_Handle& operator= (const Base_Handle& theOther)
    {
        Copy (theOther.get());
        return *this;
    }

    //! Assignment operator.
    Base_Handle& operator= (Base_Handle&& theOther)
    {
        std::swap (myObject, theOther.myObject);
        return *this;
    }

    //! Assignment operator.
    Base_Handle& operator= (ConstPointerType theObject)
    {
        Copy (theObject);
        return *this;
    }

    void reset()
    {
        Decrement();
        myObject = nullptr;
    }

    operator bool() const
    {
        return !IsNull();
    }

    PointerType get() const
    {
        return myObject;
    }

    PointerType operator->() const
    {
        assert (!IsNull());
        return myObject;
    }

    ReferenceType operator*() const
    {
        assert (!IsNull());
        return *myObject;
    }

    __CADEX_EXPORT int use_count() const;

private:

    bool IsNull() const
    {
        return myObject == nullptr;
    }

    void Copy (ConstPointerType theObject)
    {
        if (myObject == theObject)
            return;

        Decrement();
        myObject = const_cast<PointerType> (theObject);
        Increment();
    }

    __CADEX_EXPORT void Increment();
    __CADEX_EXPORT void Decrement();

private:
    PointerType myObject;
};

inline bool operator== (const Base_Handle& theH1, const Base_Handle& theH2)
{
    return theH1.get() == theH2.get();
}

inline bool operator== (const Base_Handle& theH1, Base_Handle::ConstPointerType theP2)
{
    return theH1.get() == theP2;
}

inline bool operator!= (const Base_Handle& theH1, const Base_Handle& theH2)
{
    return theH1.get() != theH2.get();
}

inline bool operator!= (const Base_Handle& theH1, Base_Handle::ConstPointerType theP2)
{
    return theH1.get() != theP2;
}

struct Base_HandleHash
{
    __CADEX_EXPORT size_t operator() (const Base_Handle& theHandle) const;
};

}}

#endif
