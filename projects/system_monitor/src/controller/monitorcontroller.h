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
    Q_PROPERTY(double currentRam READ currentRam NOTIFY currentRamChanged FINAL)
    Q_PROPERTY(double deviceTotalRam READ deviceTotalRam NOTIFY deviceTotalRamChanged FINAL)
    Q_PROPERTY(bool isPaused READ isPaused NOTIFY isPausedChanged FINAL)
public:
    explicit MonitorController(QObject *parent = nullptr);
    ~MonitorController();

    Q_INVOKABLE void setCpuSeries(QXYSeries* cpuSeries);
    Q_INVOKABLE void setRamSeries(QXYSeries* ramSeries);
    Q_INVOKABLE void pauseMonitor();
    Q_INVOKABLE void resumeMonitor();

    int currentCpu();
    double currentRam();
    double deviceTotalRam();
    bool isPaused();
    void initialize();

signals:
    void initializeFail();
    void currentCpuChanged();
    void currentRamChanged();
    void deviceTotalRamChanged();
    void isPausedChanged();
    void monitorPaused();
    void monitorResume();

private:
    void onCpuMetricReceived(CpuMetric cpuMetric);
    void onRamMetricReceived(RamMetric ramMetric);

private:
    MetricWorker* m_metricWorker = nullptr;
    QThread* m_workerThread = nullptr;
    bool m_isPaused = false;

    double m_currentCpu = 0;
    double m_currentRam = 0;
    double m_deviceTotalRam = 0;

    QPointer<QXYSeries> m_cpuSeries;
    QList<QPointF> m_cpuPoints;

    QPointer<QXYSeries> m_ramSeries;
    QList<QPointF> m_ramPoints;
};

#endif // MONITORCONTROLLER_H
