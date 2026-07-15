/**
 * @file      monitorcontroller.cpp
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "monitorcontroller.h"

MonitorController::MonitorController(QObject *parent)
    : QObject{parent}
{
    initialize();
}

void MonitorController::initialize()
{
    m_metricWorker = new MetricWorker();
    m_workerThread = new QThread(this);

    connect(m_workerThread, &QThread::started, m_metricWorker, &MetricWorker::initialize);
    connect(m_workerThread, &QThread::finished, m_metricWorker, &QObject::deleteLater);

    connect(m_metricWorker, &MetricWorker::initializeFailed, this, &MonitorController::initializeFail);
    connect(m_metricWorker, &MetricWorker::cpuMetricReceived, this, &MonitorController::onCpuMetricReceived);
    connect(m_metricWorker, &MetricWorker::ramMetricReceived, this, &MonitorController::onRamMetricReceived);

    // setup points
    for (int i = 0; i < 60; i++) {
        m_cpuPoints.append(QPointF(i, 0));
        m_ramPoints.append(QPointF(i, 0));
    }

    m_workerThread->start();
}

void MonitorController::initializeFail()
{
    // Todo: We can quite the app here or show error
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

}

void MonitorController::resumeMonitor()
{

}

int MonitorController::currentCpu()
{
    return m_currentCpu;
}

int MonitorController::currentRam()
{
    return m_currentRam;
}

void MonitorController::onCpuMetricReceived(double metric)
{
    for (int i = 0; i < 59; i++) {
        m_cpuPoints[i].setY(m_cpuPoints[i + 1].y());
    }
    m_cpuPoints[59].setY(metric);
    m_currentCpu = static_cast<int>(std::round(metric));
    emit currentCpuChanged();

    if (m_cpuSeries != nullptr) {
        m_cpuSeries->replace(m_cpuPoints);
    }
}

void MonitorController::onRamMetricReceived(double metric)
{
    for (int i = 0; i < 59; i++) {
        m_ramPoints[i].setY(m_ramPoints[i + 1].y());
    }
    m_ramPoints[59].setY(metric);
    m_currentRam = static_cast<int>(std::round(metric));
    emit currentRamChanged();

    if (m_ramSeries != nullptr) {
        m_ramSeries->replace(m_ramPoints);
    }
}
