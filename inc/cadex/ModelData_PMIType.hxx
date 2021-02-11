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


#ifndef _ModelData_PMIType_HeaderFile
#define _ModelData_PMIType_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

namespace cadex {

enum ModelData_PMIType
{
    ModelData_PMI_Note,
    ModelData_PMI_Dimension,
    ModelData_PMI_Tolerance,
    ModelData_PMI_CoordinateSystem,
    ModelData_PMI_CenterLine,
    ModelData_PMI_ReferenceGeometry,
    ModelData_PMI_MeasurementPoint,
    ModelData_PMI_Datum,
    ModelData_PMI_FeatureControlFrame,
    ModelData_PMI_Weld,
    ModelData_PMI_SurfaceFinish,
    ModelData_PMI_Section,
    ModelData_PMI_Undefined = 1000,
    ModelData_PMI_UserDefined
};

}

#endif // __CADEX_PREVIEW_PMI
#endif
