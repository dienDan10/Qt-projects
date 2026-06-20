#include "dispatcher.h"

Dispatcher::Dispatcher(QObject *parent)
    : QObject{parent}
{
}

void Dispatcher::addTask(const QString &title)
{
    dispatch(Action{ActionType::AddTask, AddTaskPayload{title}});
}

void Dispatcher::deleteTask(const QString &taskId)
{
    dispatch(Action{ActionType::DeleteTask, DeleteTaskPayload{taskId}});
}

void Dispatcher::toggleComplete(const QString &taskId)
{
    dispatch(Action{ActionType::ToggleComplete, ToggleCompletePayload{taskId}});
}

void Dispatcher::setFilter(const FilterType::Type filter)
{
    dispatch(Action{ActionType::SetFilter, SetFilterPayload{filter}});
}

void Dispatcher::dispatch(Action action)
{
    emit actionDispatched(action);
}
