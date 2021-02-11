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


#ifndef _ModelPrs_View3dPlaneTrihedron_HeaderFile
#define _ModelPrs_View3dPlaneTrihedron_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION

#include <cadex/ModelPrs_View3dObject.hxx>

namespace cadex {
class ModelData_Axis1Placement;
class ModelData_Line;

class ModelPrs_View3dAxis : public cadex::ModelPrs_View3dObject
{
public:
    __CADEX_EXPORT ModelPrs_View3dAxis (const cadex::ModelData_Axis1Placement& theAxis, double theLength);

    __CADEX_EXPORT ModelPrs_View3dAxis (const cadex::ModelData_Line& theLine, double theLength);
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_View3dPlaneTrihedron_HeaderFile
