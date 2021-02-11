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

#ifndef _Base_SEHOwner_HeaderFile
#define _Base_SEHOwner_HeaderFile

#include <cadex/Base_Macro.hxx>

namespace cadex {

namespace internal {
    class Base_SEHOwnerImpl;
}

class Base_SEHOwner
{
public:

    //! Constructor.
    __CADEX_EXPORT Base_SEHOwner (bool theFPE = false);

    //! Destructor.
    __CADEX_EXPORT ~Base_SEHOwner ();

private:

    Base_SEHOwner (const Base_SEHOwner&);
    Base_SEHOwner& operator= (const Base_SEHOwner&);
    internal::Base_SEHOwnerImpl*    myImpl;
};

}

#endif
