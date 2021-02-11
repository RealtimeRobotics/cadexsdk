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


#ifndef _ModelPrs_DisplayMode_HeaderFile
#define _ModelPrs_DisplayMode_HeaderFile

namespace cadex {

enum ModelPrs_DisplayMode
{
    ModelPrs_DM_Wireframe                    = 0,
    ModelPrs_DM_Shaded,
    ModelPrs_DM_ShadedWithBoundaries,
    ModelPrs_DM_SurfaceWireframe,
    ModelPrs_DM_ShadedWithSurfaceBoundaries,
    ModelPrs_DM_Undefined                    = 100,
};

}

#endif // _ModelPrs_DisplayMode_HeaderFile
