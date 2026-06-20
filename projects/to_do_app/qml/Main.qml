pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts

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