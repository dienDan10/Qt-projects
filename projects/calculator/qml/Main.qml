import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import calculator


ApplicationWindow {
    id: window
    width: 320
    height: 500
    minimumHeight: height
    minimumWidth: width
    maximumHeight: height
    maximumWidth: width
    color: Config.clrBackground
    visible: true

    ColumnLayout {
        anchors.fill: parent
        // Display
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 140
            Layout.margins: 14
            color: Config.clrDisplay
            radius: 8

            // calculation expression
            Text {
                id: txtExpression
                color: Config.clrExpression
                font.pointSize: Config.fontExpression
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    bottom: parent.verticalCenter
                    leftMargin: 10
                    rightMargin: 10
                }

                text: "30 + 61"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
            }

            // result
            Text {
                id: txtResult
                color: Config.clrExpression
                font.pointSize: Config.fontResult
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.verticalCenter
                    bottom: parent.bottom

                    leftMargin: 10
                    rightMargin: 10
                }

                text: "91"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
            }
        }

        // Numbers and Operations
        Keyboard {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 14
        }

    }
}
