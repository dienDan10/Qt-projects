#pragma once

#include <QObject>
#include <QQmlEngine>
#include "../tasks/FilterType.h"
#include "action.h"
class Dispatcher: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Dispatcher is a singleton and cannot be created in QML")
public:
    explicit Dispatcher(QObject *parent = nullptr);

    // actions creator
    Q_INVOKABLE void addTask(const QString& title);
    Q_INVOKABLE void deleteTask(const QString& taskId);
    Q_INVOKABLE void toggleComplete(const QString& taskId);
    Q_INVOKABLE void setFilter(const FilterType::Type filter);

signals:
    void actionDispatched(const Action& action);

private:
    void dispatch(Action action);
};
