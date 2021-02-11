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


#ifndef _ModelPrs_Selection_HeaderFile
#define _ModelPrs_Selection_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>

#include <cadex/ModelData_Shape.hxx>
#include <vector>

namespace cadex {
class ModelPrs_SelectionVisitor;
class ModelPrs_SceneNode;

namespace internal {
class ModelPrs_SelectionImpl;
}

class ModelPrs_Selection : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_SelectionImpl    ImplType;

    __CADEX_EXPORT ModelPrs_Selection();

    __CADEX_EXPORT ModelPrs_Selection (initialized);

    __CADEX_EXPORT void Accept (ModelPrs_SelectionVisitor& theVisitor) const;

    __CADEX_EXPORT void Append (const ModelPrs_SceneNode& theNode);

    __CADEX_EXPORT void Append (const ModelPrs_SceneNode& theNode, const std::vector<ModelData_Shape>& theShapes);
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_Selection_HeaderFile
