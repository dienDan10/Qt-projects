import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtCharts

ApplicationWindow {
    id: root
    width: 1000
    height: 700
    visible: true
    title: "System Monitor"
    color: Theme.current.surface

    property bool paused: false

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: Theme.current.surfaceBright }
            GradientStop { position: 1.0; color: Theme.current.surface }
        }
    }

    Rectangle {
        x: -160
        y: -120
        width: 380
        height: 380
        radius: 190
        color: Theme.current.primaryContainer
        opacity: 0.14
    }

    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 340
        height: 340
        radius: 170
        color: Theme.current.secondaryContainer
        opacity: 0.12
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.spacing.pageMargin
        spacing: Theme.spacing.sectionGap

        ControlBar {
            Layout.fillWidth: true

            paused: root.paused

            onPauseClicked: root.paused = true
            onResumeClicked: root.paused = false
        }

        Label {
            text: "Live CPU and memory activity"
            color: Theme.current.surfaceVariantOn
            font.family: Theme.typography.familySans
            font.pixelSize: Theme.typography.bodyPixelSize
            font.weight: Theme.typography.bodyWeight
            Layout.fillWidth: true
        }

        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: root.width > 920 ? 2 : 1
            rowSpacing: Theme.spacing.sectionGap
            columnSpacing: Theme.spacing.sectionGap

            MetricCard {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "CPU Usage"
                subtitle: "23 %"
                paused: root.paused
            }

            MetricCard {
                Layout.fillWidth: true
                Layout.fillHeight: true

                title: "Memory Usage"
                subtitle: "6.3 GB / 16 GB"
                paused: root.paused
            }
        }
    }
}
