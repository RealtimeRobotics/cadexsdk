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


#ifndef _ACIS_ReaderParameters_HeaderFile
#define _ACIS_ReaderParameters_HeaderFile

#include <cadex/Base_ReaderParameters.hxx>

namespace cadex {

class ACIS_ReaderParameters : public Base_ReaderParameters
{
public:

    __CADEX_EXPORT ACIS_ReaderParameters();

    __CADEX_EXPORT bool TryCreateSolids() const;

    __CADEX_EXPORT bool& TryCreateSolids();

    __CADEX_EXPORT void SetTryCreateSolids (bool theValue);
};

}

#endif
