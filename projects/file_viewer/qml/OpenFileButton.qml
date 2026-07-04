import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Item {
    id: root
    width: 160
    height: 44

    signal fileSelected(string fileUrl)

    FileDialog {
        id: fileDialog
        title: "Chọn file"
        fileMode: FileDialog.OpenFile
        nameFilters: [
            "CSV file (*.csv)",
            "Json file (*.json)"
        ]
        onAccepted: {
            root.fileSelected(selectedFile)
        }
    }

    Rectangle {
        id: bg
        anchors.fill: parent
        radius: 10
        color: mouseArea.pressed ? "#2D6CDF" : (mouseArea.containsMouse ? "#3B82F6" : "#2563EB")

        border.color: "#1E40AF"
        border.width: 1

        Behavior on color {
            ColorAnimation { duration: 120 }
        }

        Text {
            anchors.centerIn: parent
            text: "📂 Mở file"
            color: "white"
            font.pixelSize: 14
            font.bold: true
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: fileDialog.open()
    }
}