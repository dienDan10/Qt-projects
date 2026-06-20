pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: window
    width: 300
    height: 600
    visible: true
    title: qsTr("To Do App")

    required property TaskFilterProxy taskModel
    required property Dispatcher dispatcher

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            TextField {
                id: newTaskField
                Layout.fillWidth: true
                placeholderText: "Nhập task mới..."
                // View KHÔNG gọi taskModel.addTask() - method đó không còn tồn tại nữa.
                // Mọi ý định thay đổi state đi qua dispatcher.
                onAccepted: {
                    dispatcher.addTask(text)
                    text = ""
                }
            }
        }

        FilterBar {
            id: filter_bar
            Layout.fillWidth: true
            taskModel: window.taskModel
            dispatcher: window.dispatcher
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: window.taskModel
            delegate: TaskDelegate {
                dispatcher: window.dispatcher
            }
        }
    }
}