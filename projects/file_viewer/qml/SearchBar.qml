import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    property alias text: input.text
    property string placeholder: "Search..."
    signal searchTextChanged(string text)

    height: 42
    radius: 12
    color: input.activeFocus ? "#252525" : (controlArea.containsMouse ? "#232323" : "#1a1a1a")
    border.width: 1
    border.color: input.activeFocus ? "#4ea1ff" : "#333333"

    // Glow nhẹ khi focus
    layer.enabled: input.activeFocus
    layer.effect: null // (nếu dùng Qt5Compat.GraphicalEffects có thể thêm DropShadow ở đây)

    Behavior on color { ColorAnimation { duration: 150; easing.type: Easing.OutCubic } }
    Behavior on border.color { ColorAnimation { duration: 150; easing.type: Easing.OutCubic } }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 10
        spacing: 8

        Text {
            text: "🔍"
            font.pixelSize: 14
            opacity: input.activeFocus ? 1.0 : 0.6
            Behavior on opacity { NumberAnimation { duration: 150 } }
        }

        TextField {
            id: input
            Layout.fillWidth: true
            placeholderText: root.placeholder
            placeholderTextColor: "#6b6b6b"
            background: null
            color: "#f0f0f0"
            font.pixelSize: 14
            selectByMouse: true
            selectionColor: "#4ea1ff"
            onTextChanged: root.searchTextChanged(text)
            leftPadding: 0
            topPadding: 0
            bottomPadding: 0
        }

        // Nút xóa nhanh, chỉ hiện khi có text
        Text {
            visible: input.text.length > 0
            text: "✕"
            font.pixelSize: 12
            color: clearArea.containsMouse ? "#f0f0f0" : "#6b6b6b"
            Behavior on color { ColorAnimation { duration: 100 } }

            MouseArea {
                id: clearArea
                anchors.fill: parent
                anchors.margins: -6
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    input.text = ""
                    input.forceActiveFocus()
                }
            }
        }
    }

    MouseArea {
        id: controlArea
        anchors.fill: parent
        hoverEnabled: true
        z: -1
        onClicked: input.forceActiveFocus()
    }
}