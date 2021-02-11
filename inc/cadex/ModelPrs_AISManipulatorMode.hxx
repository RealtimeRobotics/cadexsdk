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


#ifndef _ModelPrs_AISManipulatorMode_HeaderFile
#define _ModelPrs_AISManipulatorMode_HeaderFile

namespace cadex {
typedef int ManipulatorModes;

enum ModelPrs_AISManipulatorMode
{
    ModelPrs_AISMM_None = 0x00,
    ModelPrs_AISMM_Translation = 0x01,
    ModelPrs_AISMM_Rotation = 0x02
};
}

#endif // _ModelPrs_AISManipulatorMode_HeaderFile
