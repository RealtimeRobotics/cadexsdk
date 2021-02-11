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


#ifndef _JT_ReaderParameters_HeaderFile
#define _JT_ReaderParameters_HeaderFile

#include <cadex/Base_ReaderParameters.hxx>

namespace cadex {

class JT_ReaderParameters : public Base_ReaderParameters
{
public:

    enum LayerConversionType {
        None,
        LayerFilter,
        RefSet
    };

    __CADEX_EXPORT JT_ReaderParameters();

    __CADEX_EXPORT LayerConversionType LayerConversionMode() const;
    __CADEX_EXPORT LayerConversionType& LayerConversionMode();
};

}

#endif
