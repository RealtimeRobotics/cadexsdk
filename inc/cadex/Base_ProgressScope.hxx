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


#ifndef _Base_ProgressScope_HeaderFile
#define _Base_ProgressScope_HeaderFile

#include <cadex/Base_ProgressStatus.hxx>

namespace cadex {

namespace internal {
class Base_ProgressScopeImpl;
}

class Base_ProgressScope
{
public:

    //! Defines a type of the progress status value and ranges.
    
    typedef Base_ProgressStatus::ValueType ValueType;

    //! Defines a type of the progress status value and ranges.
    typedef ValueType                       value_type;

    //! Constructor.
    __CADEX_EXPORT Base_ProgressScope (const Base_ProgressStatus& theStatus,
        ValueType theScaleInParent = -1);

    //! Constructor.
    __CADEX_EXPORT Base_ProgressScope (const Base_ProgressScope& theStatus, ValueType theScaleInParent);

    //! Destructor.
    __CADEX_EXPORT ~Base_ProgressScope();

    //! Returns a current value.
    __CADEX_EXPORT value_type Value() const;

    //! Set the scope range.
    __CADEX_EXPORT void SetRange (value_type theMin, value_type theMax);

    //! Set the scope range.
    template <typename T1, typename T2>
    void SetRange (T1 theMin, T2 theMax)
    { SetRange (static_cast<value_type> (theMin), static_cast<value_type> (theMax)); }

    //! Set the scope range.
    template <typename T>
    void SetRange (T theMax)
    { SetRange (0, theMax); }

    //! Returns a minimum value.
    __CADEX_EXPORT value_type MinValue() const;

    //! Returns a maximum value.
    __CADEX_EXPORT value_type MaxValue() const;

    //! Returns an owning progress status object.
    __CADEX_EXPORT Base_ProgressStatus Owner() const;

private:

#if !defined(SWIG) && !defined(__CADEX_CADEXCORE_DLL)
    //must always be on stack
    void* operator new (size_t theSize);
    void* operator new[] (size_t theSize);
    void* operator new (size_t, void* theAddress);
#endif

    Base_ProgressScope();
    Base_ProgressScope (const Base_ProgressScope&);
    Base_ProgressScope& operator= (const Base_ProgressScope&);
    const cadex::internal::Base_ProgressScopeImpl& Impl() const;
    cadex::internal::Base_ProgressScopeImpl& Impl();

    static const size_t myImplSize = 256;
    union ImplMemory
    {
        void*   myAlign;
        char    myBuf[myImplSize];
    }   myImplMemory;

    friend class internal::Base_ProgressScopeImpl;
};

}

#endif
