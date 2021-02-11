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


#ifndef _ModelPrs_CameraPositionType_HeaderFile
#define _ModelPrs_CameraPositionType_HeaderFile

namespace cadex {

enum ModelPrs_CameraPositionType
{
    ModelPrs_CMT_Xpos,
    ModelPrs_CMT_Ypos,
    ModelPrs_CMT_Zpos,
    ModelPrs_CMT_Xneg,
    ModelPrs_CMT_Yneg,
    ModelPrs_CMT_Zneg,
    ModelPrs_CMT_XposYpos,
    ModelPrs_CMT_XposZpos,
    ModelPrs_CMT_YposZpos,
    ModelPrs_CMT_XnegYneg,
    ModelPrs_CMT_XnegYpos,
    ModelPrs_CMT_XnegZneg,
    ModelPrs_CMT_XnegZpos,
    ModelPrs_CMT_YnegZneg,
    ModelPrs_CMT_YnegZpos,
    ModelPrs_CMT_XposYneg,
    ModelPrs_CMT_XposZneg,
    ModelPrs_CMT_YposZneg,
    ModelPrs_CMT_XposYposZpos,
    ModelPrs_CMT_XposYnegZpos,
    ModelPrs_CMT_XposYposZneg,
    ModelPrs_CMT_XnegYposZpos,
    ModelPrs_CMT_XposYnegZneg,
    ModelPrs_CMT_XnegYposZneg,
    ModelPrs_CMT_XnegYnegZpos,
    ModelPrs_CMT_XnegYnegZneg,
    // Aliases
    ModelPrs_CMT_Front   = ModelPrs_CMT_Xpos,
    ModelPrs_CMT_Back    = ModelPrs_CMT_Xneg,
    ModelPrs_CMT_Top     = ModelPrs_CMT_Zpos,
    ModelPrs_CMT_Bottom  = ModelPrs_CMT_Zneg,
    ModelPrs_CMT_Left    = ModelPrs_CMT_Yneg,
    ModelPrs_CMT_Right   = ModelPrs_CMT_Ypos,
    ModelPrs_CMT_Default = ModelPrs_CMT_XposYnegZpos
};

}

#endif // _ModelPrs_CameraPositionType_HeaderFile
