#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>
#include "taskstore.h"
#include "FilterType.h"
class TaskModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("TaskModel is a singleton and cannot be created in QML")
public:
    enum Roles
    {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        CompletedRole
    };

    explicit TaskModel(TaskStore *taskStore, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    FilterType::Type currentFilter() const;

signals:
    void filterChanged(FilterType::Type filter);

private:
    TaskStore *m_taskStore;
};
