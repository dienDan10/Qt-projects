/**
 * @file      raminfo.h
 * @author    diendanx
 * @date      2026-7-19
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef METRIC_H
#define METRIC_H

struct RamMetric {
    double totalRam{};
    double availableRam{};
    double usePercentage{};
};

struct CpuMetric {
    double usePercentage{};
};

#endif // METRIC_H
