import QtQuick
import QtQuick.Layouts

GridLayout {
    columns: 4
    columnSpacing: 10
    rowSpacing: 10

    // Row 1: 7 8 9 /
    NumberBtn {
        text: "7"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "8"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "9"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    OperatorBtn {
        text: "/"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    // Row 2: 4 5 6 x
    NumberBtn {
        text: "4"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "5"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "6"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    OperatorBtn {
        text: "x"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    // Row 3: 1 2 3 -
    NumberBtn {
        text: "1"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "2"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "3"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    OperatorBtn {
        text: "-"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    // Row 4: +- 0 . +
    NumberBtn {
        text: "_"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "0"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    NumberBtn {
        text: "."
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    OperatorBtn {
        text: "+"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    // Row 5: backspace AC =
    BackspaceBtn {
        text: "Backspace"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    OperatorBtn {
        text: "AC"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    OperatorBtn {
        text: "="
        Layout.columnSpan: 2
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
