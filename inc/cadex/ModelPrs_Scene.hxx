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


#ifndef _ModelPrs_Scene_HeaderFile
#define _ModelPrs_Scene_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>

namespace cadex {
class ModelPrs_SceneNode;
class ModelPrs_SceneNodeVisitor;
class ModelPrs_SelectionManager;

namespace internal {
class ModelPrs_SceneImpl;
}

class ModelPrs_Scene : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_SceneImpl    ImplType;

    __CADEX_EXPORT ModelPrs_Scene();

    __CADEX_EXPORT void AddRoot (ModelPrs_SceneNode& theNode);

    __CADEX_EXPORT void RemoveRoot (ModelPrs_SceneNode& theNode);

    __CADEX_EXPORT void Clear();

    __CADEX_EXPORT void Update();

    __CADEX_EXPORT void Wait();

    __CADEX_EXPORT void Accept (ModelPrs_SceneNodeVisitor& theVisitor);

    __CADEX_EXPORT ModelPrs_SelectionManager& SelectionManager();
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_Scene_HeaderFile
