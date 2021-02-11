import CadEx 1.2
import QtQuick 2.7
import QtQuick.Controls 2.3

BaseWindow {
    menuBarItem.background: Rectangle {
        color: viewCubeStyleItem.normalColor
        anchors.fill: parent
    }

    fileMenuItem.background: Rectangle {
        color: viewCubeStyleItem.normalColor
        implicitWidth: 200
    }

    ModelPrsQtQuick_ViewPort {
        id: viewPort
        objectName: "viewPort"
        anchors.fill: parent
        antialiasing: false
        selectionEnabled: true
        highlightEnabled: true
        trihedronEnabled: true
        gridPlaneEnabled: true

        backgroundStyle: ModelPrsQtQuick_BackgroundStyle {
            topColor: "#303030"
            bottomColor: "#303030"
        }
        viewCubeStyle: ModelPrsQtQuick_ViewCubeStyle {
            id: viewCubeStyleItem
            normalColor: "#6e6e6e"
            hoveredColor: "#545454"
            pressedColor: "#474747"
            textColor: "#949494"
            trihedronTextColor: "#949494"
        }

        property int viewCubeSize: Math.max (Math.min (viewPort.width, viewPort.height) / 5, 200)
        property int viewCubeMargins: 10

        viewCubeGeometry: Qt.rect (viewPort.width - viewCubeMargins - viewCubeSize,
                                   viewCubeMargins,
                                   viewCubeSize,
                                   viewCubeSize)
    }
}
