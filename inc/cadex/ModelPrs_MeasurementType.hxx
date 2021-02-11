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


#ifndef _ModelPrs_MeasurementType_HeaderFile
#define _ModelPrs_MeasurementType_HeaderFile

namespace cadex {

enum ModelPrs_MeasurementType {
    ModelPrs_MT_Distance,
    ModelPrs_MT_Radius,
    ModelPrs_MT_Diameter,
    ModelPrs_MT_AngleBetweenPlanes,
    ModelPrs_MT_AngleBetweenVertexes,
    ModelPrs_MT_Undefined             = 100
};

}

#endif // _ModelPrs_MeasurementType_HeaderFile
