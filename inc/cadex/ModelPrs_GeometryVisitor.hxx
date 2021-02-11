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


#ifndef _ModelPrs_GeometryVisitor_HeaderFile
#define _ModelPrs_GeometryVisitor_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION

namespace cadex {
class ModelData_BRepRepresentation;
class ModelData_Body;
class ModelData_PMIGraphicalElement;
class ModelData_PolyRepresentation;
class ModelData_PolyVertexSet;
class ModelPrs_Measurement;

class ModelPrs_GeometryVisitor
{
public:
    __CADEX_EXPORT virtual ~ModelPrs_GeometryVisitor();
    virtual void Visit (const ModelData_Body& theShape, const ModelData_BRepRepresentation& theRep) = 0;
    virtual void Visit (const ModelData_BRepRepresentation& theRep) = 0;
    virtual void Visit (const ModelData_PolyVertexSet& thePVS) = 0;
    virtual void Visit (const ModelData_PolyRepresentation& theRep) = 0;
    virtual void Visit (const ModelPrs_Measurement& theMeasurement) = 0;
    virtual void Visit (const ModelData_PMIGraphicalElement& thePMIGraphicalElement) = 0;
};

class ModelPrs_GeometryVoidVisitor : public ModelPrs_GeometryVisitor
{
public:
    __CADEX_EXPORT void Visit (const ModelData_Body& theShape, const ModelData_BRepRepresentation& theRep) override;
    __CADEX_EXPORT void Visit (const ModelData_BRepRepresentation& theRep) override;
    __CADEX_EXPORT void Visit (const ModelData_PolyVertexSet& thePVS) override;
    __CADEX_EXPORT void Visit (const ModelData_PolyRepresentation& theRep) override;
    __CADEX_EXPORT void Visit (const ModelPrs_Measurement& theMeasurement) override;
    __CADEX_EXPORT void Visit (const ModelData_PMIGraphicalElement& thePMIGraphicalElement) override;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_GeometryVisitor_HeaderFile
