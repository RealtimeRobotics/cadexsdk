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


#ifndef _ModelData_BodyType_HeaderFile
#define _ModelData_BodyType_HeaderFile

namespace cadex {

enum ModelData_BodyType
{
    ModelData_BT_Undefined,
    ModelData_BT_Acorn,
    ModelData_BT_Wireframe,
    ModelData_BT_Sheet,
    ModelData_BT_Solid,
    ModelData_BT_General //reserved for the future, not used
};

}

#endif
