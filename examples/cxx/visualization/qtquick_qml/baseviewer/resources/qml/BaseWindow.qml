import QtQuick 2.7
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0 as Platform
import CadEx 1.2

ApplicationWindow {
    title: qsTr ("CAD Exchanger")
    minimumWidth: 1000
    minimumHeight: 600
    width: 1000
    height: 600

    property alias loading: busyIndicator.running
    property alias menuBarItem: menuBarItem
    property alias fileMenuItem: fileMenuItem

    signal menuCompleted
    signal importFile (var url);

    menuBar: MenuBar {
        id: menuBarItem
        enabled: !loading

        Menu {
            id: fileMenuItem
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Import...")
                onTriggered: {
                    fileDialog.open()
                }
            }
            MenuSeparator { }
            MenuItem {
                text: qsTr("&Quit")
                onTriggered: {
                    Qt.quit();
                }
            }
        }

        Component.onCompleted: {
            menuCompleted();
        }
    }

    Platform.FileDialog {
        id: fileDialog
        title: qsTr ("Please choose a STEP file")
        fileMode: Platform.FileDialog.OpenFile
        options: Platform.FileDialog.DontResolveSymlinks | Platform.FileDialog.DontUseCustomDirectoryIcons
        folder: Platform.StandardPaths.writableLocation (Platform.StandardPaths.HomeLocation)
        nameFilters: [ "STEP files (*.stp *.step)" ]
        onAccepted: {
            importFile (file);
        }
    }

    Dialog {
        id: dialog
        objectName: "dialog"
        title: qsTr ("Error")
        parent: ApplicationWindow.overlay
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: 300
        standardButtons: Dialog.Ok
        visible: false
        closePolicy: Popup.CloseOnEscape
        dim: true

        property string message

        Label {
            anchors.left: parent.left
            anchors.right: parent.right
            text: dialog.message
        }
    }

    BusyIndicator {
        id: busyIndicator
        running: false
        visible: running
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        width: 80
        height: 80
        parent: ApplicationWindow.overlay
    }
}
