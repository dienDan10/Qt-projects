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
#include "itemviewmodel.h"
#include "actionprovider.h"

void registerQmlType() {
    ItemViewModel* viewModel = new ItemViewModel();
    qmlRegisterSingletonInstance<ItemViewModel>("fileviewer.singleton", 1, 0, "ItemModel",viewModel);

    ActionProvider* actionProvider = new ActionProvider();
    qmlRegisterSingletonInstance<ActionProvider>("fileviewer.singleton", 1, 0, "ActionProvider",actionProvider);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    registerQmlType();

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("file_viewer", "Main");

    return QGuiApplication::exec();
}
