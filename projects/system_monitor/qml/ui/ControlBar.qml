import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    signal pauseClicked
    signal resumeClicked

    property bool paused: false

    implicitHeight: 84
    radius: Theme.spacing.radiusXl
    color: Theme.current.secondaryOn
    border.color: Theme.current.outlineVariant
    border.width: 1
    antialiasing: true

    // gradient: Gradient {
    //     GradientStop {
    //         position: 0.0
    //         color: Theme.current.surface
    //     }
    //     GradientStop {
    //         position: 1.0
    //         color: Theme.current.surfaceBright
    //     }
    // }

    RowLayout {
        anchors.fill: parent
        anchors.margins: Theme.spacing.cardPadding
        spacing: Theme.spacing.lg

        ColumnLayout {
            spacing: Theme.spacing.xxxs

            Label {
                text: "System Monitor"
                color: Theme.current.primary
                font.family: Theme.typography.familySans
                font.pixelSize: Theme.typography.appTitlePixelSize
                font.weight: Theme.typography.weightBold
                font.letterSpacing: Theme.typography.appTitleLetterSpacing
            }

            Label {
                text: paused ? "Metrics paused" : "Live system metrics"
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
            implicitWidth: 88
            implicitHeight: 34
            radius: 999
            color: paused ? Theme.current.secondaryContainer : Theme.current.primaryContainer
            border.color: Theme.current.outlineVariant
            border.width: 1
            Layout.alignment: Qt.AlignVCenter

            Label {
                anchors.centerIn: parent
                text: paused ? "Paused" : "Live"
                color: paused ? Theme.current.secondaryContainerOn : Theme.current.primaryContainerOn
                font.family: Theme.typography.familySans
                font.pixelSize: Theme.typography.labelMediumPixelSize
                font.weight: Theme.typography.labelMediumWeight
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            id: pauseButton
            text: "Pause"
            enabled: !paused
            Layout.alignment: Qt.AlignVCenter

            contentItem: Label {
                text: pauseButton.text
                color: pauseButton.enabled ? Theme.current.primaryOn : Theme.current.surfaceVariantOn
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: Theme.typography.familySans
                font.pixelSize: Theme.typography.buttonPixelSize
                font.weight: Theme.typography.buttonWeight
            }

            background: Rectangle {
                radius: 10
                color: pauseButton.enabled ? Theme.current.primary : Theme.current.surfaceContainerHigh
                border.color: Theme.current.outlineVariant
                border.width: 1
            }

            onClicked: pauseClicked()
        }

        Button {
            id: resumeButton
            text: "Resume"
            enabled: paused
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredWidth: implicitWidth
            Layout.maximumWidth: implicitWidth

            contentItem: Label {
                text: resumeButton.text
                color: resumeButton.enabled ? Theme.current.primaryOn : Theme.current.surfaceVariantOn
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: Theme.typography.familySans
                font.pixelSize: Theme.typography.buttonPixelSize
                font.weight: Theme.typography.buttonWeight
            }

            background: Rectangle {
                radius: 10
                color: resumeButton.enabled ? Theme.current.primary : Theme.current.surfaceContainerHigh
                border.color: Theme.current.outlineVariant
                border.width: 1
            }

            onClicked: resumeClicked()
        }
    }
}
