import CadEx 1.2

BaseWindow {
    property var viewPort: viewPortItem

    ModelPrsQtQuick_ViewPort {
        id: viewPortItem
        objectName: "viewPort"
        anchors.fill: parent
        highlightEnabled: true
    }
}
