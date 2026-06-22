import QtQuick

Item {
    id: display
    property int fontSize: 22
    readonly property int maxDigits: Math.min(16, Math.floor(display.width / fontSize))
    readonly property color backgroundColor: "#262626"
    readonly property color qtGreenColor: "#2CDE85"

    Item {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: display.backgroundColor
            radius: 8

            Column {
                anchors.fill: parent
                anchors.margins: 14
                spacing: 4

                Text {
                    id: expressionText
                    text: "123 + 456"
                    font.pixelSize: display.fontSize
                    color: "#888888"
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignBottom
                    elide: Text.ElideLeft
                }

                Text {
                    id: resultText
                    text: "579"
                    font.pixelSize: display.fontSize
                    color: display.qtGreenColor
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignBottom
                    elide: Text.ElideLeft
                }
            }
        }
    }
}
