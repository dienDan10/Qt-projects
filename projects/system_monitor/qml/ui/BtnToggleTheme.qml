import QtQuick

Rectangle {
    id: root

    signal toggled

    property bool dark: false

    width: 50
    height: 28
    radius: height / 2

    color: dark ? Theme.current.surfaceVariantOn : Theme.current.primary

    border.width: 1
    border.color: dark ? Theme.current.surfaceVariantOn : Theme.current.primary

    Behavior on color {
        ColorAnimation {
            duration: 220
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            root.dark = !root.dark;
            root.toggled();
        }

        onPressed: thumb.scale = 0.92
        onReleased: thumb.scale = 1.0
    }

    Text {
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.verticalCenter: parent.verticalCenter

        text: "☀"
        font.pixelSize: 12
        opacity: dark ? 0.25 : 1.0

        Behavior on opacity {
            NumberAnimation {
                duration: 180
            }
        }
    }

    Text {
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter

        text: "🌙"
        font.pixelSize: 12
        opacity: dark ? 1.0 : 0.25

        Behavior on opacity {
            NumberAnimation {
                duration: 180
            }
        }
    }

    Rectangle {
        id: thumb

        width: 24
        height: 24
        radius: 15

        anchors.verticalCenter: parent.verticalCenter
        x: dark ? parent.width - width - 3 : 3

        color: "white"

        border.color: "#DDDDDD"

        Behavior on x {
            NumberAnimation {
                duration: 220
                easing.type: Easing.InOutCubic
            }
        }

        Behavior on scale {
            NumberAnimation {
                duration: 120
            }
        }

        Text {
            anchors.centerIn: parent
            text: dark ? "🌙" : "☀"
            font.pixelSize: 12
        }
    }
}
