import QtQuick.Controls 2.3
import CadEx 1.2

BaseViewerWindow {
    signal selectionModeChanged (var index)
    signal selectionFilterChanged (var index)

    enum SelectionMode {
        None = 0x00,
        Node = 0x01,
        Face = 0x08,
        Edge = 0x20
    }

    enum SelectionFilters {
        None       = 0x00,
        CircleEdge = 0x01,
        PlanarFace = 0x02,
        RevolFace  = 0x04
    }


    Menu {
        id: selectionModeMenu
        title: qsTr("&Selection mode")
        property var selectionModeMask: SelectionHandlingWindow.SelectionMode.None

        onSelectionModeMaskChanged: {
            selectionModeChanged (selectionModeMask);
        }

        function updateMask (theMode, checked)
        {
            selectionModeMask = checked ? selectionModeMask | theMode
                                        : selectionModeMask & ~theMode;
        }

        MenuItem {
            text: qsTr("&None")
            checkable: true
            checked: !nodeSelectionModeMenuItem.checked &&
                     !faceSelectionModeMenuItem.checked &&
                     !edgeSelectionModeMenuItem.checked
            onCheckedChanged: {
                if (checked) {
                    nodeSelectionModeMenuItem.checked = false;
                    faceSelectionModeMenuItem.checked = false;
                    edgeSelectionModeMenuItem.checked = false;
                }
                selectionModeMenu.updateMask (SelectionHandlingWindow.SelectionMode.None, checked);
            }
        }
        MenuItem {
            id: nodeSelectionModeMenuItem
            text: qsTr("&Node")
            checkable: true
            onCheckedChanged: {
                if (checked) {
                    faceSelectionModeMenuItem.checked = false;
                    edgeSelectionModeMenuItem.checked = false;
                }
                selectionModeMenu.updateMask (SelectionHandlingWindow.SelectionMode.Node, checked)
            }
        }
        MenuItem {
            id: faceSelectionModeMenuItem
            text: qsTr("&Face")
            checkable: true
            onCheckedChanged: {
                if (checked) {
                    nodeSelectionModeMenuItem.checked = false;
                }
                selectionModeMenu.updateMask (SelectionHandlingWindow.SelectionMode.Face, checked);
            }
        }
        MenuItem {
            id: edgeSelectionModeMenuItem
            text: qsTr("&Edge")
            checkable: true
            onCheckedChanged: {
                if (checked) {
                    nodeSelectionModeMenuItem.checked = false;
                }
                selectionModeMenu.updateMask (SelectionHandlingWindow.SelectionMode.Edge, checked);
            }
        }
    }

    Menu {
        id: selectionFilterMenu
        title: qsTr("&Selection Filter")
        property int selectionFilterMask: SelectionHandlingWindow.SelectionFilters.None

        onSelectionFilterMaskChanged: {
            selectionFilterChanged (selectionFilterMask);
        }

        function updateMask (theFilter, checked)
        {
            selectionFilterMask = checked ? selectionFilterMask | theFilter
                                          : selectionFilterMask & ~theFilter
        }

        MenuItem {
            text: qsTr("&None")
            checkable: true
            checked: !circleFilterMenuItem.checked &&
                     !planarFacesMenuItem.checked &&
                     !radialSurfacesMenuItem.checked
            onCheckedChanged: {
                if (checked) {
                    circleFilterMenuItem.checked = false;
                    planarFacesMenuItem.checked = false;
                    radialSurfacesMenuItem.checked = false;
                }
                selectionFilterMenu.updateMask (SelectionHandlingWindow.SelectionFilters.None, checked);
            }
        }
        MenuItem {
            id: circleFilterMenuItem
            text: qsTr("&Circle edges only")
            checkable: true
            onCheckedChanged: {
                selectionFilterMenu.updateMask (SelectionHandlingWindow.SelectionFilters.CircleEdge, checked);
            }
        }
        MenuItem {
            id: planarFacesMenuItem
            text: qsTr("&Planar faces only")
            checkable: true
            onCheckedChanged: {
                selectionFilterMenu.updateMask (SelectionHandlingWindow.SelectionFilters.PlanarFace, checked);
            }
        }
        MenuItem {
            id: radialSurfacesMenuItem
            text: qsTr("&Revolution faces only")
            checkable: true
            onCheckedChanged: {
                selectionFilterMenu.updateMask (SelectionHandlingWindow.SelectionFilters.RevolFace, checked);
            }
        }
    }

    onMenuCompleted: {
        menuBarItem.addMenu (selectionModeMenu);
        menuBarItem.addMenu (selectionFilterMenu);
    }
}
