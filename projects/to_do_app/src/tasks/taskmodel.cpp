#include "taskmodel.h"

TaskModel::TaskModel(TaskStore *taskStore, QObject *parent)
    : QAbstractListModel{parent}, m_taskStore{taskStore}
{
    // add
    connect(m_taskStore, &TaskStore::taskAdded, this, [this](int index, const Task &task)
            {
        beginInsertRows(QModelIndex(), index, index);
        endInsertRows(); });

    // remove
    connect(m_taskStore, &TaskStore::taskRemoved, this, [this](int index)
            {
        beginRemoveRows(QModelIndex(), index, index);
        endRemoveRows(); });

    // toggle
    connect(m_taskStore, &TaskStore::taskToggled, this, [this](int index)
            {
        const auto modelIndex = this->index(index);
        emit dataChanged(modelIndex, modelIndex, {CompletedRole}); });

    // filter
    connect(m_taskStore, &TaskStore::filterChanged, this, [this](FilterType::Type filter)
            { emit filterChanged(filter); });
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(m_taskStore->tasks().size());
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    int idx = index.row();
    Task task = m_taskStore->tasks().at(idx);

    switch (role)
    {
    case IdRole:
        return task.id;
    case TitleRole:
        return task.text;
    case CompletedRole:
        return task.completed;
    }

    return {};
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {TitleRole, "title"},
        {CompletedRole, "completed"}};
}

FilterType::Type TaskModel::currentFilter() const
{
    return m_taskStore->currentFilter();
}
