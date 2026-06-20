#pragma once

#include <QObject>
#include <QSortFilterProxyModel>
#include <QQmlEngine>
#include "FilterType.h"
#include "taskmodel.h"

class TaskFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("This is a proxy model, not meant to be created directly in QML")
    // type - reader - writer - notifier
    Q_PROPERTY(FilterType::Type currentFilter READ currentFilter NOTIFY filterChanged)
public:
    explicit TaskFilterProxy(TaskModel *taskModel, QObject *parent = nullptr);

    FilterType::Type currentFilter() const;

signals:
    void filterChanged();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    FilterType::Type m_currentFilter{FilterType::All};
};
