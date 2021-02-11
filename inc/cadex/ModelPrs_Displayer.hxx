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


#ifndef _ModelPrs_Displayer_HeaderFile
#define _ModelPrs_Displayer_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_Templates.hxx>

namespace cadex {
class ModelData_Representation;
class ModelData_SceneGraphElement;
class ModelPrs_View3dObject;

class ModelPrs_Displayer
{
public:

    typedef internal::cadex_vector<ModelPrs_View3dObject>::type         V3dObjVecType;
    typedef internal::cadex_vector<ModelData_SceneGraphElement>::type   SGEVecType;

    __CADEX_EXPORT virtual ~ModelPrs_Displayer();

    __CADEX_EXPORT virtual void Display (const V3dObjVecType& theView3dObjects,
        const ModelData_Representation& theRep,
        const SGEVecType& theAncestors,
        int theDisplayMode) = 0;

};

}

#endif // __CADEX_PREVIEW_VISUALIZATION
#endif // _ModelPrs_Displayer_HeaderFile
