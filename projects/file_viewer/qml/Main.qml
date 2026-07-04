import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Dialogs
import fileviewer.singleton 1.0


ApplicationWindow {
    id: window
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 250
    visible: true

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        // Button open file Dialog
        OpenFileButton {
            id: btn_open_file
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.rightMargin: 10
            onFileSelected: (fileUrl) => {
                ActionProvider.loadFile(fileUrl)
            }
        }
        // Item table
        ItemTable {
            id: item_table
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: ItemModel
            onCellActivated: (row, column) => {
                        console.log("Double click:", row, column)
                    }
        }
    }

}
