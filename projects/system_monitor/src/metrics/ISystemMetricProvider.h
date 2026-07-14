/**
 * @file      ISystemMetricProvider.h
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef ISYSTEMMETRICPROVIDER_H
#define ISYSTEMMETRICPROVIDER_H

class ISystemMetricProvider {
public:
    virtual ~ISystemMetricProvider() = default;
    virtual bool initialize() = 0;
    virtual double readCpuUsage() = 0;
    virtual double readRamUsage() = 0;
};

#endif // ISYSTEMMETRICPROVIDER_H
