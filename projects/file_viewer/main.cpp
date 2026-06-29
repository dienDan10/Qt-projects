/**
 * @file      main.cpp
 * @author    diendanx
 * @date      2026-6-29
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
    engine.loadFromModule("file_viewer", "Main");

    return QGuiApplication::exec();
}
