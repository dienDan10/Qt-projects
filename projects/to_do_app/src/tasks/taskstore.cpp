#include "taskstore.h"
#include <QUuid>
#include <QDebug>

TaskStore::TaskStore(Dispatcher *dispatcher, QObject *parent)
    : QObject{parent}
{
    m_storage = new QFile(QCoreApplication::applicationDirPath() + "/data/tasks.json", this);
    qDebug() << QCoreApplication::applicationDirPath() + "/data/tasks.json";
    this->load();
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

void TaskStore::load()
{
    if (!m_storage->open(QIODevice::ReadOnly))
    {
        qWarning() << "Could not open tasks.json for reading:" << m_storage->errorString();
        return;
    }

    QByteArray data = m_storage->readAll();
    if (data.isEmpty())
    {
        qDebug() << "No existing tasks found.";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject())
    {
        qWarning() << "Invalid JSON in tasks.json";
        return;
    }

    QJsonObject rootObj = doc.object();
    QJsonArray tasksArray = rootObj.value("tasks").toArray();

    for (const QJsonValue &taskValue : tasksArray)
    {
        if (!taskValue.isObject())
            continue;

        QJsonObject taskObj = taskValue.toObject();
        Task task;
        task.id = taskObj.value("id").toString();
        task.text = taskObj.value("text").toString();
        task.completed = taskObj.value("completed").toBool();

        m_tasks.push_back(task);
    }

    m_storage->close();
}

void TaskStore::persist()
{
    if (!m_storage->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qWarning() << "Could not open tasks.json for reading:" << m_storage->errorString();
        return;
    }

    QJsonObject tasks;
    QJsonArray arr;
    for (const Task &task : m_tasks)
    {
        QJsonObject taskObj;
        taskObj.insert("id", task.id);
        taskObj.insert("text", task.text);
        taskObj.insert("completed", task.completed);

        arr.push_back(taskObj);
    }

    tasks.insert("tasks", arr);

    m_storage->write(QJsonDocument(tasks).toJson(QJsonDocument::Indented));
    m_storage->close();
}
