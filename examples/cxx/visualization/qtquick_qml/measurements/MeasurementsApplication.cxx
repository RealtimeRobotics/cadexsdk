// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// You may use this file under the terms of the BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ****************************************************************************


#include "MeasurementsApplication.hxx"

#include <cadex/ModelAlgo_BoundingBox.hxx>
#include <cadex/ModelAlgo_TransformationApplier.hxx>
#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_Box.hxx>
#include <cadex/ModelData_Color.hxx>
#include <cadex/ModelData_Face.hxx>
#include <cadex/ModelData_Transformation.hxx>
#include <cadex/ModelData_Vertex.hxx>
#include <cadex/ModelPrsQtQuick_ViewPort.hxx>
#include <cadex/ModelPrs_Geometry.hxx>
#include <cadex/ModelPrs_Measurement.hxx>
#include <cadex/ModelPrs_MeasurementFactory.hxx>
#include <cadex/ModelPrs_SceneNode.hxx>
#include <cadex/ModelPrs_SceneNodeFactory.hxx>
#include <cadex/ModelPrs_Selection.hxx>
#include <cadex/ModelPrs_SelectionManager.hxx>
#include <cadex/ModelPrs_SelectionVisitor.hxx>

#include <QtCore/QDebug>
#include <QtQuick/QQuickWindow>

#include <deque>
#include <memory>

using namespace cadex;

namespace {

class SelectionVisitor : public ModelPrs_SelectionVisitor
{
public:
    void Visit (const ModelPrs_SceneNode& /*theNode*/) override
    {

    }

    void Visit (const ModelPrs_SceneNode& theNode, const std::vector<ModelData_Shape>& theShapes) override
    {
        auto aTrsf   = theNode.Transformation();
        auto aParent = theNode.Parent();

        while (aParent) {
            aTrsf = aParent.Transformation() * aTrsf;
            aParent = aParent.Parent();
        }

        myShape = theShapes.front();
        myShape = ModelAlgo_TransformationApplier::Transform (myShape, aTrsf);
    }

    ModelData_Shape myShape;
};

size_t NumberOfRequiredShapes (ModelPrs_MeasurementType theType)
{
    switch (theType) {
    case ModelPrs_MT_Radius:
    case ModelPrs_MT_Diameter:
        return 1;
    case ModelPrs_MT_Distance:
    case ModelPrs_MT_AngleBetweenPlanes:
        return 2;
    case ModelPrs_MT_AngleBetweenVertexes:
        return 3;
    default:
        return 0;
    }
}

int GetSelectionModeForMeasurement (ModelPrs_MeasurementType theType)
{
    switch (theType) {
    case ModelPrs_MT_Radius:
    case ModelPrs_MT_Diameter:
        return ModelPrs_SM_Face | ModelPrs_SM_Edge;
    case ModelPrs_MT_Distance:
        return ModelPrs_SM_Vertex | ModelPrs_SM_Edge | ModelPrs_SM_Face;
    case ModelPrs_MT_AngleBetweenPlanes:
        return ModelPrs_SM_Face;
    case ModelPrs_MT_AngleBetweenVertexes:
        return ModelPrs_SM_Vertex;
    default:
        return ModelPrs_SM_None;
    }
}

int GetSelectionFilterForMeasurement (ModelPrs_MeasurementType theType)
{
    switch (theType) {
    case ModelPrs_MT_Radius:
    case ModelPrs_MT_Diameter:
        return ModelPrs_SFT_CircleEdgeFilter | ModelPrs_SFT_RevolFaceFilter;
    case ModelPrs_MT_AngleBetweenPlanes:
        return ModelPrs_SFT_PlanarFaceFilter;
    case ModelPrs_MT_Distance:
    case ModelPrs_MT_AngleBetweenVertexes:
    default:
        return ModelPrs_SFT_None;
    }
}

std::vector<ModelPrs_Measurement> CreateMeasurements (const std::vector<cadex::ModelData_Shape>& theShapes,
                                                      ModelPrs_MeasurementType theType)
{
    std::vector<ModelPrs_Measurement> aMeasurements;

    ModelPrs_MeasurementFactory aFactory;

    switch (theType) {
    case ModelPrs_MT_Radius: {
        auto aMinorRadius = aFactory.CreateMinorRadius (theShapes[0]);
        auto aMajorRadius = aFactory.CreateMajorRadius (theShapes[0]);

        if (aMinorRadius) {
            aMeasurements.push_back (aMinorRadius);
        }
        if (aMajorRadius && aMinorRadius != aMajorRadius) {
            aMeasurements.push_back (aMajorRadius);
        }
        break;
    }
    case ModelPrs_MT_Diameter: {
        auto aMinorDiameter = aFactory.CreateMinorDiameter (theShapes[0]);
        auto aMajorDiameter = aFactory.CreateMajorDiameter (theShapes[0]);

        if (aMinorDiameter) {
            aMeasurements.push_back (aMinorDiameter);
        }
        if (aMajorDiameter && aMinorDiameter != aMajorDiameter) {
            aMeasurements.push_back (aMajorDiameter);
        }
        break;
    }
    case ModelPrs_MT_Distance: {
        auto aDistance = aFactory.CreateDistance (theShapes[0], theShapes[1]);
        if (aDistance) {
            aMeasurements.push_back (aDistance);
        }
        break;
    }
    case ModelPrs_MT_AngleBetweenPlanes: {
        Q_ASSERT (theShapes[0].Type() == ModelData_ST_Face && theShapes[1].Type() == ModelData_ST_Face);
        const auto& aFirstFace  = ModelData_Face::Cast (theShapes[0]);
        const auto& aSecondFace = ModelData_Face::Cast (theShapes[1]);
        auto anAngle = aFactory.CreateAngle (aFirstFace, aSecondFace);
        if (anAngle) {
            aMeasurements.push_back (anAngle);
        }
        break;
    }
    case ModelPrs_MT_AngleBetweenVertexes: {
        Q_ASSERT (theShapes[0].Type() == ModelData_ST_Vertex
                  && theShapes[1].Type() == ModelData_ST_Vertex
                  && theShapes[2].Type() == ModelData_ST_Vertex);
        const auto& aFirstVertex  = ModelData_Vertex::Cast (theShapes[0]);
        const auto& aSecondVertex = ModelData_Vertex::Cast (theShapes[1]);
        const auto& aThirdVertex  = ModelData_Vertex::Cast (theShapes[2]);
        auto anAngle = aFactory.CreateAngle (aFirstVertex, aSecondVertex, aThirdVertex);
        if (anAngle) {
            aMeasurements.push_back (anAngle);
        }
        break;
    }
    default:
        Q_ASSERT(false);
    }
    return aMeasurements;
}

} // end of unnamed namespace


