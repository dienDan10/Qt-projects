import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtCharts
import "../components"
import monitor.singleton 1.0

ApplicationWindow {
    id: root
    width: 1000
    height: 1200
    visible: true
    title: "System Monitor"
    color: Theme.current.surface

    property bool paused: Monitor.isPaused

    PrimaryBackground {}

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.spacing.pageMargin
        spacing: Theme.spacing.sectionGap

        //======================CONTROL BAR=================================
        ControlBar {
            Layout.fillWidth: true

            paused: root.paused

            onPauseClicked: {
                Monitor.pauseMonitor();
            }

            onResumeClicked: {
                Monitor.resumeMonitor();
            }
        }

        //======================== LABEL AND TOGGLE DARK LIGHT THEME =================
        RowLayout {
            Layout.fillWidth: true

            Label {
                text: "Live CPU and memory activity"
                color: Theme.current.surfaceVariantOn
                font.family: Theme.typography.familySans
                font.pixelSize: Theme.typography.bodyPixelSize
                font.weight: Theme.typography.bodyWeight
            }

            Item {
                Layout.fillWidth: true
            }

            BtnToggleTheme {
                dark: Theme.darkMode

                onToggled: {
                    Theme.darkMode = !Theme.darkMode;
                }
            }
        }

        //======================= METRIC MONITOR SECTION =============================
        GridLayout {
            Layout.fillWidth: true
            columns: root.width > 1200 ? 2 : 1
            rowSpacing: Theme.spacing.sectionGap
            columnSpacing: Theme.spacing.sectionGap

            MetricCard {
                id: cpuMetricCard
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 400
                Layout.maximumHeight: 400

                title: "CPU"
                subtitle: `${Monitor.currentCpu}%`
                chartLabelTL: "% Utilization"
                chartLabelBL: "60 seconds"
                chartLabelTR: `100%`
                chartLabelBR: "0"
                paused: root.paused

                Component.onCompleted: {
                    Monitor.setCpuSeries(cpuMetricCard.areaSeries);
                }
            }

            MetricCard {
                id: ramMetricCard
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 400
                Layout.maximumHeight: 400

                title: "Memory"
                subtitle: `${Monitor.currentRam.toFixed(1)} GB`
                chartLabelTL: "Memory Usage"
                chartLabelBL: "60 seconds"
                chartLabelTR: `${Monitor.deviceTotalRam.toFixed(1)} GB`
                chartLabelBR: "0"
                paused: root.paused

                Component.onCompleted: {
                    Monitor.setRamSeries(ramMetricCard.areaSeries);
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
