#ifndef TASK_H
#define TASK_H
#include <QString>

struct Task
{
    QString id;
    QString text;
    bool completed = false;
};

#endif // TASK_H