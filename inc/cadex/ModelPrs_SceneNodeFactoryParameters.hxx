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


#ifndef _ModelPrs_SceneNodeFactoryParameters_HeaderFile
#define _ModelPrs_SceneNodeFactoryParameters_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>
#include <cadex/ModelData_RepresentationMask.hxx>
#include <cadex/ModelData_RepresentationSelector.hxx>

#include <memory>

namespace cadex {
class Base_ProgressStatus;

namespace internal {
class ModelPrs_SceneNodeFactoryParametersImpl;
}

class ModelPrs_SceneNodeFactoryParameters : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_SceneNodeFactoryParametersImpl    ImplType;
    typedef std::shared_ptr<ModelData_RepresentationSelector>           RepSelector;

    __CADEX_EXPORT ModelPrs_SceneNodeFactoryParameters (
        const Base_ProgressStatus&               theProgressStatus,
        const RepSelector&                       theRepMode,
        bool                                     theDecomposition = false,
        const ModelAlgo_BRepMesherParameters&    theBRepParams = ModelAlgo_BRepMesherParameters());

    __CADEX_EXPORT ModelPrs_SceneNodeFactoryParameters (
        const RepSelector& theRepMode,
        bool                                     theDecomposition = false,
        const ModelAlgo_BRepMesherParameters&    theBRepParams = ModelAlgo_BRepMesherParameters());

    __CADEX_EXPORT ModelPrs_SceneNodeFactoryParameters (
        ModelData_RepresentationMask             theRepMask = ModelData_RM_Any,
        bool                                     theDecomposition = false,
        const ModelAlgo_BRepMesherParameters&    theBRepParams = ModelAlgo_BRepMesherParameters());

    __CADEX_EXPORT ModelPrs_SceneNodeFactoryParameters (
        const Base_ProgressStatus&               theProgressStatus,
        ModelData_RepresentationMask             theRepMask = ModelData_RM_Any,
        bool                                     theDecomposition = false,
        const ModelAlgo_BRepMesherParameters&    theBRepParams = ModelAlgo_BRepMesherParameters());

    __CADEX_EXPORT void SetDecomposition (bool theDecomposition);
    __CADEX_EXPORT bool Decomposition() const;

    __CADEX_EXPORT void SetRepresentationMode (const RepSelector& theSelector);
    __CADEX_EXPORT const RepSelector& RepresentationMode() const;

    __CADEX_EXPORT void SetProgressStatus (const Base_ProgressStatus& theStatus);
    __CADEX_EXPORT const Base_ProgressStatus& ProgressStatus() const;

    __CADEX_EXPORT void SetMesherParameters (const ModelAlgo_BRepMesherParameters& theParameters);
    __CADEX_EXPORT const ModelAlgo_BRepMesherParameters& MesherParameters() const;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_SceneNodeFactoryParameters_HeaderFile
