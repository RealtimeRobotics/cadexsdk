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


#ifndef _Base_Settings_HeaderFile
#define _Base_Settings_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_TypeDef.hxx>
#include <memory>

namespace cadex {

namespace internal {
class Base_SettingsImpl;
}

class Base_Settings
{
public:

    enum Id {
        //range 0 - 99 - for common parameters
        ConcurrentMode,
        Common_ConcurrentMode = ConcurrentMode, //deprecated value, use ConcurrentMode instead
        UseExceptions,
        UserDefined           = 10000
    };

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Returns global settings object.
    __CADEX_EXPORT static const std::shared_ptr<Base_Settings>& Default();

    //! Sets integer parameter value.
    __CADEX_EXPORT void SetValue (const Id theId, int theVal);

    //! Sets double parameter value.
    __CADEX_EXPORT void SetValue (const Id theId, double theVal);

    //! Sets boolean parameter value.
    __CADEX_EXPORT void SetValue (const Id theId, bool theVal);

    //! Sets string parameter value.
    __CADEX_EXPORT void SetValue (const Id theId, const UTF16* theVal);

    //! Returns integer parameter value.
    __CADEX_EXPORT int IntValue (const Id theId, int theDefaultVal) const;

    //! Returns double parameter value.
    __CADEX_EXPORT double DoubleValue (const Id theId, double theDefaultVal) const;

    //! Returns boolean parameter value.
    __CADEX_EXPORT bool BoolValue (const Id theId, bool theDefaultVal) const;

    //! Returns string parameter value.
    __CADEX_EXPORT const UTF16* StringValue (const Id theId,
        const UTF16* theDefaultVal) const;

protected:

    //! Constructor.
    __CADEX_EXPORT Base_Settings();

private:

    std::shared_ptr<internal::Base_SettingsImpl>    myImpl;
};

}

#endif
