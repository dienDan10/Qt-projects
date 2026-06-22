import QtQuick
import QtQuick.Controls

RoundButton {
    id: calculatorButton
    implicitWidth: 38
    implicitHeight: 38
    radius: buttonRadius

    readonly property int fontSize: 22
    readonly property int buttonRadius: 8
    property color textColor: "#FFFFFF"
    property color accentColor: "#2CDE85"
    readonly property color backgroundColor: "#222222"
    readonly property color borderColor: "#A9A9A9"


    background: Rectangle {
        anchors.fill: parent
        color: calculatorButton.backgroundColor
        border.color: calculatorButton.borderColor
        radius: calculatorButton.buttonRadius
    }

    contentItem: Text {
        text: calculatorButton.text
        font.pixelSize: calculatorButton.fontSize
        color: calculatorButton.textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        // add animation for color change
        Behavior on color {
            ColorAnimation {
                duration: 120
                easing.type: Easing.OutElastic
            }
        }
    }
}