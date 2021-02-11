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


#ifndef _Base_PublicObject_HeaderFile
#define _Base_PublicObject_HeaderFile

#include <cadex/Base_Handle.hxx>


namespace cadex {

class Base_PublicObject
{
public:

    struct initialized {};

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    Base_PublicObject() {}

    __CADEX_EXPORT ~Base_PublicObject();

    __CADEX_EXPORT void Nullify();

    __CADEX_EXPORT bool IsNull() const;

#if _MSC_VER > 1700
    explicit operator bool() const { return !IsNull(); }
#else
    operator bool() const { return !IsNull(); }
#endif

    __CADEX_EXPORT internal::Base_HandledObject* Impl() const;

    const internal::Base_Handle& HImpl() const { return myImpl; }

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast<T*> (Impl()); }

    bool operator== (const Base_PublicObject& theObject) const
    {
        return theObject.HImpl() == myImpl;
    }

    bool operator!= (const Base_PublicObject& theObject) const
    {
        return theObject.HImpl() != myImpl;
    }

protected:

    __CADEX_EXPORT explicit Base_PublicObject (const internal::Base_HandledObject* theObject);

    //! Reserved for internal use.
    template<typename T>
    T* GetOrCreateImpl()
    {
        if (IsNull()) {
            myImpl = new T;
        }
        return Impl<T>();
    }

private:

    internal::Base_Handle   myImpl;
};

class Base_PublicObjectHash
{
public:
    size_t operator() (const Base_PublicObject& theObject) const
    {
        return internal::Base_HandleHash() (theObject.HImpl());
    }
};

}

#endif
