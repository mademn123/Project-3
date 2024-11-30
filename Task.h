#ifndef TASKSCHEDULERTEMP_TASK_H
#define TASKSCHEDULERTEMP_TASK_H


#include <QString>
#include <QDateTime>
#include <vector>

struct Task {
    QString name;
    QDateTime dueDate;
    int priority;
    QString description;
    int duration; // in minutes
    std::vector<Task*> dependencies;
    std::vector<Task*> adjacentTasks;
};

#endif // TASK_H
