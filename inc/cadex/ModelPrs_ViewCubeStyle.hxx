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


#ifndef _ModelPrs_ViewCubeStyle_HeaderFile
#define _ModelPrs_ViewCubeStyle_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelData_Color.hxx>

namespace cadex {

class ModelPrs_ViewCubeStyle : public Base_PublicObject
{
public:
    __CADEX_EXPORT ModelPrs_ViewCubeStyle();

    __CADEX_EXPORT const ModelData_Color& NormalColor() const;
    __CADEX_EXPORT void SetNormalColor (const ModelData_Color& theColor);

    __CADEX_EXPORT const ModelData_Color& HoveredColor() const;
    __CADEX_EXPORT void SetHoveredColor (const ModelData_Color& theColor);

    __CADEX_EXPORT const ModelData_Color& PressedColor() const;
    __CADEX_EXPORT void SetPressedColor (const ModelData_Color& theColor);

    __CADEX_EXPORT const ModelData_Color& TextColor() const;
    __CADEX_EXPORT void SetTextColor (const ModelData_Color& theColor);

    __CADEX_EXPORT const ModelData_Color& TrihedronTextColor() const;
    __CADEX_EXPORT void SetTrihedronTextColor (const ModelData_Color& theColor);
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_BackgroundStyle_HeaderFile
