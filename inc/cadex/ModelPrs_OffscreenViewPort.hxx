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


#ifndef _ModelPrs_OffscreenViewPort_HeaderFile
#define _ModelPrs_OffscreenViewPort_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>
#include <cadex/Base_UTF16String.hxx>
#include <cadex/ModelPrs_AxisType.hxx>
#include <cadex/ModelPrs_CameraProjectionType.hxx>
#include <cadex/ModelPrs_CameraPositionType.hxx>

#include <vector>

namespace cadex {
class ModelData_Box2d;
class ModelData_Box;
class ModelData_Direction;
class ModelData_Point;
class ModelPrs_BackgroundStyle;
class ModelPrs_Exploder;
class ModelPrs_Scene;
class ModelPrs_ViewCubeStyle;

namespace internal {
class ModelPrs_OffscreenViewPortImpl;
}

class ModelPrs_OffscreenViewPort : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_OffscreenViewPortImpl    ImplType;

    __CADEX_EXPORT ModelPrs_OffscreenViewPort();

    __CADEX_EXPORT bool AttachToScene (const ModelPrs_Scene& theScene);

    __CADEX_EXPORT void Resize (unsigned int theWidth, unsigned int theHeight);

    __CADEX_EXPORT bool GrabToImage (const Base_UTF16String& thePath) const;
    __CADEX_EXPORT std::vector<unsigned char> GrabToBuffer() const;

    __CADEX_EXPORT void FitAll();
    __CADEX_EXPORT void FitBox (const ModelData_Box& theBox);

    __CADEX_EXPORT void RotateToAngle (ModelPrs_AxisType theType, double theAngle);

    __CADEX_EXPORT const ModelPrs_BackgroundStyle& BackgroundStyle() const;
    __CADEX_EXPORT void SetBackgroundStyle (const ModelPrs_BackgroundStyle& theStyle);

    __CADEX_EXPORT const ModelPrs_ViewCubeStyle& ViewCubeStyle() const;
    __CADEX_EXPORT void SetViewCubeStyle (const ModelPrs_ViewCubeStyle& theStyle);

    __CADEX_EXPORT const ModelData_Box2d& ViewCubeGeometry() const;
    __CADEX_EXPORT void SetViewCubeGeometry (const ModelData_Box2d& theBox);

    __CADEX_EXPORT bool ViewCubeEnabled() const;
    __CADEX_EXPORT void SetViewCubeEnabled (bool theEnabled);

    __CADEX_EXPORT ModelPrs_CameraProjectionType CameraProjectionType() const;
    __CADEX_EXPORT void SetCameraProjectionType (ModelPrs_CameraProjectionType theType);

    __CADEX_EXPORT void SetCameraPositionType (ModelPrs_CameraPositionType theOrientation);

    __CADEX_EXPORT void SetCameraView (const ModelData_Point& thePosition,
                                       const ModelData_Point& theTarget,
                                       const ModelData_Direction& theUp);

    __CADEX_EXPORT ModelPrs_Exploder Exploder();
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif //_ModelPrs_OffscreenViewPort_HeaderFile
