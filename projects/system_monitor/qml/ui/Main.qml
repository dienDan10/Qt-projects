import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtCharts
import "../components"

ApplicationWindow {
    id: root
    width: 1000
    height: 1200
    visible: true
    title: "System Monitor"
    color: Theme.current.surface

    property bool paused: false

    PrimaryBackground {}

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
            columns: root.width > 1200 ? 2 : 1
            rowSpacing: Theme.spacing.sectionGap
            columnSpacing: Theme.spacing.sectionGap

            MetricCard {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 500
                Layout.maximumHeight: 500

                title: "CPU Usage"
                subtitle: "23 %"
                paused: root.paused
            }

            MetricCard {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 500
                Layout.maximumHeight: 500

                title: "Memory Usage"
                subtitle: "6.3 GB / 16 GB"
                paused: root.paused
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
