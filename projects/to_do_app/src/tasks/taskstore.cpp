#include "taskstore.h"
#include <QUuid>
#include <algorithm>
#include <QDebug>

TaskStore::TaskStore(Dispatcher *dispatcher, QObject *parent)
    : QObject{parent}
{
    m_tasks = {
        {"1", "Learn C++", true},
        {"2", "Learn Qt", false},
        {"3", "Build a To-Do App", false}};
    connect(dispatcher, &Dispatcher::actionDispatched, this, &TaskStore::onActionDispatched);
}

void TaskStore::onActionDispatched(const Action &action)
{
    // std::visit + if constexpr: "switch" type-safe tại compile-time theo payload thực tế
    // đang nằm trong variant. Không cần enum so sánh thủ công, không cần ép kiểu.
    std::visit([this](auto &&payload)
               {
        using T = std::decay_t<decltype(payload)>;
        if constexpr (std::is_same_v<T, AddTaskPayload>) {
            handleAddTask(payload);
        } else if constexpr (std::is_same_v<T, ToggleCompletePayload>) {
            handleToggleComplete(payload);
        } else if constexpr (std::is_same_v<T, DeleteTaskPayload>) {
            handleDeleteTask(payload);
        } else if constexpr (std::is_same_v<T, SetFilterPayload>) {
            handleSetFilter(payload);
        } }, action.payload);
}

void TaskStore::handleAddTask(const AddTaskPayload &payload)
{
    Task newTask{QUuid::createUuid().toString(QUuid::WithoutBraces), payload.text, false};
    m_tasks.push_back(newTask);
    persist();
    emit taskAdded(m_tasks.size() - 1, newTask);
}

void TaskStore::handleToggleComplete(const ToggleCompletePayload &payload)
{
    int index = indexOfTaskId(payload.taskId);
    if (index == -1)
        return;

    m_tasks[index].completed = !m_tasks[index].completed;
    persist();

    emit taskToggled(index);
}

void TaskStore::handleDeleteTask(const DeleteTaskPayload &payload)
{
    int index = indexOfTaskId(payload.taskId);
    if (index == -1)
        return;

    m_tasks.erase(m_tasks.begin() + index);
    persist();
    emit taskRemoved(index);
}

void TaskStore::handleSetFilter(const SetFilterPayload &payload)
{
    qDebug() << "Changing filter to" << payload.filter;
    if (m_filter == payload.filter)
        return;

    m_filter = payload.filter;
    emit filterChanged(m_filter);
}

int TaskStore::indexOfTaskId(const QString &taskId) const
{
    for (size_t i = 0; i < m_tasks.size(); ++i)
    {
        if (m_tasks[i].id == taskId)
        {
            return static_cast<int>(i);
        }
    }

    return -1; // not found
}

void TaskStore::persist()
{
    // TODO: Implement task persistence (save to JSON)
}
