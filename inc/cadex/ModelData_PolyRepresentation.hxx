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


#ifndef _ModelData_PolyRepresentation_HeaderFile
#define _ModelData_PolyRepresentation_HeaderFile

#include <cadex/Base_SharedPtr.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>
#include <cadex/ModelData_Representation.hxx>

namespace cadex {

class ModelData_Face;
class ModelData_IndexedTriangleSet;
class ModelData_Shape;
class ModelData_PolyShape;
class ModelData_PolyShapeList;

namespace internal {
class ModelData_PolyRepresentationImpl;
}

class ModelData_PolyRepresentation : public ModelData_Representation
{
public:

    typedef cadex::internal::ModelData_PolyRepresentationImpl  ImplType;

    __CADEX_EXPORT ModelData_PolyRepresentation();
    __CADEX_EXPORT ModelData_PolyRepresentation (initialized);
    __CADEX_EXPORT ModelData_PolyRepresentation (ImplType* theImpl);

    __CADEX_EXPORT ModelData_PolyRepresentation (const ModelData_BRepRepresentation& theRef,
        const ModelAlgo_BRepMesherParameters& theParameters = ModelAlgo_BRepMesherParameters(),
        bool theComputeImmediately = false);
    __CADEX_EXPORT ModelData_PolyRepresentation (const ModelData_PolyShape& theNode);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void Add (const ModelData_PolyShape& theShape);

    __CADEX_EXPORT const ModelData_PolyShapeList& Get() const;

    __CADEX_EXPORT ModelData_IndexedTriangleSet Triangulation (const ModelData_Face& theFace) const;

    class Provider
    {
    public:

        __CADEX_DEFINE_MEMORY_MANAGEMENT

        __CADEX_EXPORT virtual ~Provider();

        virtual void Feed (ModelData_PolyRepresentation& theRepresentation) const = 0;
    };

    __CADEX_EXPORT void AddProvider (const std::shared_ptr<Provider>& theProvider);

    __CADEX_EXPORT void Clear();

private:

    friend class internal::ModelData_PolyRepresentationImpl;
};

}

#endif
