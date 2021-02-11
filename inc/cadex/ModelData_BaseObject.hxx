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


#ifndef _ModelData_BaseObject_HeaderFile
#define _ModelData_BaseObject_HeaderFile

#include <cadex/Base_Handle.hxx>

namespace cadex {
namespace internal {
class ModelData_ImplTool;
class ModelData_BaseObjectImpl;
}

class Base_UTF16String;
class Base_Uuid;

class ModelData_BaseObject
{
public:

    struct initialized {};

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Defines a type identifier.
    typedef int IdType;

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_BaseObject() {}

    __CADEX_EXPORT ~ModelData_BaseObject();

    __CADEX_EXPORT IdType TypeId() const;

    //! Returns true if the object has a type \a T.
    /*! Helper method which uses static method T::GetTypeId() to compare with value returned by
        virtual method TypeId().
    */
    template <typename T>
    bool IsOfType() const
    { return TypeId() == T::GetTypeId(); }

    __CADEX_EXPORT void SetName (const Base_UTF16String& theName);
    __CADEX_EXPORT Base_UTF16String Name() const;

    __CADEX_EXPORT void SetUuid (const Base_Uuid& theUuid);
    __CADEX_EXPORT Base_Uuid Uuid() const;

    __CADEX_EXPORT void Nullify();

    __CADEX_EXPORT bool IsNull() const;

    operator bool() const { return !IsNull(); }

    __CADEX_EXPORT internal::ModelData_BaseObjectImpl* Impl() const;

    const internal::Base_Handle& HImpl() const { return myImpl; }

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast<T*> (Impl()); }

protected:

    //! Constructor (reserved for internal use).
    __CADEX_EXPORT ModelData_BaseObject (const internal::ModelData_BaseObjectImpl* theImpl);

    //! Constructor (reserved for internal use).
    __CADEX_EXPORT ModelData_BaseObject (const internal::ModelData_BaseObjectImpl* theImpl,
        const Base_UTF16String& theName);

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
    friend class internal::ModelData_ImplTool;
};

inline bool operator== (const ModelData_BaseObject& theO1, const ModelData_BaseObject& theO2)
{
    return theO1.HImpl() == theO2.HImpl();
}

inline bool operator!= (const ModelData_BaseObject& theO1, const ModelData_BaseObject& theO2)
{
    return theO1.HImpl() != theO2.HImpl();
}

class ModelData_BaseObjectHash
{
public:
    size_t operator() (const ModelData_BaseObject& theValue) const
    { return internal::Base_HandleHash() (theValue.HImpl()); }
};

}

#endif
