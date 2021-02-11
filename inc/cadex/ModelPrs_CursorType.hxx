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


#ifndef _ModelPrs_CursorType_HeaderFile
#define _ModelPrs_CursorType_HeaderFile

namespace cadex {

enum ModelPrs_CursorType {
    ModelPrs_CT_DefaultCursor,
    ModelPrs_CT_ZoomCursor,
    ModelPrs_CT_SelectCursor,
    ModelPrs_CT_PanCursor,
    ModelPrs_CT_GlobalPanCursor,
    ModelPrs_CT_RotateCursor,
    ModelPrs_CT_TranslateCursor
};

}

#endif // _ModelPrs_CursorType_HeaderFile
