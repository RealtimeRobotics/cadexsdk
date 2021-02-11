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


#ifndef _ModelPrs_Manipulator_HeaderFile
#define _ModelPrs_Manipulator_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>


namespace cadex {
class ModelPrs_ManipulatorObserver;
class ModelPrs_SceneNode;

namespace internal {
class ModelPrs_ManipulatorImpl;
}

class ModelPrs_Manipulator : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_ManipulatorImpl    ImplType;

    __CADEX_EXPORT ModelPrs_Manipulator();

    __CADEX_EXPORT ModelPrs_SceneNode AttachedTo() const;
    __CADEX_EXPORT void AttachTo (const ModelPrs_SceneNode& theSceneNode);
    __CADEX_EXPORT void Detach();

    __CADEX_EXPORT void ResetTransformation();

    __CADEX_EXPORT void Register (ModelPrs_ManipulatorObserver& theObserver);
    __CADEX_EXPORT void Unregister();
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_Manipulator_HeaderFile
