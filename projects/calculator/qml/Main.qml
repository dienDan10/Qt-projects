import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import calculator


ApplicationWindow {
    id: window
    width: 320
    height: 480
    minimumHeight: height
    minimumWidth: width
    maximumHeight: height
    maximumWidth: width
    color: root.backgroundColor
    visible: true

    Item {
        id: root
        anchors.fill: parent

        readonly property int margin: 14
        readonly property color backgroundColor: "#222222"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.margin
            spacing: 14

            Display {
                id: display
                Layout.fillWidth: true
                Layout.preferredHeight: 200
            }

            NumberPad {
                id: numberPad
                Layout.margins: root.margin
                Layout.fillWidth: true
            }
        }
    }
}
