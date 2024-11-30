#include "Task.h"
#include "Task.h"

Task::Task(const QString &name, const QDateTime &dueDate, int priority, const QString &description, int duration)
        : name(name), dueDate(dueDate), priority(priority), description(description), duration(duration) {
}

void Task::addDependency(Task *dependency) {
    dependencies.push_back(dependency);
}

void Task::removeDependency(Task *dependency) {
    dependencies.erase(std::remove(dependencies.begin(), dependencies.end(), dependency), dependencies.end());
}

void Task::addAdjacentTask(Task *task) {
    adjacentTasks.push_back(task);
}

void Task::removeAdjacentTask(Task *task) {
    adjacentTasks.erase(std::remove(adjacentTasks.begin(), adjacentTasks.end(), task), adjacentTasks.end());
}
