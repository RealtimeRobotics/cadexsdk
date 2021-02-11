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


#ifndef _ModelAlgo_BRepMesherParameters_HeaderFile
#define _ModelAlgo_BRepMesherParameters_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>

namespace cadex {

namespace internal {
class ModelAlgo_BRepMesherParametersImpl;
class Base_MeshAlgoFactory;
}

class ModelAlgo_BRepMesherParameters
{
public:
    enum Granularity {
        Coarse, Medium, Fine, Custom
    };

    enum TriangulatorVersion {
        V1 = 1,
        V2 = 2,
        V3 = 3
    };

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_BRepMesherParameters (Granularity theGranularity = Fine,
        bool theMergeFaceSets = true);

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_BRepMesherParameters (const ModelAlgo_BRepMesherParameters& theOther);

    //! Sets mesh granularity policy.
    __CADEX_EXPORT void SetGranularity (Granularity theVal);
    __CADEX_EXPORT Granularity GetGranularity() const;

    __CADEX_EXPORT void SetChordalDeflection (double theValue);
    __CADEX_EXPORT double ChordalDeflection() const;

    __CADEX_EXPORT void SetIsRelativeChordalDeflection (bool theValue);
    __CADEX_EXPORT bool IsRelativeChordalDeflection() const;

    __CADEX_EXPORT void SetMaxEdgeLength (double theValue);
    __CADEX_EXPORT double MaxEdgeLength() const;

    __CADEX_EXPORT void SetIsRelativeMaxEdgeLength (bool theValue);
    __CADEX_EXPORT bool IsRelativeMaxEdgeLength() const;

    __CADEX_EXPORT void SetAngularDeflection (double theValue);
    __CADEX_EXPORT double AngularDeflection() const;

    __CADEX_EXPORT void SetTriangulatorVersion (TriangulatorVersion theValue);
    __CADEX_EXPORT TriangulatorVersion GetTriangulatorVersion() const;

    __CADEX_EXPORT bool  MergeFaceSets() const;
    __CADEX_EXPORT bool& MergeFaceSets();

    __CADEX_EXPORT bool  GenerateFaceMeshAssociations() const;
    __CADEX_EXPORT bool& GenerateFaceMeshAssociations();

    __CADEX_EXPORT bool  GetUVCoordinates() const;
    __CADEX_EXPORT bool& GetUVCoordinates();

    __CADEX_EXPORT bool  PreserveVisualizationMesh() const;
    __CADEX_EXPORT bool& PreserveVisualizationMesh();

    __CADEX_EXPORT const internal::Base_MeshAlgoFactory& ComputationalMeshAlgo() const;
    __CADEX_EXPORT       internal::Base_MeshAlgoFactory& ComputationalMeshAlgo();

    __CADEX_EXPORT ModelAlgo_BRepMesherParameters& operator= (const ModelAlgo_BRepMesherParameters& theOther);

    __CADEX_EXPORT internal::ModelAlgo_BRepMesherParametersImpl* Impl() const;

private:
    std::shared_ptr<internal::ModelAlgo_BRepMesherParametersImpl>   myImpl;
};

}

#endif
