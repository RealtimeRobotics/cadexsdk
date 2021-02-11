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


#ifndef _ModelPrs_GeometryType_HeaderFile
#define _ModelPrs_GeometryType_HeaderFile

enum ModelPrs_GeometryType
{
    ModelPrs_GT_Body,
    ModelPrs_GT_BRepRepresentation,
    ModelPrs_GT_PolyVertexSet,
    ModelPrs_GT_PolyRepresentation,
    ModelPrs_GT_Measurement,
    ModelPrs_GT_PMI,
    ModelPrs_GT_Undefined = 100
};

#endif // _ModelPrs_GeometryType_HeaderFile
