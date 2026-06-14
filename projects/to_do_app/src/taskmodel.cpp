#include "taskmodel.h"
#include <QUuid>

TaskModel::TaskModel(QObject* parent) : QAbstractListModel(parent) {
    task_list.append(Task {"task 1", "Do something fun", true});
    task_list.append(Task {"task 2", "Do something fun", true});
    task_list.append(Task {"task 3", "Do something fun", true});
    task_list.append(Task {"task 4", "Do something fun", true});
    task_list.append(Task {"task 5", "Do something fun", true});
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return task_list.size();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= task_list.length())
        return {};

    const Task& task = task_list.at(index.row());
    switch (role) {
        case IdRole: return task.id;
        case TitleRole: return task.title;
        case DoneRole: return task.done;
    }

    return {};
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {TitleRole, "title"},
        {DoneRole, "done"}
    };
}

void TaskModel::addTask(const QString &title)
{
    beginInsertRows({}, task_list.length(), task_list.length());
    task_list.append(Task {
        QUuid::createUuid().toString(QUuid::WithoutBraces),
        title,
        false
    });
    endInsertRows();
}

void TaskModel::removeTask(int row)
{
    if (row < 0 || row >= task_list.size()) return;
    beginRemoveRows({}, row, row);
    task_list.removeAt(row);
    endRemoveRows();
}

void TaskModel::setDone(int row)
{
    if (row < 0 || row >= task_list.size()) return;
    task_list[row].done = !task_list[row].done;
    const QModelIndex idx = index(row);
    emit dataChanged(idx, idx, {DoneRole});
}
