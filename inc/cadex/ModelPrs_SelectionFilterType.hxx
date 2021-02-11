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


#ifndef _ModelPrs_SelectionFilterType_HeaderFile
#define _ModelPrs_SelectionFilterType_HeaderFile

namespace cadex {

enum ModelPrs_SelectionFilterType
{
    ModelPrs_SFT_None                = 0x00,
    ModelPrs_SFT_CircleEdgeFilter    = 0x01,
    ModelPrs_SFT_PlanarFaceFilter    = 0x02,
    ModelPrs_SFT_RevolFaceFilter     = 0x04
};

}

#endif // _ModelPrs_SelectionFilterType_HeaderFile
