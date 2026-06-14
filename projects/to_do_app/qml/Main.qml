import QtQuick
import QtQuick.Layouts
import to_do_app

Window {
    id: window
    width: 300
    height: 600
    visible: true
    title: qsTr("To Do App")

    TaskModel {
        id: taskModel
    }

    TaskFilterProxy {
        id: task_proxy
        sourceModel: taskModel

        function sourceIndex(proxyIndex) {
            return mapToSource(index(proxyIndex, 0)).row
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        FilterBar {
            id: filter_bar
            Layout.fillWidth: true
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: task_proxy
            delegate: TaskDelegate{
                onDeleteTaskRequested: (index) => taskModel.removeTask(task_proxy.sourceIndex(index))
                onToggleDoneRequested: (index) => taskModel.setDone(task_proxy.sourceIndex(index))
            }
        }
    }
}