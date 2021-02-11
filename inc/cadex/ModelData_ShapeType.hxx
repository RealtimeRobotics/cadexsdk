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


#ifndef _ModelData_ShapeType_HeaderFile
#define _ModelData_ShapeType_HeaderFile

namespace cadex {

enum ModelData_ShapeType
{
    ModelData_ST_BodyList,
    ModelData_ST_Body,
    ModelData_ST_Solid = 2,
    ModelData_ST_Shell,
    ModelData_ST_Face,
    ModelData_ST_Wire,
    ModelData_ST_Edge,
    ModelData_ST_Vertex,
    ModelData_ST_Undefined
};

}

#endif
