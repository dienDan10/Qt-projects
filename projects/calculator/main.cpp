#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSharedPointer>
#include "calculatorengine.h"
#include "flux/dispatcher.h"
#include "src/calculatoraction.h"

void registerMetaData() {
    auto calcEngine = QSharedPointer<CalculatorEngine>::create();
    Dispatcher::instance().registerStore<CalculatorAction>(calcEngine);
    qmlRegisterSingletonInstance<CalculatorEngine>("calculator", 1, 0, "CalculatorEngine", calcEngine.get());
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // register qml types
    //registerMetaData();

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("calculator", "Main");

    return QGuiApplication::exec();
}
