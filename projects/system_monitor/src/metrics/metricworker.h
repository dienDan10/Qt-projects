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

class MetricWorker : public QObject
{
    Q_OBJECT
public:
    explicit MetricWorker(QObject *parent = nullptr);

signals:
};

#endif // METRICWORKER_H
