/**
 * @file      windowmetricprovider.cpp
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "windowmetricprovider.h"
#include "windows.h"

WindowMetricProvider::WindowMetricProvider() {}

bool WindowMetricProvider::initialize()
{
    /*
     * Get the sample the first time this provider is contructed, so that
     * with each call to system api after this point, we have data to calculate
     * the cpu %
     * */

    FILETIME idle, kernal, user;
    if (!GetSystemTimes(&idle, &kernal, &user)) {
        return false;
    }

    m_prevIdle = idle;
    m_prevKernal = kernal;
    m_prevUser = user;
    return true;
}

CpuMetric WindowMetricProvider::readCpuMetric()
{
    FILETIME idle, kernal, user;
    CpuMetric cpuMetric;
    if (!GetSystemTimes(&idle, &kernal, &user)) {
        return cpuMetric;
    }

    // convert FILETIME to int 64
    uint64_t idleNow = FileTimeToInt64(idle);
    uint64_t kernalNow = FileTimeToInt64(kernal);
    uint64_t userNow = FileTimeToInt64(user);
    uint64_t prevIdle = FileTimeToInt64(m_prevIdle);
    uint64_t prevKernal = FileTimeToInt64(m_prevKernal);
    uint64_t prevUser = FileTimeToInt64(m_prevUser);

    // calculate delta
    uint64_t deltaIdle = idleNow - prevIdle;
    uint64_t deltaTotal = (kernalNow + userNow) - (prevKernal + prevUser);

    // update prev value
    m_prevIdle = idle;
    m_prevKernal = kernal;
    m_prevUser = user;

    // calculate cpu %
    if (deltaTotal == 0.0) return cpuMetric;   // in case we call too fast, but rarely happend
    double usage = (1.0 - static_cast<double>(deltaIdle) / static_cast<double>(deltaTotal)) * 100;
    cpuMetric.usePercentage = usage < 0.0 ? 0.0 : (usage > 100.0) ? 100.0 : usage;
    /*
     * deltaIdle <= deltaTotal
     * so deltaIdle can be equal deltaTotal (i don't know if this can happend???)
     * in that case usage will be 0
     * we should clamp the value for safety, window can be weird
     * */
    return cpuMetric;
}

RamMetric WindowMetricProvider::readRamMetric()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    RamMetric ramMetric;

    if (!GlobalMemoryStatusEx(&memInfo)) {
        return RamMetric();
    }
    /*
    memInfo.ullTotalPhys       // tổng RAM vật lý
    memInfo.ullAvailPhys       // RAM vật lý còn trống
    memInfo.ullTotalPageFile   // tổng page file (RAM + swap)
    memInfo.ullAvailPageFile   // page file còn trống
    memInfo.dwMemoryLoad       // % RAM đang dùng (0-100), Windows tính sẵn
    đơn vị trả ra ở đây sẽ là byte
    */

    // all value will be return as bytes
    ramMetric.totalRam = static_cast<double>(memInfo.ullTotalPhys);
    ramMetric.availableRam = static_cast<double>(memInfo.ullAvailPhys);
    ramMetric.usePercentage = static_cast<double>(memInfo.dwMemoryLoad);
    return ramMetric;
}


double WindowMetricProvider::getTotalRam()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (!GlobalMemoryStatusEx(&memInfo)) {
        return -1;
    }

    // here we return ram as bytes
    return static_cast<double>(memInfo.ullTotalPhys);
}

uint64_t WindowMetricProvider::FileTimeToInt64(const FILETIME &ft)
{
    ULARGE_INTEGER u;
    u.LowPart = ft.dwLowDateTime;
    u.HighPart = ft.dwHighDateTime;
    return u.QuadPart;
}
