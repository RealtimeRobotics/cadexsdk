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


#ifndef _Base_ReaderParameters_HeaderFile
#define _Base_ReaderParameters_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_LengthUnit.hxx>
#include <memory>

namespace cadex {
namespace internal {
class Base_ReaderParametersImpl;
}

class Base_ReaderParameters
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Reserved for internal use.
    typedef std::shared_ptr <internal::Base_ReaderParametersImpl>    ImplPtrType;

    __CADEX_EXPORT bool DelayedConversion() const;

    __CADEX_EXPORT bool& DelayedConversion();

    __CADEX_EXPORT bool ReadPMI() const;

    __CADEX_EXPORT bool& ReadPMI();

#if __CADEX_PREVIEW_SAVE_EXTERNAL_REFERENCE_PATHS
    __CADEX_EXPORT bool SaveExternalReferencePaths() const;

    __CADEX_EXPORT bool& SaveExternalReferencePaths();
#endif

    __CADEX_EXPORT void SetLengthUnit (Base_LengthUnit LengthUnit);

    //! Returns internal implementation object.
    /*! \internal.*/
    internal::Base_ReaderParametersImpl* Impl() const { return myImpl.get(); }

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast<T*> (Impl()); }

    //! Reserved for internal use.
    const ImplPtrType& SharedImpl() const
    { return myImpl; }

protected:

    __CADEX_EXPORT Base_ReaderParameters (internal::Base_ReaderParametersImpl* theImpl);

private:
    ImplPtrType    myImpl;
};

}

#endif
