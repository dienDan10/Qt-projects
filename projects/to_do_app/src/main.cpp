#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tasks/taskmodel.h"
#include "tasks/taskstore.h"
#include "flux/dispatcher.h"
#include "tasks/taskfilterproxy.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []()
        { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    Dispatcher dispatcher;
    TaskStore taskStore(&dispatcher);
    TaskModel taskModel(&taskStore);
    TaskFilterProxy taskFilterProxy(&taskModel);

    engine.setInitialProperties({{"taskModel", QVariant::fromValue(&taskFilterProxy)},
                                 {"dispatcher", QVariant::fromValue(&dispatcher)}});

    engine.loadFromModule("to_do_app", "Main");

    return QCoreApplication::exec();
}
