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


#ifndef _ModelPrsQtQuick_ViewPort_HeaderFile
#define _ModelPrsQtQuick_ViewPort_HeaderFile

#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelPrsQtQuick_Macro.hxx>

#include <QtQuick/QQuickFramebufferObject>
#include <memory>

#if _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4251)
#endif

namespace cadex {
class ModelData_Box;
class ModelPrs_BackgroundStyle;
class ModelPrs_Exploder;
class ModelPrs_Manipulator;
class ModelPrs_Scene;
class ModelPrs_ViewCubeStyle;

namespace internal {
class ModelPrsQtQuick_ViewPortImpl;
class ModelPrsQtQuick_RendererImpl;
}

class CadExViewQtQuick_EXPORT ModelPrsQtQuick_ViewPort : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY (MouseMode mouseMode         READ mouseMode        WRITE setMouseMode        NOTIFY mouseModeChanged       )
    Q_PROPERTY (bool selectionEnabled       READ selectionEnabled WRITE setSelectionEnabled NOTIFY selectionEnabledChanged)
    Q_PROPERTY (bool highlightEnabled       READ highlightEnabled WRITE setHighlightEnabled NOTIFY highlightEnabledChanged)
    Q_PROPERTY (bool trihedronEnabled       READ trihedronEnabled WRITE setTrihedronEnabled NOTIFY trihedronEnabledChanged)
    Q_PROPERTY (bool gridPlaneEnabled       READ gridPlaneEnabled WRITE setGridPlaneEnabled NOTIFY gridPlaneEnabledChanged)

    Q_PROPERTY (bool viewCubeEnabled        READ viewCubeEnabled  WRITE setViewCubeEnabled  NOTIFY viewCubeEnabledChanged )
    Q_PROPERTY (QRect viewCubeGeometry      READ viewCubeGeometry WRITE setViewCubeGeometry NOTIFY viewCubeGeometryChanged)
    Q_PROPERTY (QObject* viewCubeStyle      READ viewCubeStyle    WRITE setViewCubeStyle    NOTIFY viewCubeStyleChanged   )

    Q_PROPERTY (QObject* backgroundStyle    READ backgroundStyle  WRITE setBackgroundStyle  NOTIFY backgroundStyleChanged )

    Q_PROPERTY (CameraProjectionType cameraProjectionType READ cameraProjectionType WRITE setCameraProjectionType NOTIFY cameraProjectionTypeChanged)

public:
    typedef cadex::internal::ModelPrsQtQuick_ViewPortImpl    ImplType;

    enum MouseMode {
        Normal,
        FitArea
    };
    Q_ENUM (MouseMode)

    enum CameraProjectionType {
        Isometric,
        Perspective
    };
    Q_ENUM (CameraProjectionType)

    class Renderer : public QQuickFramebufferObject::Renderer
    {
    public:
        typedef cadex::internal::ModelPrsQtQuick_RendererImpl ImplType;

        Renderer();

    protected:
        void render() override;

        QOpenGLFramebufferObject* createFramebufferObject (const QSize& theSize) override;

        void synchronize (QQuickFramebufferObject* theViewPort) override;

    private:
        std::shared_ptr<ImplType> myImpl;
    };

    explicit ModelPrsQtQuick_ViewPort (QQuickItem* theParent = nullptr);

    static void RegisterQtTypes();

    bool AttachToScene (const ModelPrs_Scene& theScene);

    Q_INVOKABLE void fitAll();
    Q_INVOKABLE void animatedFitAll();

    void fitBox (const ModelData_Box& theBox);
    void animatedFitBox (const ModelData_Box& theBox);

    CameraProjectionType cameraProjectionType() const;
    void setCameraProjectionType (CameraProjectionType theType);

    MouseMode mouseMode() const;
    void setMouseMode (MouseMode theMode);

    bool highlightEnabled() const;
    void setHighlightEnabled (bool theEnabled);

    bool selectionEnabled() const;
    void setSelectionEnabled (bool theEnabled);

    bool viewCubeEnabled() const;
    void setViewCubeEnabled (bool theEnabled);

    QRect viewCubeGeometry();
    void setViewCubeGeometry (const QRect& theRect);

    bool trihedronEnabled() const;
    void setTrihedronEnabled (bool theEnabled);

    bool gridPlaneEnabled() const;
    void setGridPlaneEnabled (bool theEnabled);

    const ModelPrs_BackgroundStyle& BackgroundStyle() const;
    void SetBackgroundStyle (const ModelPrs_BackgroundStyle& theStyle);

    const ModelPrs_ViewCubeStyle& ViewCubeStyle() const;
    void SetViewCubeStyle (const ModelPrs_ViewCubeStyle& theStyle);

    ModelPrs_Manipulator Manipulator();

    ModelPrs_Exploder Exploder();

signals:
    void mouseModeChanged();
    void cameraProjectionTypeChanged();
    void highlightEnabledChanged();
    void selectionEnabledChanged();
    void trihedronEnabledChanged();
    void gridPlaneEnabledChanged();

    void backgroundStyleChanged();

    void viewCubeStyleChanged();
    void viewCubeEnabledChanged();
    void viewCubeGeometryChanged();

public:
    Renderer* createRenderer() const override;

    bool event (QEvent* theEvent) override;

    QObject* backgroundStyle();
    void setBackgroundStyle (QObject* theStyle);

    QObject* viewCubeStyle();
    void setViewCubeStyle (QObject* theStyle);

    const std::shared_ptr<ImplType>& Impl() const;

protected:
    void hoverEnterEvent   (QHoverEvent* theEvent) override;
    void hoverMoveEvent    (QHoverEvent* theEvent) override;
    void hoverLeaveEvent   (QHoverEvent* theEvent) override;

    void mousePressEvent   (QMouseEvent* theEvent) override;
    void mouseMoveEvent    (QMouseEvent* theEvent) override;
    void mouseReleaseEvent (QMouseEvent* theEvent) override;

    void wheelEvent (QWheelEvent* theEvent) override;

    void touchEvent (QTouchEvent* theEvent) override;

protected:
    std::shared_ptr<ImplType> myImpl;
};

}

#if _MSC_VER
#pragma warning (pop)
#endif

#endif // _ModelPrsQtQuick_ViewPort_HeaderFile
