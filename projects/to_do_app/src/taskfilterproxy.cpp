#include "taskfilterproxy.h"
#include "taskmodel.h"

TaskFilterProxy::TaskFilterProxy(QObject* parent) : QSortFilterProxyModel(parent) {}

int TaskFilterProxy::filter()
{
    return m_filter;
}

void TaskFilterProxy::setFilter(int filter)
{
    if (m_filter == filter) return;
    m_filter = filter;
    emit filterChanged();
    invalidate();
}

bool TaskFilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_filter == All) return true;

    const QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
    const bool done = sourceModel()->data(idx, TaskModel::DoneRole).toBool();

    if (m_filter == Active) return !done;
    if (m_filter == Completed) return done;

    return true;
}
