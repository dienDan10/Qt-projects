import QtQuick

Rectangle {
    id: root

    property string text: "="
    property color clrBorder: "#AAAAAA"

    signal clicked(string text)

    radius: 8
    color: mouseArea.containsMouse ? Config.clrOperatorBtn : "transparent"
    border.color: mouseArea.containsMouse ? "transparent" : clrBorder
    border.width: 2

    Text {
        id: txtOperator
        text: root.text
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: Config.fontOperatorBtn
        font.bold: true
        color: mouseArea.containsMouse
               ? Config.clrOperatorBtnTextHovered : Config.clrOperatorBtnText
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