SelectionChangesObserver::SelectionChangesObserver (MeasurementsApplication& theApplication)
    : myApplication (theApplication)
{

}

void SelectionChangesObserver::SelectionChangedByScene (const cadex::ModelPrs_Selection& theCurrent,
                                                        const cadex::ModelPrs_Selection& /*theSelected*/,
                                                        const cadex::ModelPrs_Selection& /*theDeselected*/)
{
    if (theCurrent.IsNull()) {
        Clear();
    } else {
        SelectionVisitor aVisitor;
        theCurrent.Accept (aVisitor);
        myShapes.push_back (aVisitor.myShape);
    }

    myApplication.OnSelectionChanged (myShapes);
}

void SelectionChangesObserver::Clear()
{
    myShapes.clear();
}

MeasurementInfo::MeasurementInfo (MeasurementsApplication* theParent)
    : QObject (theParent)
{

}

void MeasurementInfo::setNumberOfSelectedShapes (int theValue)
{
    if (myNumberOfSelectedShapes != theValue) {
        myNumberOfSelectedShapes = theValue;
        emit numberOfSelectedShapesChanged();
    }
}
void MeasurementInfo::setMeasurementsResults (const QString& theValue)
{
    if (myMeasurementsResults != theValue) {
        myMeasurementsResults = theValue;
        emit measurementsResultsChanged();
    }
}


MeasurementsApplication::MeasurementsApplication()
    : mySelectionObserver (*this),
      myMeasurementSize (-1.),
      myAngleUnit (Base_AU_Degree),
      myLengthUnit (Base_LU_Millimeters)
{
    myMeasurementInfo = new MeasurementInfo (this);

    myScene.SelectionManager().Register (mySelectionObserver);

    connect (this, &BaseViewerApplication::initialized, this, &MeasurementsApplication::onInitialized);
}

