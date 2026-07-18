import QtQuick
import QtCharts

Rectangle {
    id: root
    color: Theme.current.secondaryOn

    property alias areaSeries: line
    property alias chartLabelTL: topLeftLabel.text
    property alias chartLabelTR: topRightLabel.text
    property alias chartLabelBL: bottomLeftLabel.text
    property alias chartLabelBR: bottomRightLabel.text

    ChartView {
        id: chart

        legend.visible: false
        antialiasing: true
        backgroundColor: "transparent"
        plotAreaColor: "transparent"
        dropShadowEnabled: false
        anchors.fill: parent

        margins {
            top: Theme.spacing.md
            bottom: Theme.spacing.md
            left: 0
            right: 0
        }

        ValueAxis {
            id: axisX
            min: 0
            max: 59          // 60 seconds of history
            //visible: false   // Task Manager hides the x-axis labels
            tickCount: 15
            gridLineColor: Qt.rgba(Theme.current.primary.r, Theme.current.primary.g, Theme.current.primary.b, 0.15)
            labelsVisible: false
            lineVisible: false
            minorGridVisible: false
        }

        ValueAxis {
            id: axisY
            min: 0
            max: 100
            tickCount: 10
            gridLineColor: Qt.rgba(Theme.current.primary.r, Theme.current.primary.g, Theme.current.primary.b, 0.15)
            labelsVisible: false
            lineVisible: false
            minorGridVisible: false
        }

        AreaSeries {
            // id: areaSeries
            axisX: axisX
            axisY: axisY
            // color: Theme.current.primaryContainer
            borderColor: Theme.current.primary
            borderWidth: 1
            color: Qt.rgba(Theme.current.primary.r, Theme.current.primary.g, Theme.current.primary.b, 0.1)

            upperSeries: LineSeries {
                id: line
            }
        }
    }

    Text {
        id: topRightLabel
        text: "100%"
        color: Theme.current.primary
        font.pixelSize: Theme.typography.labelSmallPixelSize
        font.weight: Theme.typography.labelSmallWeight
        anchors.top: root.top
        anchors.right: root.right
        anchors.topMargin: 7
        anchors.rightMargin: 12
        z: 10   // ensure it renders above the chart
    }

    Text {
        id: topLeftLabel
        text: "% Utilization"
        color: Theme.current.primary
        font.pixelSize: Theme.typography.labelSmallPixelSize
        font.weight: Theme.typography.labelSmallWeight
        anchors.top: root.top
        anchors.left: root.left
        anchors.topMargin: 7
        anchors.leftMargin: 12
        z: 10   // ensure it renders above the chart
    }

    Text {
        id: bottomRightLabel
        text: "0"
        color: Theme.current.primary
        font.pixelSize: Theme.typography.labelSmallPixelSize
        font.weight: Theme.typography.labelSmallWeight
        anchors.bottom: root.bottom
        anchors.right: root.right
        anchors.bottomMargin: 7
        anchors.rightMargin: 12
        z: 10   // ensure it renders above the chart
    }

    Text {
        id: bottomLeftLabel
        text: "60 seconds"
        color: Theme.current.primary
        font.pixelSize: Theme.typography.labelSmallPixelSize
        font.weight: Theme.typography.labelSmallWeight
        anchors.bottom: root.bottom
        anchors.left: root.left
        anchors.bottomMargin: 7
        anchors.leftMargin: 12
        z: 10   // ensure it renders above the chart
    }
}
