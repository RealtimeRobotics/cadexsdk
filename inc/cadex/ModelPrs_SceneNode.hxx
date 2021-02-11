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


#ifndef _ModelPrs_SceneNode_HeaderFile
#define _ModelPrs_SceneNode_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelPrs_DisplayMode.hxx>
#include <cadex/ModelPrs_SceneNodeVisitor.hxx>
#include <cadex/ModelPrs_SelectionMode.hxx>
#include <cadex/ModelPrs_VisibilityMode.hxx>

#include <memory>

namespace cadex {
class ModelData_Appearance;
class ModelData_Transformation;
class ModelPrs_Geometry;

namespace internal {
class ModelPrs_SceneNodeImpl;
}

class ModelPrs_SceneNode : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_SceneNodeImpl    ImplType;
#ifndef  SWIG
    class Data { };
#endif
    __CADEX_EXPORT ModelPrs_SceneNode();
    __CADEX_EXPORT ModelPrs_SceneNode (initialized);

    __CADEX_EXPORT ModelPrs_SceneNode Parent() const;
    __CADEX_EXPORT bool Detach();

    __CADEX_EXPORT void AddChildNode (ModelPrs_SceneNode& theNode);
    __CADEX_EXPORT void RemoveChildNode (ModelPrs_SceneNode& theNode);
    __CADEX_EXPORT void RemoveChildrenNodes();

    __CADEX_EXPORT ModelPrs_Geometry Geometry() const;
    __CADEX_EXPORT void SetGeometry (const ModelPrs_Geometry& theGeometry);

    __CADEX_EXPORT ModelData_Appearance Appearance() const;
    __CADEX_EXPORT void SetAppearance (const ModelData_Appearance& theAppearance);

    __CADEX_EXPORT ModelData_Transformation Transformation() const;
    __CADEX_EXPORT void SetTransformation (const ModelData_Transformation& theTransformation);

    __CADEX_EXPORT ModelPrs_DisplayMode DisplayMode() const;
    __CADEX_EXPORT void SetDisplayMode (ModelPrs_DisplayMode theMode);

    __CADEX_EXPORT ModelPrs_SelectionMode SelectionMode() const;
    __CADEX_EXPORT void SetSelectionMode (ModelPrs_SelectionMode theMode);

    __CADEX_EXPORT ModelPrs_VisibilityMode VisibilityMode() const;
    __CADEX_EXPORT void SetVisibilityMode (ModelPrs_VisibilityMode theMode);
#ifndef  SWIG
    __CADEX_EXPORT std::shared_ptr<Data> UserData() const;
    __CADEX_EXPORT void SetUserData (const std::shared_ptr<Data>& theUserData);
#endif
    __CADEX_EXPORT void Accept (ModelPrs_SceneNodeVisitor& theVisitor) const;

    __CADEX_EXPORT void Invalidate();

    friend class internal::ModelPrs_SceneNodeImpl;

    __CADEX_EXPORT ModelPrs_SceneNode (ImplType* theImpl);
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_SceneNode_HeaderFile
