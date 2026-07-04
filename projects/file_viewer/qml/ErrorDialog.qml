import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Item {
    Button {
        text: "MessageDialog loading";
        anchors.centerIn: parent
        onClicked: {
            dialog.visible = true
        }
    }

    MessageDialog {
        id: dialog
        text: qsTr("The document has been modified.")
        informativeText: qsTr("Do you want to save your changes?")
        buttons: MessageDialog.Ok | MessageDialog.Cancel
        onButtonClicked: function (button, role) {
            switch (button) {
                case MessageDialog.Ok:
                    document.save()
                    break;
            }
        }
    }
}
