import QtQuick 2.15

Item {
    anchors.fill: parent
    // backgound color
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: Theme.current.surfaceContainer
            }
            GradientStop {
                position: 1.0
                color: Theme.current.surfaceDim
            }
        }
    }

    // decorating background
    Rectangle {
        x: -160
        y: -120
        width: 380
        height: 380
        radius: 190
        color: Theme.current.primaryContainer
        opacity: 0.8
    }

    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 340
        height: 340
        radius: 170
        color: Theme.current.secondaryContainer
        opacity: 0.8
    }
}
