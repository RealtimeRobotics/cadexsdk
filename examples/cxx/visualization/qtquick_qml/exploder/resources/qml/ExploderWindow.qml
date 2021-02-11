import QtQuick 2.12
import QtQuick.Controls 2.3
import CadEx 1.2

BaseViewerWindow {
    id: root
    signal explodeValueChanged(var value)

    Rectangle {
        id: exploderBar
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
                color: exploderBar.textColor
                text: qsTr ("Explode value")
            }

            Row {
                width: parent.width - 40
                spacing: 10

                Slider {
                    id: slider
                    from: 0
                    to: 1
                    value: 0
                    stepSize: 0.02

                    onValueChanged: {
                        root.explodeValueChanged (value);
                    }

                    onPressedChanged: {
                        if (autoFitAll.checked && !pressed) {
                            viewPort.animatedFitAll();
                        }
                    }
                }

                Text {
                    text: Math.round (slider.value * 100) + " %"
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 12
                }
            }

            Row {
                Button {
                    width: 180
                    text: qsTr ("Fit-all")
                    onClicked: {
                        viewPort.animatedFitAll();
                    }
                }

                CheckBox {
                    id: autoFitAll
                    text: qsTr ("Auto")
                }
            }
        }
    }
}
