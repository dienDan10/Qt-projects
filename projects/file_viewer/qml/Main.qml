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
    color: "#1e1e1e"

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        // Button open file Dialog
        OpenFileButton {
            id: btn_open_file
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.margins: 10
            onFileSelected: (fileUrl) => {
                ActionProvider.loadFile(fileUrl)
            }
        }

        // filter text TextField
        SearchBar {
            id: search
            Layout.margins: 5
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.preferredWidth: 200

            text: ItemModel.searchText

            onSearchTextChanged: (text) => {
                ItemModel.searchText = text;
            }
        }

        // Item table
        ItemTable {
            id: item_table
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: ItemModel
            onColumnHeaderClicked: (column) => {
                ActionProvider.sortColumn(column)
            }
        }
    }

}
