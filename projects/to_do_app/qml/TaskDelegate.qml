import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root

    required property int index
    required property string title
    required property bool done

    // signals
    signal deleteTaskRequested(int index);
    signal toggleDoneRequested(int index);

    width: ListView.view.width
    height: 52
    color: "transparent"

    RowLayout {
        anchors {
            fill: parent
            leftMargin: 12
            rightMargin: 12
        }
        spacing: 10

        // Checkbox
        Rectangle {
            width: 20
            height: 20
            radius: 4
            border.width: 1.5
            border.color: root.done ? "#4CAF50" : "#BDBDBD"
            color: root.done ? "#4CAF50" : "transparent"

            Text {
                anchors.centerIn: parent
                text: "✓"
                color: "white"
                font.pixelSize: 13
                visible: root.done
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.toggleDoneRequested(root.index)
            }
        }

        // Title
        Text {
            Layout.fillWidth: true
            text: root.title
            font.pixelSize: 14
            color: root.done ? "#BDBDBD" : "#212121"
            elide: Text.ElideRight
        }

        // Delete button
        Rectangle {
            width: 28
            height: 28
            radius: 14
            color: deleteArea.containsMouse ? "#FFEBEE" : "transparent"

            Text {
                anchors.centerIn: parent
                text: "✕"
                font.pixelSize: 13
                color: deleteArea.containsMouse ? "#E53935" : "#BDBDBD"
            }

            MouseArea {
                id: deleteArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: root.deleteTaskRequested(root.index)
            }
        }
    }

    // Separator
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: "#F0F0F0"
    }
}