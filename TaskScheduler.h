//
// Created by aarit on 11/30/2024.
//

#ifndef TASKSCHEDULERTEMP_TASKSCHEDULER_H
#define TASKSCHEDULERTEMP_TASKSCHEDULER_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QComboBox>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTimer>
#include "Task.h"
#include "TaskItem.h"

class TaskScheduler : public QMainWindow {
    Q_OBJECT

public:
    TaskScheduler(QWidget* parent = nullptr);
    void addTask(Task* task);
    void addDependency(Task* task, Task* dependency);
    void generateSchedule();
    void visualizeTasks();
    void saveTasks();
    void loadTasks();
    void showPriorityGraph();

public slots:
            void addTaskFromUI();
    void addDependencyFromUI();
    void removeTask();
    void updateTaskColors();
    void exitApplication();
    void removeDependency();
    void displayTaskDetails();
    void sortTasksByDueDate();
    void sortTasksByPriority();

private:
    QLineEdit* nameInput;
    QDateTimeEdit* dueDateInput;
    QLineEdit* priorityInput;
    QTextEdit* descriptionInput;
    QSpinBox* durationInput;
    QTreeWidget* taskList;
    QComboBox* taskCombo1;
    QComboBox* taskCombo2;
    std::vector<Task*> tasks;
    QGraphicsScene* scene;
    QMainWindow* priorityGraphWindow;

    QString formatDuration(int minutes);
    Task* findTaskByName(const QString& name);
    void calculateAndAssignPriority(Task* task);
    void updateDependenciesDisplay();
    void printAdjacencyList();
    bool eventFilter(QObject* obj, QEvent* event) override;
    bool isCircularDependency(Task* task, Task* newDep);
    void addEdge(Task* task1, Task* task2);
    void removeEdge(Task* task1, Task* task2);
    void handleBarHover(bool status, int index, QBarSet* barSet);
};

#endif // TASKSCHEDULER_H
