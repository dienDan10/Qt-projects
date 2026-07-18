/**
 * @file      monitorcontroller.cpp
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "monitorcontroller.h"
#include <QDebug>
MonitorController::MonitorController(QObject *parent)
    : QObject{parent}
{
}

MonitorController::~MonitorController()
{
    if (m_workerThread) {
        m_workerThread->quit();
        if (! m_workerThread->wait(1000)) {
            // incase thread cannot stop due to the worker is still running
            // that means the worker logic have problem
            qCritical() << "Metric workder thread failed to quit on time.";
        }
    }
}

void MonitorController::initialize()
{
    m_metricWorker = new MetricWorker();
    m_workerThread = new QThread(this);
    m_metricWorker->moveToThread(m_workerThread);

    connect(m_workerThread, &QThread::started, m_metricWorker, &MetricWorker::initialize);
    connect(m_workerThread, &QThread::finished, m_metricWorker, &QObject::deleteLater);

    connect(m_metricWorker, &MetricWorker::initializeFailed, this, [this]() {
        emit initializeFail();
    });
    connect(m_metricWorker, &MetricWorker::cpuMetricReceived, this, &MonitorController::onCpuMetricReceived);
    connect(m_metricWorker, &MetricWorker::ramMetricReceived, this, &MonitorController::onRamMetricReceived);
    connect(this, &MonitorController::monitorPaused, m_metricWorker, &MetricWorker::pauseTimer);
    connect(this, &MonitorController::monitorResume, m_metricWorker, &MetricWorker::resumeTimer);

    // setup points
    for (int i = 0; i < 60; i++) {
        m_cpuPoints.append(QPointF(i, 0));
        m_ramPoints.append(QPointF(i, 0));
    }

    // get device total ram
    m_deviceTotalRam = m_metricWorker->getDeviceTotalRam() / (1024.0 * 1024.0 * 1024.0);

    m_workerThread->start();
}

void MonitorController::setCpuSeries(QXYSeries *cpuSeries)
{
    m_cpuSeries = cpuSeries;
}

void MonitorController::setRamSeries(QXYSeries *ramSeries)
{
    m_ramSeries = ramSeries;
}

void MonitorController::pauseMonitor()
{
    if (m_isPaused) return;
    m_isPaused = true;
    emit monitorPaused();
    emit isPausedChanged();
}

void MonitorController::resumeMonitor()
{
    if (!m_isPaused) return;
    m_isPaused = false;
    emit monitorResume();
    emit isPausedChanged();
}

int MonitorController::currentCpu()
{
    return m_currentCpu;
}

double MonitorController::currentRam()
{
    return m_currentRam;
}

double MonitorController::deviceTotalRam()
{
    return m_deviceTotalRam;
}

bool MonitorController::isPaused()
{
    return m_isPaused;
}

void MonitorController::onCpuMetricReceived(CpuMetric metric)
{
    for (int i = 0; i < 59; i++) {
        m_cpuPoints[i].setY(m_cpuPoints[i + 1].y());
    }
    m_cpuPoints[59].setY(metric.usePercentage);
    m_currentCpu = static_cast<int>(std::round(metric.usePercentage));
    emit currentCpuChanged();

    if (m_cpuSeries != nullptr) {
        m_cpuSeries->replace(m_cpuPoints);
    }
}

void MonitorController::onRamMetricReceived(RamMetric ramMetric)
{
    for (int i = 0; i < 59; i++) {
        m_ramPoints[i].setY(m_ramPoints[i + 1].y());
    }
    m_ramPoints[59].setY(ramMetric.usePercentage);
    m_currentRam = (ramMetric.totalRam - ramMetric.availableRam) / (1024.0 * 1024.0 * 1024.0);
    emit currentRamChanged();

    if (m_ramSeries != nullptr) {
        m_ramSeries->replace(m_ramPoints);
    }
}
