#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>
#include "task.h"

class TaskModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        DoneRole
    };

    explicit TaskModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // business logic
    Q_INVOKABLE void addTask(const QString& title);
    Q_INVOKABLE void removeTask(int row);
    Q_INVOKABLE void setDone(int row);

private:
    QList<Task> task_list;
};

#endif // TASKMODEL_H
