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


#ifndef _STEP_WriterParameters_HeaderFile
#define _STEP_WriterParameters_HeaderFile

#include <cadex/Base_WriterParameters.hxx>


namespace cadex {

class STEP_WriterParameters : public Base_WriterParameters
{
public:

    enum VersionType {
        V1 = 1,
        V2 = 2
    };

    enum BRepRepresentationType {
        Auto,
        AdvancedBRep,
        ManifoldSurface,
        NonManifoldSurface,
        EdgeBasedWireframe,
    };

    enum ExternalReferencesModeType {
        Monolithic,
        PerPart,
        PerAssembly
    };

    __CADEX_EXPORT STEP_WriterParameters();

    __CADEX_EXPORT BRepRepresentationType  PreferredBRepRepresentationType() const;
    __CADEX_EXPORT BRepRepresentationType& PreferredBRepRepresentationType();

    __CADEX_EXPORT ExternalReferencesModeType  ExternalReferencesMode() const;
    __CADEX_EXPORT ExternalReferencesModeType& ExternalReferencesMode();

    __CADEX_EXPORT VersionType  Version() const;
    __CADEX_EXPORT VersionType& Version();

    __CADEX_EXPORT bool  WritePCurves() const;
    __CADEX_EXPORT bool& WritePCurves();
};

}

#endif
