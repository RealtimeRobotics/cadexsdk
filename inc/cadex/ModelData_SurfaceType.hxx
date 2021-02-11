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


#ifndef _ModelData_SurfaceType_HeaderFile
#define _ModelData_SurfaceType_HeaderFile

namespace cadex {

enum ModelData_SurfaceType
{
    ModelData_ST_Plane,
    ModelData_ST_Cylinder,
    ModelData_ST_Cone,
    ModelData_ST_Sphere,
    ModelData_ST_Torus,
    ModelData_ST_LinearExtrusion,
    ModelData_ST_Revolution,
    ModelData_ST_Bezier,
    ModelData_ST_BSpline,
    ModelData_ST_Offset,
    ModelData_ST_Trimmed,
    ModelData_SrfT_Undefined = 100, //to avoid name collision with ShapeType
    ModelData_ST_UserDefined
};

}

#endif
