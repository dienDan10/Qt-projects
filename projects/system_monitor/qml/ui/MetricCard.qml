import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    radius: Theme.spacing.radiusXl
    color: Theme.current.secondaryOn
    border.color: Theme.current.outlineVariant
    border.width: 1
    antialiasing: true

    // gradient: Gradient {
    //     GradientStop {
    //         position: 0.0
    //         color: Theme.current.surfaceContainer
    //     }
    //     GradientStop {
    //         position: 1.0
    //         color: Theme.current.surfaceContainerLow
    //     }
    // }

    property alias title: titleLabel.text
    property alias subtitle: valueLabel.text
    property bool paused: false
    property alias areaSeries: resouceChart.areaSeries
    property alias chartLabelTL: resouceChart.chartLabelTL
    property alias chartLabelTR: resouceChart.chartLabelTR
    property alias chartLabelBL: resouceChart.chartLabelBL
    property alias chartLabelBR: resouceChart.chartLabelBR

    implicitHeight: 400

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.spacing.cardPadding
        // spacing: Theme.spacing.md

        RowLayout {
            Layout.fillWidth: true

            ColumnLayout {
                spacing: Theme.spacing.xxxs

                Label {
                    id: titleLabel
                    color: Theme.current.primary
                    font.family: Theme.typography.familySans
                    font.pixelSize: Theme.typography.titleMediumPixelSize
                    font.weight: Theme.typography.weightSemiBold
                }

                Label {
                    id: valueLabel
                    color: Theme.current.primary
                    font.family: Theme.typography.familySans
                    font.pixelSize: Theme.typography.bodyPixelSize
                    font.weight: Theme.typography.bodyWeight
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Rectangle {
                implicitWidth: 76
                implicitHeight: 28
                radius: 999
                color: paused ? Theme.current.secondaryContainer : Theme.current.primaryContainer
                border.color: Theme.current.outlineVariant
                border.width: 1

                Label {
                    anchors.centerIn: parent
                    text: paused ? "Paused" : "Live"
                    color: paused ? Theme.current.secondaryContainerOn : Theme.current.primaryContainerOn
                    font.family: Theme.typography.familySans
                    font.pixelSize: Theme.typography.labelMediumPixelSize
                    font.weight: Theme.typography.labelMediumWeight
                }
            }
        }

        ResourceChart {
            id: resouceChart
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
