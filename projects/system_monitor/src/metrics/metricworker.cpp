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

double MetricWorker::getDeviceTotalRam()
{
    double totalRam = m_metricProvider->getTotalRam();
    // handle -1 return;
    return totalRam;
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
    CpuMetric cpuMetric = m_metricProvider->readCpuMetric();
    // todo: handle -1;
    emit cpuMetricReceived(cpuMetric);
}

void MetricWorker::getRamMetric()
{
    RamMetric ramMetric = m_metricProvider->readRamMetric();
    // todo: handle no value return;
    emit ramMetricReceived(ramMetric);
}
