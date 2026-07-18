/**
 * @file      windowmetricprovider.h
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef WINDOWMETRICPROVIDER_H
#define WINDOWMETRICPROVIDER_H
#include "ISystemMetricProvider.h"
// #include "windows.h"
#include <cstdint>
#include <minwindef.h>

class WindowMetricProvider : public ISystemMetricProvider
{
public:
    WindowMetricProvider();

    bool initialize() override;
    CpuMetric readCpuMetric() override;
    RamMetric readRamMetric() override;
    double getTotalRam() override;

private:
    static uint64_t FileTimeToInt64(const FILETIME& ft);

    /*
     * in general, window system api for cpu will return cpu idle time, kernal time and user time
     * from the system start up until the api is called
     * to calculate the cpu % at a second we need to know the cpu % of the previous second
     * and calculate with the delta
     * that is why we need to store the previous cpu time and update it after every call
     * */
    FILETIME m_prevIdle{};
    FILETIME m_prevKernal{};
    FILETIME m_prevUser{};
};

#endif // WINDOWMETRICPROVIDER_H
