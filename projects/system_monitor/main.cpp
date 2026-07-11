/**
 * @file      %{Cpp:License:FileName}
 * @author    diendanx
 * @date      2026-7-11
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("system_monitor", "Main");

    return QGuiApplication::exec();
}
