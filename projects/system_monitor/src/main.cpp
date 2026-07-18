/**
 * @file      %{Cpp:License:FileName}
 * @author    diendanx
 * @date      2026-7-11
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QSharedPointer>
#include <QDebug>
#include "controller/monitorcontroller.h"

void setAppFont(const QGuiApplication& app) {
    QFontDatabase::addApplicationFont(
        ":/assets/fonts/Inter_18pt-Regular.ttf");
    QFontDatabase::addApplicationFont(
        ":/assets/fonts/Inter_18pt-Medium.ttf");
    QFontDatabase::addApplicationFont(
        ":/assets/fonts/Inter_18pt-SemiBold.ttf");
    QFontDatabase::addApplicationFont(
        ":/assets/fonts/Inter_18pt-Bold.ttf");

    app.setFont(QFont("Inter"));
}

void registerQmlTypes(QApplication& app) {
    auto monitor = new MonitorController(&app);
    QObject::connect(monitor, &MonitorController::initializeFail, &app, [&app, &monitor]() {
        qCritical() << "Failed to initilize monitor, quit app.";
        app.quit();
    });
    monitor->initialize();
    qmlRegisterSingletonInstance("monitor.singleton", 1, 0, "Monitor", monitor);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // set font
    setAppFont(app);
    registerQmlTypes(app);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("system_monitor", "Main");

    return app.exec();
}
