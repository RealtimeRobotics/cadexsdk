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


#ifndef _ModelPrs_DisplayerApplier_HeaderFile
#define _ModelPrs_DisplayerApplier_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_Templates.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>
#include <cadex/ModelData_RepresentationMask.hxx>
#include <cadex/ModelData_RepresentationSelector.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>
#include <cadex/ModelPrs_DisplayMode.hxx>

namespace cadex {
class Base_ProgressStatus;
class ModelData_Model;
class ModelData_Part;
class ModelData_Transformation;
class ModelPrs_Displayer;
class ModelPrs_View3dObject;

class ModelPrs_DisplayerApplier
{
public:
    typedef cadex::internal::cadex_vector<ModelData_SceneGraphElement>::type   SGEVecType;
    typedef cadex::internal::cadex_vector<ModelPrs_View3dObject>::type   V3dObjVecType;

    class RepresentationCache
    {
    public:
        __CADEX_DEFINE_MEMORY_MANAGEMENT

        __CADEX_EXPORT virtual ~RepresentationCache();

        //! Returns a hash value for the list of scene graph elements.
        /*! Can be used to compute a unique hash value for the path from \a theFirst to \a theLast element.*/
        __CADEX_EXPORT static size_t HashValue (const SGEVecType& theVec);

        /*! Must return null handle (and must not throw exception) if theRepMode does not have an interactive object.

            Must not attempt to create a representation (this is responsibility of ModelPrs_DisplayerApplier).

            \sa SaveInteractiveObject().
        */
        virtual ModelPrs_DisplayerApplier::V3dObjVecType InteractiveObjects (
            const std::shared_ptr<ModelData_RepresentationSelector>& theRepMode,
            const SGEVecType& theAncestors) const = 0;

        //! Registers an interactive object for the given representation.
        /*! This saved interactive object can later be requested using the InteractiveObject() method.
        */
        virtual void SaveInteractiveObjects (
            const std::shared_ptr<ModelData_RepresentationSelector>& theRepMode,
            const SGEVecType& theAncestors,
            const ModelPrs_DisplayerApplier::V3dObjVecType& theView3dObjects) = 0;
    };

    struct DisplayParams
    {
        DisplayParams (const std::shared_ptr<ModelData_RepresentationSelector>& theRepMode,
                       ModelPrs_Displayer&                                      theDisplayer,
                       RepresentationCache*                                     theCache,
                       Base_ProgressStatus&                                     theProgressStatus,
                       ModelPrs_DisplayMode                                     theDisplayMode,
                       const ModelAlgo_BRepMesherParameters&                    theBRepParams    ) :
            myRepresentationMode (theRepMode),
            myDisplayer          (theDisplayer),
            myCache              (theCache),
            myProgressStatus     (theProgressStatus),
            myDisplayMode        (theDisplayMode),
            myBRepParams         (theBRepParams)
        {}

        DisplayParams (ModelData_RepresentationMask                             theRepMask,
                       ModelPrs_Displayer&                                      theDisplayer,
                       RepresentationCache*                                     theCache,
                       Base_ProgressStatus&                                     theProgressStatus,
                       cadex::ModelPrs_DisplayMode                              theDisplayMode,
                       const ModelAlgo_BRepMesherParameters&                    theBRepParams) :
            myDisplayer          (theDisplayer),
            myCache              (theCache),
            myProgressStatus     (theProgressStatus),
            myDisplayMode        (theDisplayMode),
            myBRepParams         (theBRepParams)
        {
            myRepresentationMode.reset (new ModelData_RepresentationMaskSelector (theRepMask));
        }

        std::shared_ptr<ModelData_RepresentationSelector> myRepresentationMode;
        ModelPrs_Displayer& myDisplayer;
        RepresentationCache* myCache;
        Base_ProgressStatus& myProgressStatus;
        cadex::ModelPrs_DisplayMode myDisplayMode;
        ModelAlgo_BRepMesherParameters myBRepParams;

    private:

        DisplayParams& operator= (const DisplayParams&);
    };

    //! Applies the display infrastructure to display the entire scene graph.
    __CADEX_EXPORT static void Apply (const ModelData_Model& theSceneGraph,
        const DisplayParams& theParams,
        bool theAllowConcurrency = false,
        bool thePerBodyCreate = false);

    //! Applies the display infrastructure to display the sub-graph starting with \a theElement.
    __CADEX_EXPORT static void Apply (const ModelData_SceneGraphElement& theElement,
        const DisplayParams& theParams,
        bool theAllowConcurrency = false,
        bool thePerBodyCreate = false);

    //! Applies the display infrastructure to display the part with explicit transformation.
    __CADEX_EXPORT static void Apply (const ModelData_Part& thePart,
        const ModelData_Transformation& theTrsf,
        const DisplayParams& theParams,
        bool theAllowConcurrency = false,
        bool thePerBodyCreate = false);

    //! Applies the display infrastructure to display the sub-graph starting with \a theElement.
    __CADEX_EXPORT static void Apply (const ModelData_SceneGraphElement& theElement,
        const SGEVecType& theAncestors,
        const DisplayParams& theParams,
        bool theAllowConcurrency = false,
        bool thePerBodyCreate = false);

    //! Applies the display infrastructure to display the sub-graph starting with \a theEntries
    __CADEX_EXPORT static void Apply (
        const SGEVecType& theEntries,
        const SGEVecType& theAncestors,
        const DisplayParams& theParams,
        bool theAllowConcurrency = false,
        bool thePerBodyCreate = false);

};

}

#endif // __CADEX_PREVIEW_VISUALIZATION
#endif // _ModelPrs_DisplayerApplier_HeaderFile
