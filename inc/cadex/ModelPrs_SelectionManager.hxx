// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2019, CADEX. All rights reserved.
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


#ifndef _ModelPrs_SelectionManager_HeaderFile
#define _ModelPrs_SelectionManager_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelPrs_SelectionFilterType.hxx>

namespace cadex {
class ModelPrs_Selection;
class ModelPrs_SelectionChangesObserver;

namespace internal {
class ModelPrs_SceneBackend;
class ModelPrs_SelectionManagerImpl;
}

class ModelPrs_SelectionManager : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_SelectionManagerImpl    ImplType;

    __CADEX_EXPORT void Select (const ModelPrs_Selection& theSelection);

    __CADEX_EXPORT void Deselect (const ModelPrs_Selection& theSelection);

    __CADEX_EXPORT void DeselectAll();

    __CADEX_EXPORT void SetFilter (ModelPrs_SelectionFilterType theFilter);

    __CADEX_EXPORT void Register (ModelPrs_SelectionChangesObserver& theObserver);

    __CADEX_EXPORT void Unregister();

protected:
    __CADEX_EXPORT ModelPrs_SelectionManager();

    friend class cadex::internal::ModelPrs_SceneBackend;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_SelectionManager_HeaderFile
