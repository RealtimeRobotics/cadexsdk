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


#ifndef _ModelAlgo_BRepMesher_HeaderFile
#define _ModelAlgo_BRepMesher_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>

namespace cadex {

class Base_ProgressStatus;
class Mesh_SMDS;
class ModelAlgo_BRepMesherParameters;
class ModelData_PolyShape;
class ModelData_PolyShapeList;
class ModelData_BRepRepresentation;
class ModelData_Model;
class ModelData_PolyRepresentation;
class ModelData_SceneGraphElement;
class ModelData_Body;

namespace internal {

class ModelAlgo_BRepMesherImpl;
class ModelData_SceneGraphElementFilter;
}


class ModelAlgo_BRepMesher
{
public:

    //! Defines a mesher parameters type.
    typedef ModelAlgo_BRepMesherParameters  ParametersType;

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_BRepMesher();

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_BRepMesher (const ModelAlgo_BRepMesherParameters& theParameters);

    //! Returns parameters.
    __CADEX_EXPORT const ModelAlgo_BRepMesherParameters& Parameters() const;

    //! Returns parameters.
    __CADEX_EXPORT ModelAlgo_BRepMesherParameters& Parameters();

    __CADEX_EXPORT void Compute (const ModelData_Model& theModel,
        bool theEnforceAddition = false) const;

    __CADEX_EXPORT void Compute (const ModelData_SceneGraphElement& theElement,
        bool theEnforceAddition = false) const;

    __CADEX_EXPORT ModelData_PolyRepresentation Compute (const ModelData_BRepRepresentation& theBRep,
        bool theComputeImmediately = true) const;

    __CADEX_EXPORT ModelData_PolyShapeList Compute (const ModelData_Body& theBody) const;

    __CADEX_EXPORT ModelData_PolyShapeList Compute (const ModelData_Body& theBody,
        const ModelData_BRepRepresentation& theContext) const;

    __CADEX_EXPORT ModelData_PolyShapeList Compute (const ModelData_Body& theBody,
        std::shared_ptr<Mesh_SMDS>& theMeshDS) const;

    __CADEX_EXPORT ModelData_PolyShapeList Compute (const ModelData_Body& theBody,
        const ModelData_BRepRepresentation& theContext,
        std::shared_ptr<Mesh_SMDS>& theMeshDS) const;


    //! Returns a progress status.
    __CADEX_EXPORT Base_ProgressStatus& ProgressStatus() const;

    //! Returns an implementation object.
    /*! \internal
    */
    const std::shared_ptr<internal::ModelAlgo_BRepMesherImpl>& Impl() const { return myImpl; }

protected:

    //! Internal implementation object.
    std::shared_ptr<internal::ModelAlgo_BRepMesherImpl>   myImpl;
};

}

#endif
