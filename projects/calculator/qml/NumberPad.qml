import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import calculator

Item {
    id: controller
    implicitHeight: mainGrid.implicitHeight

    readonly property color qtGreenColor: "#2CDE85"
    readonly property color backspaceRedColor: "#DE2C2C"
    readonly property int spacing: 5

    Rectangle {
        id: numberPad
        anchors.fill: parent
        color: "transparent"
        radius: 8

        GridLayout {
            id: mainGrid
            anchors.fill: parent
            columns: 4
            rowSpacing: controller.spacing
            columnSpacing: controller.spacing

            DigitButton { text: "7" }
            DigitButton { text: "8" }
            DigitButton { text: "9" }
            OperatorButton {
                text: "÷"
                accentColor: controller.qtGreenColor
            }

            DigitButton { text: "4" }
            DigitButton { text: "5" }
            DigitButton { text: "6" }
            OperatorButton {
                text: "×"
                accentColor: controller.qtGreenColor
            }

            DigitButton { text: "1" }
            DigitButton { text: "2" }
            DigitButton { text: "3" }
            OperatorButton {
                text: "-"
                accentColor: controller.qtGreenColor
            }

            DigitButton { text: "0" }
            DigitButton { text: "." }
            RoundButton {
                implicitWidth: 38
                implicitHeight: 38
                radius: 8
                background: Rectangle {
                    color: controller.backspaceRedColor
                    radius: 8
                }

                Image {
                    anchors.centerIn: parent
                    source: "../assets/images/backspace_fill.svg"
                    width: parent.width * 0.6
                    height: width
                    fillMode: Image.PreserveAspectFit
                }
            }
            OperatorButton {
                text: "+"
                accentColor: controller.qtGreenColor
                implicitWidth: 48
            }
        }
    }
}
