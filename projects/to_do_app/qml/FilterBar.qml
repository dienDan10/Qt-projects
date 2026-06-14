import QtQuick
import QtQuick.Layouts
import to_do_app

Rectangle {
    height: 44
    color: "transparent"

    RowLayout {
        anchors.centerIn: parent
        spacing: 4

        Repeater {
            model: ["All", "Active", "Completed"]

            delegate: Rectangle {
                required property int index
                required property string modelData

                width: 90
                height: 32
                radius: 16
                color: task_proxy.filter === index ? "#212121" : "transparent"
                border.width: 1
                border.color: task_proxy.filter === index ? "#212121" : "#BDBDBD"

                Text {
                    anchors.centerIn: parent
                    text: parent.modelData
                    font.pixelSize: 13
                    color: task_proxy.filter === index ? "white" : "#757575"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: task_proxy.filter = parent.index
                }
            }
        }
    }
}