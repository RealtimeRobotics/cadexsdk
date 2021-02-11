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


#ifndef _ModelPrs_SelectionMode_HeaderFile
#define _ModelPrs_SelectionMode_HeaderFile

namespace cadex {

enum ModelPrs_SelectionMode
{
    ModelPrs_SM_None      = 0x00,
    ModelPrs_SM_Node      = 0x01,
    ModelPrs_SM_Solid     = 0x02,
    ModelPrs_SM_Shell     = 0x04,
    ModelPrs_SM_Face      = 0x08,
    ModelPrs_SM_Wire      = 0x10,
    ModelPrs_SM_Edge      = 0x20,
    ModelPrs_SM_Vertex    = 0x40,
    ModelPrs_SM_Undefined = 0x8000
};

}

#endif // _ModelPrs_SelectionMode_HeaderFile
