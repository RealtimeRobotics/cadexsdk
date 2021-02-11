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


#ifndef _ModelData_RepresentationMask_HeaderFile
#define _ModelData_RepresentationMask_HeaderFile

namespace cadex {

enum ModelData_RepresentationMask
{
    ModelData_RM_BRep         = 0x01,
    ModelData_RM_CoarseLOD    = 0x10,
    ModelData_RM_MediumLOD    = 0x20,
    ModelData_RM_FineLOD      = 0x40,
    ModelData_RM_Poly         = ModelData_RM_CoarseLOD | ModelData_RM_MediumLOD | ModelData_RM_FineLOD,
    ModelData_RM_Any          = ModelData_RM_BRep | ModelData_RM_Poly,
};

}

#endif
