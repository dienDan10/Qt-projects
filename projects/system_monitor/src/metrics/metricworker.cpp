/**
 * @file      metricworker.cpp
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "metricworker.h"
#include "metricproviderfactory.h"

MetricWorker::MetricWorker(QObject *parent)
    : QObject{parent}
{
    m_metricProvider = createSystemMetricProvider();
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
}

void MetricWorker::initialize()
{
    bool initResult = false;
    if (m_metricProvider != nullptr) {
        initResult = m_metricProvider->initialize();
    }

    if (!initResult) {
        emit initializeFailed();
        return;
    }

    connect(m_timer, &QTimer::timeout, this, [this]() {
        getSystemMetrics();
    });
    m_timer->start();
}

void MetricWorker::pauseTimer()
{
    m_timer->stop();
}

void MetricWorker::resumeTimer()
{
    m_timer->start();
}

void MetricWorker::getSystemMetrics()
{
    getCpuMetric();
    getRamMetric();
}

void MetricWorker::getCpuMetric()
{
    double cpuMetric = m_metricProvider->readCpuUsage();
    // todo: handle -1;
    emit cpuMetricReceived(cpuMetric);
}

void MetricWorker::getRamMetric()
{
    double ramMetric = m_metricProvider->readRamUsage();
    // todo: handle -1;
    emit ramMetricReceived(ramMetric);
}
