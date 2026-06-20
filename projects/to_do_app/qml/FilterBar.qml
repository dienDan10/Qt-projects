pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root
    height: 44
    color: "transparent"

    required property TaskFilterProxy taskModel
    required property Dispatcher dispatcher

    readonly property var filterValues: [FilterType.All, FilterType.Active, FilterType.Completed]

    RowLayout {
        anchors.centerIn: parent
        spacing: 4

        Repeater {
            model: ["All", "Active", "Completed"]

            delegate: Rectangle {
                id: filterButton
                required property int index
                required property string modelData

                width: 90
                height: 32
                radius: 16
                color: root.taskModel.currentFilter === root.filterValues[index] ? "#212121" : "transparent"
                border.width: 1
                border.color: root.taskModel.currentFilter === root.filterValues[index] ? "#212121" : "#BDBDBD"

                Text {
                    anchors.centerIn: parent
                    text: parent.modelData
                    font.pixelSize: 13
                    color: root.taskModel.currentFilter === root.filterValues[filterButton.index] ? "white" : "#757575"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.dispatcher.setFilter(root.filterValues[filterButton.index])
                }
            }
        }
    }
}