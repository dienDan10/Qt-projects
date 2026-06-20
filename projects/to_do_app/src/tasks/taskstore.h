#pragma once

#include <QObject>
#include <QString>
#include <QCoreApplication>
#include "../flux/dispatcher.h"
#include "FilterType.h"
#include "task.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class TaskStore : public QObject
{
    Q_OBJECT

public:
    explicit TaskStore(Dispatcher *dispatcher, QObject *parent = nullptr);

    std::vector<Task> &tasks() { return m_tasks; }
    FilterType::Type currentFilter() const { return m_filter; }

signals:
    void taskAdded(int index, const Task &task);
    void taskRemoved(int index);
    void taskToggled(int index);
    void filterChanged(FilterType::Type filter);

private slots:
    void onActionDispatched(const Action &action);

private:
    void handleAddTask(const AddTaskPayload &payload);
    void handleToggleComplete(const ToggleCompletePayload &payload);
    void handleDeleteTask(const DeleteTaskPayload &payload);
    void handleSetFilter(const SetFilterPayload &payload);

    int indexOfTaskId(const QString &taskId) const;

    // TODO: gọi vào TaskStorage (load/save JSON)
    void load();
    void persist();

private:
    std::vector<Task> m_tasks;
    FilterType::Type m_filter = FilterType::All;
    QFile *m_storage = nullptr;
};
