#include "taskfilterproxy.h"

TaskFilterProxy::TaskFilterProxy(TaskModel *taskModel, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->setSourceModel(taskModel);
    connect(taskModel, &TaskModel::filterChanged, this, [this](FilterType::Type filter)
            {
                m_currentFilter = filter;
                invalidate();
                emit filterChanged(); });
}

FilterType::Type TaskFilterProxy::currentFilter() const
{
    return m_currentFilter;
}

bool TaskFilterProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (m_currentFilter == FilterType::All)
        return true;

    const QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    const bool completed = sourceModel()->data(index, TaskModel::CompletedRole).toBool();

    if (m_currentFilter == FilterType::Active)
        return !completed;
    else if (m_currentFilter == FilterType::Completed)
        return completed;

    return true;
}
