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


#ifndef _ModelPrs_BackgroundStyle_HeaderFile
#define _ModelPrs_BackgroundStyle_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelData_Color.hxx>

namespace cadex {

class ModelPrs_BackgroundStyle : public Base_PublicObject
{
public:
    __CADEX_EXPORT ModelPrs_BackgroundStyle (const ModelData_Color& theColor = ModelData_Color());

    __CADEX_EXPORT ModelPrs_BackgroundStyle (const ModelData_Color& theTopColor, const ModelData_Color& theBottomColor);

    __CADEX_EXPORT bool IsGradient() const;

    __CADEX_EXPORT void SetColor (const ModelData_Color& theColor);

    __CADEX_EXPORT const ModelData_Color& TopColor() const;
    __CADEX_EXPORT void SetTopColor (const ModelData_Color& theColor);

    __CADEX_EXPORT const ModelData_Color& BottomColor() const;
    __CADEX_EXPORT void SetBottomColor (const ModelData_Color& theColor);
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_BackgroundStyle_HeaderFile
