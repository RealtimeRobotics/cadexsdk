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


#ifndef _STEP_ReaderParameters_HeaderFile
#define _STEP_ReaderParameters_HeaderFile

#include <cadex/Base_ReaderParameters.hxx>

namespace cadex {

class STEP_ReaderParameters : public Base_ReaderParameters
{
public:

    enum VersionType {
        V1 = 1,
        V2 = 2
    };

    enum BRepRepresentationType {
        Auto,
        All,
        AdvancedBRep,
        ManifoldSurface,
        NonManifoldSurface,
        EdgeBasedWireframe
    };

    __CADEX_EXPORT STEP_ReaderParameters();
    
    __CADEX_EXPORT BRepRepresentationType  PreferredBRepRepresentationType() const;
    __CADEX_EXPORT BRepRepresentationType& PreferredBRepRepresentationType();
    
    __CADEX_EXPORT VersionType  Version() const;
    __CADEX_EXPORT VersionType& Version();
};

}

#endif
