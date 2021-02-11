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


#ifndef _ModelData_CurveType_HeaderFile
#define _ModelData_CurveType_HeaderFile

namespace cadex {

enum ModelData_CurveType
{
    ModelData_CT_Line,
    ModelData_CT_Circle,
    ModelData_CT_Ellipse,
    ModelData_CT_Hyperbola,
    ModelData_CT_Parabola,
    ModelData_CT_Bezier,
    ModelData_CT_BSpline,
    ModelData_CT_Offset,
    ModelData_CT_Trimmed,
    ModelData_CT_Undefined = 100,
    ModelData_CT_UserDefined
};

}

#endif
