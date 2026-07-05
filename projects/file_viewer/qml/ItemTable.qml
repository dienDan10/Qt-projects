import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    property alias model: table.model
    // expose current selection
    property int currentRow: table.currentRow
    property int currentColumn: table.currentColumn

    signal cellActivated(int row, int column)
    signal columnHeaderClicked(int column)
    signal rowHeaderClicked(int row)

    Rectangle {
        anchors.fill: parent
        color: "#1e1e1e"
    }

    // ===== HEADER (HORIZONTAL) =====
    HorizontalHeaderView {
        id: hHeader
        anchors {
            left: vHeader.right
            right: parent.right
            top: parent.top
        }
        syncView: table
        clip: true

        delegate: Rectangle {
            id: hCell
            required property int column
            required property var display

            implicitWidth: 140
            implicitHeight: 30
            color: hHover.hovered ? "#3a3a3a" : "#2d2d2d"
            border.color: "#444"

            Text {
                anchors.centerIn: parent
                text: hCell.display
                color: "white"
                font.bold: true
                elide: Text.ElideRight
            }

            HoverHandler { id: hHover }

            TapHandler {
                onTapped: root.columnHeaderClicked(column)
            }
        }
    }

    // ===== HEADER (VERTICAL) =====
    VerticalHeaderView {
        id: vHeader
        anchors {
            top: hHeader.bottom
            bottom: parent.bottom
            left: parent.left
        }
        syncView: table
        clip: true

        delegate: Rectangle {
            id: vCell
            required property int row
            required property var display

            implicitWidth: 40
            implicitHeight: 36
            color: vHover.hovered ? "#3a3a3a" : "#2d2d2d"
            border.color: "#444"

            Text {
                anchors.centerIn: parent
                text: vCell.display
                color: "white"
                font.bold: true
                elide: Text.ElideRight
            }

            HoverHandler { id: vHover }

            TapHandler {
                onTapped: root.rowHeaderClicked(vCell.row)
            }
        }
    }

    // ===== TABLE =====
    TableView {
        id: table
        anchors {
            left: vHeader.right
            right: parent.right
            top: hHeader.bottom
            bottom: parent.bottom
        }
        clip: true
        reuseItems: true
        boundsBehavior: Flickable.StopAtBounds
        interactive: true
        rowSpacing: 1
        columnSpacing: 1

        // ===== sizing =====
        columnWidthProvider: function(column) {
            return 140
        }
        rowHeightProvider: function(row) {
            return 36
        }

        // ===== selection mode =====
        selectionModel: ItemSelectionModel {
            onCurrentChanged: (cur, prev) => {
                console.log(`Current: (row=${cur.row}, col=${cur.column})`)
            }
        }
        selectionBehavior: TableView.SelectCells
        selectionMode: TableView.SingleSelection

        // ===== delegate =====
        delegate: Rectangle {
            id: cell
            required property int row
            required property int column
            required property var model
            required property bool selected
            required property bool current

            implicitHeight: 36
            implicitWidth: 140
            color: {
                if (current)
                    return "#2d72d9"
                if (selected)
                    return "#3a3a3a"
                return row % 2 === 0 ? "#252526" : "#1f1f1f"
            }
            border.color: "#333"

            Text {
                anchors.centerIn: parent
                text: display   // Qt DisplayRole
                color: "white"
                elide: Text.ElideRight
            }

            HoverHandler { id: hover }
            Rectangle {
                anchors.fill: parent
                visible: hover.hovered
                color: "#20ffffff"
            }

            TapHandler {
                onDoubleTapped: {
                    root.cellActivated(row, column)
                }
            }
        }
    }
}