void MeasurementsApplication::onMeasurementModeChanged (const QVariant& theMode)
{
    myMeasurementMode = static_cast<ModelPrs_MeasurementType> (theMode.toInt());

    auto aSelectionMode = GetSelectionModeForMeasurement (myMeasurementMode);
    myRoot.SetSelectionMode (static_cast<ModelPrs_SelectionMode> (aSelectionMode));

    auto aSelectionFilter = GetSelectionFilterForMeasurement (myMeasurementMode);
    myScene.SelectionManager().SetFilter (static_cast<ModelPrs_SelectionFilterType> (aSelectionFilter));

    mySelectionObserver.Clear();
    myRoot.RemoveChildNode (myRootMeasurementsNode);
    myScene.Update();
}

void MeasurementsApplication::onMeasurementAngleUnitsChanged (const QVariant& theIndex)
{
    myAngleUnit = static_cast<Base_AngleUnit> (theIndex.toInt());
    UpdateResult();
    myRootMeasurementsNode.Invalidate();
    myScene.Update();
}

void MeasurementsApplication::onMeasurementLengthUnitsChanged (const QVariant& theIndex)
{
    myLengthUnit = static_cast<Base_LengthUnit> (theIndex.toInt());
    UpdateResult();
    myRootMeasurementsNode.Invalidate();
    myScene.Update();
}

namespace {

double ComputeMeasurementSize (const ModelData_Model& theModel)
{
    ModelData_Box aModelBoundingBox;
    ModelAlgo_BoundingBox::Compute (theModel, aModelBoundingBox);
    if (!aModelBoundingBox.IsInfinite()) {
        auto r = std::max ({ aModelBoundingBox.XRange(),
                             aModelBoundingBox.YRange(),
                             aModelBoundingBox.ZRange() });
        return r / 16.;
    } else {
        return 10.;
    }
}

} // end of unnamed namespace

void MeasurementsApplication::UpdateResult()
{
    QStringList aResult;
    for (auto& aMeasurement : myMeasurements) {
        aMeasurement.SetAngleUnit (myAngleUnit);
        aMeasurement.SetLengthUnit (myLengthUnit);
        aResult.push_back (QString::number (aMeasurement.Value(), 'g', 3));
    }

    myMeasurementInfo->setMeasurementsResults (aResult.join ("; "));
}

void MeasurementsApplication::OnSelectionChanged (const std::vector<cadex::ModelData_Shape>& theShapes)
{
    myMeasurementInfo->setNumberOfSelectedShapes (static_cast<int> (theShapes.size()));

    if (theShapes.empty() || theShapes.size() < NumberOfRequiredShapes (myMeasurementMode)) {
        return;
    }

    myMeasurements = CreateMeasurements (theShapes, myMeasurementMode);
    UpdateResult();

    if (myMeasurements.empty()) {
        myMeasurementInfo->setNumberOfSelectedShapes (0);
        mySelectionObserver.Clear();
        return;
    }

    if (myMeasurementSize < 0) {
        myMeasurementSize = ComputeMeasurementSize (myModel);
    }

    ModelPrs_SceneNode aTempRootMeasureNode;
    aTempRootMeasureNode.SetAppearance (ModelData_Color (1.f, 1.f, 1.f, 1.f));

    ModelPrs_SceneNodeFactory aFactory;
    for (auto& aMeasurement : myMeasurements) {
        aMeasurement.SetSize (myMeasurementSize);
        auto aSceneNode = aFactory.Create (aMeasurement);
        aTempRootMeasureNode.AddChildNode (aSceneNode);
    }

    myScene.RemoveRoot (myRootMeasurementsNode);
    myScene.AddRoot (aTempRootMeasureNode);
    myScene.Update();

    myRootMeasurementsNode = aTempRootMeasureNode;

    mySelectionObserver.Clear();
}

void MeasurementsApplication::onInitialized()
{
    connect (myMainWindow, SIGNAL (measurementModeChanged (const QVariant&)),
             this,         SLOT (onMeasurementModeChanged (const QVariant&)));

    connect (myMainWindow, SIGNAL (measurementAngleUnitsChanged (const QVariant&)),
             this,         SLOT (onMeasurementAngleUnitsChanged (const QVariant&)));

    connect (myMainWindow, SIGNAL (measurementLengthUnitsChanged (const QVariant&)),
             this,         SLOT (onMeasurementLengthUnitsChanged (const QVariant&)));

    myMainWindow->setProperty ("model", QVariant::fromValue (myMeasurementInfo));
}

void MeasurementsApplication::Clear()
{
    myMeasurementSize = -1.;
    myMeasurementInfo->setNumberOfSelectedShapes (0);
    myMeasurementInfo->setMeasurementsResults("");

    myScene.RemoveRoot (myRootMeasurementsNode);
    BaseViewerApplication::Clear();
}
