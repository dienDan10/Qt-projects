import QtQuick

Rectangle {
    id: root

    property string text: "1"
    property color clrBorder: "#AAAAAA"

    signal clicked(string text)

    radius: 8
    color: mouseArea.containsMouse ? Config.clrNumberBtn : "transparent"
    border.color: mouseArea.containsMouse ? "transparent" : clrBorder
    border.width: 2

    Text {
        id: txtNum
        text: root.text
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: Config.fontNumberBtn
        color: mouseArea.containsMouse
               ? Config.clrNumberBtnTextHovered : Config.clrNumberBtnText
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked(root.text)
        onPressed: root.scale = 0.95
        onReleased: root.scale = 1.0
    }

    Behavior on scale {
        NumberAnimation {
            duration: 200
        }
    }
}
