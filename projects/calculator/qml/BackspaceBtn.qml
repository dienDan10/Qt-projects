import QtQuick
import QtQuick.Effects

Rectangle {
    id: root

    property string text: "1"
    property color clrBorder: "#AAAAAA"

    signal clicked(string text)

    radius: 8
    color: mouseArea.containsMouse ? Config.clrBackspaceBtn : "transparent"
    border.color: Config.clrBackspaceBtn
    border.width: 2

    Image {
        id: btnIcon
        width: 30
        height: 30
        sourceSize.height: height
        sourceSize.width: width
        anchors.centerIn: parent
        source: mouseArea.containsMouse
                ? "../assets/images/backspace_fill.svg"
                : "../assets/images/backspace.svg"
    }

    MultiEffect {
        anchors.fill: btnIcon
        source: btnIcon

        // Settings required to overwrite image profile with flat color
        colorization: 1.0
        brightness: mouseArea.containsMouse ? 0 : 1.0
        colorizationColor: Config.clrBackspaceBtn // Target color
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
