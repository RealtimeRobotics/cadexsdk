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


#ifndef _JT_WriterParameters_HeaderFile
#define _JT_WriterParameters_HeaderFile

#include <cadex/Base_LengthUnit.hxx>
#include <cadex/Base_WriterParameters.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>


namespace cadex {

class JT_WriterParameters : public Base_WriterParameters
{
public:

    enum FileSplitModeType {
        Monolithic,
        PerPart,
        Shattered
    };

    enum LayerConversionType {
        None,
        LayerFilter,
        RefSet
    };

    __CADEX_EXPORT JT_WriterParameters();

    __CADEX_EXPORT void SetFileSplitMode (FileSplitModeType theMode);
    __CADEX_EXPORT FileSplitModeType FileSplitMode() const;

    __CADEX_EXPORT LayerConversionType LayerConversionMode() const;
    __CADEX_EXPORT LayerConversionType& LayerConversionMode();

    __CADEX_EXPORT const ModelAlgo_BRepMesherParameters& MesherParameters() const;
    __CADEX_EXPORT ModelAlgo_BRepMesherParameters& MesherParameters();

    __CADEX_EXPORT bool SaveBRepRepresentation() const;
    __CADEX_EXPORT bool& SaveBRepRepresentation();

    __CADEX_EXPORT bool SavePolyRepresentation() const;
    __CADEX_EXPORT bool& SavePolyRepresentation();

    __CADEX_EXPORT Base_LengthUnit PolyRepresentationUnit() const;
    __CADEX_EXPORT Base_LengthUnit& PolyRepresentationUnit();

    __CADEX_EXPORT bool OverrideInstanceNames() const;
    __CADEX_EXPORT bool& OverrideInstanceNames();
};

}

#endif
