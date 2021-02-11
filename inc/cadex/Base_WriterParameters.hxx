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


#ifndef _Base_WriterParameters_HeaderFile
#define _Base_WriterParameters_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_LengthUnit.hxx>
#include <cadex/ModelData_RepresentationMask.hxx>

#include <memory>


namespace cadex {
class Base_UTF16String;

namespace internal {
class Base_WriterParametersImpl;
}

class Base_WriterParameters
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Reserved for internal use.
    typedef std::shared_ptr <internal::Base_WriterParametersImpl>    ImplPtrType;

    __CADEX_EXPORT bool WriteBRepRepresentation() const;
    __CADEX_EXPORT bool& WriteBRepRepresentation();

    __CADEX_EXPORT bool WritePolyRepresentation() const;
    __CADEX_EXPORT bool& WritePolyRepresentation();

    __CADEX_EXPORT bool WriteTextures() const;
    __CADEX_EXPORT bool& WriteTextures();

    __CADEX_EXPORT bool WritePMI() const;
    __CADEX_EXPORT bool& WritePMI();

    __CADEX_EXPORT Base_LengthUnit  LengthUnit() const;
    __CADEX_EXPORT Base_LengthUnit& LengthUnit();

    __CADEX_EXPORT ModelData_RepresentationMask  PreferredLOD() const;
    __CADEX_EXPORT ModelData_RepresentationMask& PreferredLOD();

    __CADEX_EXPORT const Base_UTF16String& Author() const;
    __CADEX_EXPORT Base_UTF16String&       Author();

    __CADEX_EXPORT const Base_UTF16String& Organization() const;
    __CADEX_EXPORT Base_UTF16String&       Organization();

    __CADEX_EXPORT const Base_UTF16String& OriginatingSystem() const;
    __CADEX_EXPORT Base_UTF16String&       OriginatingSystem();

    //! Returns internal implementation object.
    /*! \internal.*/
    internal::Base_WriterParametersImpl* Impl() const { return myImpl.get(); }

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast<T*> (Impl()); }

    //! Reserved for internal use.
    const ImplPtrType& SharedImpl() const
    { return myImpl; }

protected:

    __CADEX_EXPORT Base_WriterParameters (internal::Base_WriterParametersImpl* theImpl);

private:
    ImplPtrType myImpl;
};

}

#endif
