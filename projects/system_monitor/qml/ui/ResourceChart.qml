import QtQuick
import QtCharts

ChartView {
    id: chart

    property bool paused: false
    property var samples: []

    legend.visible: false
    antialiasing: true
    backgroundColor: "transparent"
    plotAreaColor: "transparent"
    dropShadowEnabled: false

    ValueAxis {
        id: axisX
        min: 0
        max: 59
        labelsVisible: false
    }

    ValueAxis {
        id: axisY
        min: 0
        max: 100
        tickCount: 6
    }

    AreaSeries {
        axisX: axisX
        axisY: axisY
        color: Theme.current.primaryContainer

        upperSeries: LineSeries {
            id: line
            width: 2.5
            color: Theme.current.primary
        }
    }

    Component.onCompleted: {
        samples = [];

        for (let i = 0; i < 60; ++i)
            samples.push(0);

        syncSeries();
    }

    function syncSeries() {
        line.clear();

        for (let i = 0; i < samples.length; ++i)
            line.append(i, samples[i]);
    }

    Timer {
        interval: 1000
        repeat: true
        running: true

        onTriggered: {
            if (chart.paused)
                return;

            if (samples.length !== 60) {
                samples = [];

                for (let i = 0; i < 60; ++i)
                    samples.push(0);
            }

            samples.shift();
            samples.push(Math.random() * 100);

            syncSeries();
        }
    }
}
