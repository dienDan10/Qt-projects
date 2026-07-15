/**
 * @file      monitorcontroller.h
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef MONITORCONTROLLER_H
#define MONITORCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QXYSeries>
#include <QPointF>
#include <QPointer>
#include "metrics/metricworker.h"

class MonitorController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentCpu READ currentCpu NOTIFY currentCpuChanged FINAL)
    Q_PROPERTY(int currentRam READ currentRam NOTIFY currentRamChanged FINAL)
public:
    explicit MonitorController(QObject *parent = nullptr);

    Q_INVOKABLE void setCpuSeries(QXYSeries* cpuSeries);
    Q_INVOKABLE void setRamSeries(QXYSeries* ramSeries);
    Q_INVOKABLE void pauseMonitor();
    Q_INVOKABLE void resumeMonitor();

    int currentCpu();
    int currentRam();

signals:
    void currentCpuChanged();
    void currentRamChanged();

private:
    void initialize();
    void initializeFail();
    void onCpuMetricReceived(double metric);
    void onRamMetricReceived(double metric);

private:
    enum class ControllerState {
        INITIALIZING = 0,
        RUNNING,
        PAUSED
    };

private:
    MetricWorker* m_metricWorker = nullptr;
    QThread* m_workerThread = nullptr;
    ControllerState m_monitorState = ControllerState::INITIALIZING;

    double m_currentCpu = 0;
    double m_currentRam = 0;

    QPointer<QXYSeries> m_cpuSeries;
    QList<QPointF> m_cpuPoints;

    QPointer<QXYSeries> m_ramSeries;
    QList<QPointF> m_ramPoints;
};

#endif // MONITORCONTROLLER_H
