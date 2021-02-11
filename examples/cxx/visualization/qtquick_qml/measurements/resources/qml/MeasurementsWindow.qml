import QtQuick 2.12
import QtQuick.Controls 2.3
import CadEx 1.2

BaseViewerWindow {
    signal measurementModeChanged (var index)
    signal measurementAngleUnitsChanged (var index)
    signal measurementLengthUnitsChanged (var index)

    property var model: null

    property int currentMeasurementMode: -1
    property int numberOfRequiredShapes: 0

    enum MeasurementType {
        Distance,
        Radius,
        Diameter,
        AngleBetweenPlanes,
        AngleBetweenVertexes
    }

    function isAngleMeasure()
    {
        switch (currentMeasurementMode) {
        case MeasurementsWindow.MeasurementType.Distance:
        case MeasurementsWindow.MeasurementType.Radius:
        case MeasurementsWindow.MeasurementType.Diameter:
            return false;
        case MeasurementsWindow.MeasurementType.AngleBetweenPlanes:
        case MeasurementsWindow.MeasurementType.AngleBetweenVertexes:
            return true;
        }
    }

    function getShapesTypesString()
    {
        switch (currentMeasurementMode) {
        case MeasurementsWindow.MeasurementType.Distance:
            return "vertex, edge or face";
        case MeasurementsWindow.MeasurementType.Radius:
        case MeasurementsWindow.MeasurementType.Diameter:
            return "edge or face";
        case MeasurementsWindow.MeasurementType.AngleBetweenPlanes:
            return "face";
        case MeasurementsWindow.MeasurementType.AngleBetweenVertexes:
            return "vertex";
        }
    }

    function getNumberOfRequiredShapes()
    {
        switch (currentMeasurementMode) {
        case MeasurementsWindow.MeasurementType.Distance:
            return 2;
        case MeasurementsWindow.MeasurementType.Radius:
        case MeasurementsWindow.MeasurementType.Diameter:
            return 1;
        case MeasurementsWindow.MeasurementType.AngleBetweenPlanes:
            return 2;
        case MeasurementsWindow.MeasurementType.AngleBetweenVertexes:
            return 3;
        }
    }

    Menu {
        id: measurementsTypeMenu
        title: qsTr ("&Measurements")
        property string currentMenuItemName: ""
        width: angleBetweenVertexesMenuItem.width

        ButtonGroup {
            id: buttonGroup
            buttons: measurementsTypeMenu.contentChildren
            onCheckedButtonChanged: {
                measurementsTypeMenu.currentMenuItemName = checkedButton.text;
                currentMeasurementMode = checkedButton.mode;
            }
        }

        MenuItem {
            id: distanceMenuItem
            text: qsTr ("Distance")
            checkable: true
            property var mode: MeasurementsWindow.MeasurementType.Distance
        }

        MenuItem {
            id: radiusMenuItem
            text: qsTr ("Radius")
            checkable: true
            property var mode: MeasurementsWindow.MeasurementType.Radius
        }

        MenuItem {
            id: diameterMenuItem
            text: qsTr ("Diameter")
            checkable: true
            property var mode: MeasurementsWindow.MeasurementType.Diameter;
        }

        MenuItem {
            id: angleBetweenPlanesMenuItem
            text: qsTr ("Angle between planes")
            checkable: true
            property var mode: MeasurementsWindow.MeasurementType.AngleBetweenPlanes
        }

        MenuItem {
            id: angleBetweenVertexesMenuItem
            text: qsTr ("Angle between vertexes")
            checkable: true
            property var mode: MeasurementsWindow.MeasurementType.AngleBetweenVertexes
        }
    }

    onMenuCompleted: {
        menuBarItem.addMenu (measurementsTypeMenu);
    }

    onCurrentMeasurementModeChanged: {
        numberOfRequiredShapes = getNumberOfRequiredShapes();
        model.numberOfSelectedShapes = 0;
        measurementModeChanged (currentMeasurementMode);
    }

    Rectangle {
        id: measurementBar
        visible: currentMeasurementMode != -1
        radius: 3
        width: 300
        height: column.implicitHeight
        anchors.margins: 10
        anchors.top: parent.top
        anchors.right: parent.right
        color: "#CCFFFFFF"
        border.color: "#55000000"
        readonly property string textColor: "#BB000000"

        Column {
            id: column
            padding: 20
            spacing: 20
            width: parent.width

            Text {
                width: parent.width - 40
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 14
                font.bold: true
                color: measurementBar.textColor
                text: measurementsTypeMenu.currentMenuItemName
            }

            Text {
                visible: numberOfRequiredShapes != 0 && model.numberOfSelectedShapes !== numberOfRequiredShapes
                text: !model ? " " : !model.numberOfSelectedShapes ? qsTr ("Select ") + getShapesTypesString()
                                                                   : qsTr ("Selected ") + model.numberOfSelectedShapes +
                                                                     qsTr (" of ") + numberOfRequiredShapes
                font.pointSize: 13
                font.italic: true
                color: measurementBar.textColor
            }

            Text {
                id: resultText
                visible: !model ? "" : !model.numberOfSelectedShapes !== 0
                                        && model.numberOfSelectedShapes === numberOfRequiredShapes
                                        && model.measurementsResults !== ""
                property string units: isAngleMeasure() ? "" : lengthUnitComboBox.currentText
                text: !model ? "" : qsTr ("Result: ") + model.measurementsResults + units
                font.pointSize: 13
                color: measurementBar.textColor
            }

            Row {
                visible: resultText.visible

                Text {
                    text: qsTr ("Units: ")
                    font.pointSize: 13
                    color: measurementBar.textColor
                    anchors.verticalCenter: parent.verticalCenter
                }

                ComboBox {
                    id: lengthUnitComboBox
                    visible: resultText.visible && !isAngleMeasure()
                    model: ["mm", "cm", "m", "in", "ft", "yd"]
                    onCurrentIndexChanged: measurementLengthUnitsChanged (currentIndex);
                }

                ComboBox {
                    currentIndex: 1
                    visible: resultText.visible && isAngleMeasure()
                    model: ["rad", "deg"]
                    onCurrentIndexChanged: measurementAngleUnitsChanged (currentIndex);
                }
            }
        }
    }
}
