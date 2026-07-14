/**
 * @file      metricproviderfactory.h
 * @author    diendanx
 * @date      2026-7-14
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef METRICPROVIDERFACTORY_H
#define METRICPROVIDERFACTORY_H

#include "ISystemMetricProvider.h"
#include <memory>

#if defined(Q_OS_WIN)
#include "windowmetricprovider.h"
#elif defined(Q_OS_LINUX)
#include "linuxmetricprovider.h"
#endif

inline std::unique_ptr<ISystemMetricProvider> createSystemMetricProvider() {
#if defined(Q_OS_WIN)
    return std::make_unique<WindowMetricProvider>();
#elif defined(Q_OS_LINUX)
    return std::make_unique<LinuxMetricProvider>();
#else
    #error "Unsupported platform"
#endif
}

#endif // METRICPROVIDERFACTORY_H
