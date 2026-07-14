/**
 * @file      metricworker.h
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef METRICWORKER_H
#define METRICWORKER_H

#include <QObject>
#include <memory>
#include <QTimer>
#include "ISystemMetricProvider.h"

class MetricWorker : public QObject
{
    Q_OBJECT
public:
    explicit MetricWorker(QObject *parent = nullptr);

signals:
    void initializeFailed();
    void cpuMetricReceived(double metric);
    void ramMetricReceived(double metric);

public slots:
    void initialize();
    void pauseTimer();
    void resumeTimer();

private:
    void getSystemMetrics();
    void getCpuMetric();
    void getRamMetric();

private:
    std::unique_ptr<ISystemMetricProvider> m_metricProvider;
    QTimer* m_timer = nullptr;
};

#endif // METRICWORKER_H
