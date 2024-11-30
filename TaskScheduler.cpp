
#include "TaskScheduler.h"
#include "TaskScheduler.h"
#include <QGraphicsView>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QSaveFile>
#include <QDataStream>
#include <QTimer>
#include <QCalendarWidget>
#include <QDebug>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QToolTip>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QDialog>
#include <algorithm>

TaskScheduler::TaskScheduler(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Priority Task Scheduler");
    setGeometry(100, 100, 800, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Set dark theme for the main window
    this->setStyleSheet("background-color: #2b2b2b; color: #ffffff;");

    // Style input fields
    QString inputStyle = "QLineEdit, QDateTimeEdit, QSpinBox, QTextEdit { "
                         "background-color: #3a3a3a; "
                         "color: #ffffff; "
                         "border: 1px solid #555555; "
                         "border-radius: 4px; "
                         "padding: 2px; }";

    // Style buttons
    QString buttonStyle = "QPushButton { "
                          "background-color: #4CAF50; "
                          "color: white; "
                          "border: none; "
                          "padding: 5px 10px; "
                          "border-radius: 4px; }"
                          "QPushButton:hover { background-color: #45a049; }";

    // Apply button style globally
    qApp->setStyleSheet(buttonStyle);

    QGroupBox *inputGroup = new QGroupBox("Add New Task");
    QGridLayout *inputLayout = new QGridLayout(inputGroup);

    nameInput = new QLineEdit();
    dueDateInput = new QDateTimeEdit(QDateTime::currentDateTime());
    dueDateInput->setCalendarPopup(true);
    QCalendarWidget *calendar = new QCalendarWidget();
    calendar->setGridVisible(true);
    dueDateInput->setCalendarWidget(calendar);
    priorityInput = new QLineEdit();
    descriptionInput = new QTextEdit();
    durationInput = new QSpinBox();
    durationInput->setRange(1, 10080); // 1 minute to 1 week (7 × 24 × 60)
    durationInput->setSuffix(" minutes");

    inputLayout->addWidget(new QLabel("Name:"), 0, 0);
    inputLayout->addWidget(nameInput, 0, 1);
    inputLayout->addWidget(new QLabel("Due Date:"), 1, 0);
    inputLayout->addWidget(dueDateInput, 1, 1);
    inputLayout->addWidget(new QLabel("Priority:"), 2, 0);
    inputLayout->addWidget(priorityInput, 2, 1);
    inputLayout->addWidget(new QLabel("Description:"), 3, 0);
    inputLayout->addWidget(descriptionInput, 3, 1);
    inputLayout->addWidget(new QLabel("Duration:"), 4, 0);
    inputLayout->addWidget(durationInput, 4, 1);

    QPushButton *addButton = new QPushButton("Add Task");
    inputLayout->addWidget(addButton, 5, 0, 1, 2);

    mainLayout->addWidget(inputGroup);

    QGroupBox *depGroup = new QGroupBox("Manage Dependencies");
    QGridLayout *depLayout = new QGridLayout(depGroup);

    taskCombo1 = new QComboBox();
    taskCombo2 = new QComboBox();

    depLayout->addWidget(new QLabel("Task:"), 0, 0);
    depLayout->addWidget(taskCombo1, 0, 1);
    depLayout->addWidget(new QLabel("Depends On:"), 1, 0);
    depLayout->addWidget(taskCombo2, 1, 1);

    QHBoxLayout *depButtonLayout = new QHBoxLayout();
    QPushButton *addDepButton = new QPushButton("Add Dependency");
    QPushButton *removeDepButton = new QPushButton("Remove Dependency");
    depButtonLayout->addWidget(addDepButton);
    depButtonLayout->addWidget(removeDepButton);

    depLayout->addLayout(depButtonLayout, 2, 0, 1, 2);

    addDepButton->setStyleSheet(buttonStyle);
    removeDepButton->setStyleSheet(buttonStyle);

    mainLayout->addWidget(depGroup);

    taskList = new QTreeWidget();
    taskList->setHeaderLabels({"Name", "Due Date", "Priority", "Duration", "Dependencies", "Description"});
    mainLayout->addWidget(taskList);

    taskList->installEventFilter(this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *scheduleButton = new QPushButton("Generate Schedule");
    QPushButton *saveButton = new QPushButton("Save Tasks");
    QPushButton *loadButton = new QPushButton("Load Tasks");
    QPushButton *visualizeButton = new QPushButton("Visualize Tasks");
    QPushButton *removeButton = new QPushButton("Remove Task");
    QPushButton *adjacencyListButton = new QPushButton("Show Adjacency List");
    QPushButton *sortButton = new QPushButton("Sort by Due Date");
    QPushButton *showGraphButton = new QPushButton("Show Priority Graph");
    QPushButton *exitButton = new QPushButton("Exit");

    buttonLayout->addWidget(scheduleButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(visualizeButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(adjacencyListButton);
    buttonLayout->addWidget(sortButton);
    buttonLayout->addWidget(showGraphButton);
    buttonLayout->addWidget(exitButton);

    mainLayout->addLayout(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, &TaskScheduler::addTaskFromUI);
    connect(addDepButton, &QPushButton::clicked, this, &TaskScheduler::addDependencyFromUI);
    connect(removeDepButton, &QPushButton::clicked, this, &TaskScheduler::removeDependency);
    connect(scheduleButton, &QPushButton::clicked, this, &TaskScheduler::generateSchedule);
    connect(saveButton, &QPushButton::clicked, this, &TaskScheduler::saveTasks);
    connect(loadButton, &QPushButton::clicked, this, &TaskScheduler::loadTasks);
    connect(visualizeButton, &QPushButton::clicked, this, &TaskScheduler::visualizeTasks);
    connect(removeButton, &QPushButton::clicked, this, &TaskScheduler::removeTask);
    connect(taskList, &QTreeWidget::itemSelectionChanged, this, &TaskScheduler::displayTaskDetails);
    connect(adjacencyListButton, &QPushButton::clicked, this, &TaskScheduler::printAdjacencyList);
    connect(sortButton, &QPushButton::clicked, this, &TaskScheduler::sortTasksByDueDate);
    connect(showGraphButton, &QPushButton::clicked, this, &TaskScheduler::showPriorityGraph);
    connect(exitButton, &QPushButton::clicked, this, &TaskScheduler::exitApplication);

    nameInput->setStyleSheet(inputStyle);
    dueDateInput->setStyleSheet(inputStyle);
    priorityInput->setStyleSheet(inputStyle);
    descriptionInput->setStyleSheet(inputStyle);
    durationInput->setStyleSheet(inputStyle);

    addButton->setStyleSheet(buttonStyle);
    scheduleButton->setStyleSheet(buttonStyle);
    saveButton->setStyleSheet(buttonStyle);
    loadButton->setStyleSheet(buttonStyle);
    visualizeButton->setStyleSheet(buttonStyle);
    removeButton->setStyleSheet(buttonStyle);
    adjacencyListButton->setStyleSheet(buttonStyle);
    sortButton->setStyleSheet(buttonStyle);
    showGraphButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    taskList->setAlternatingRowColors(true);
    taskList->setStyleSheet("QTreeWidget { "
                            "background-color: #1a1a1a; "
                            "color: #ffffff; "
                            "alternate-background-color: #2a2a2a; }"
                            "QTreeWidget::item:selected { "
                            "background-color: #3a3a3a; "
                            "color: #ffffff; }"
                            "QTreeWidget::item { "
                            "border-bottom: 1px solid #3a3a3a; "
                            "padding: 2px 0; }");

    QTimer *colorUpdateTimer = new QTimer(this);
    connect(colorUpdateTimer, &QTimer::timeout, this, &TaskScheduler::updateTaskColors);
    colorUpdateTimer->start(60000);
}

void TaskScheduler::addTaskFromUI() {
    addTask();
}

void TaskScheduler::addTask() {
    QString name = nameInput->text();
    QDateTime dueDate = dueDateInput->dateTime();
    int priority = priorityInput->text().toInt();
    QString description = descriptionInput->toPlainText();
    int duration = durationInput->value();

    Task *task = new Task{name, dueDate, 0, description, duration};
    calculateAndAssignPriority(task);
    tasks.push_back(task);

    QTreeWidgetItem *item = new QTreeWidgetItem(taskList);
    item->setText(0, name);
    item->setData(1, Qt::UserRole, dueDate);
    item->setText(1, dueDate.toString());
    item->setText(2, QString::number(task->priority));
    item->setText(3, formatDuration(duration));
    item->setText(5, description);

    QColor backgroundColor;
    QColor itemColor = Qt::white;

    if (priority >= 8) {
        itemColor = QColor(200, 0, 0);
    } else if (priority >= 4) {
        itemColor = QColor(200, 200, 0);
    } else {
        itemColor = QColor(0, 150, 0);
    }

    int priorityAdjustment = (10 - task->priority) * 10;
    backgroundColor = backgroundColor.darker(100 + priorityAdjustment);

    if (backgroundColor.lightness() > 128) {
        itemColor = Qt::black;
    }

    for (int i = 0; i < item->columnCount(); ++i) {
        item->setBackground(i, backgroundColor);
        item->setForeground(i, itemColor);
    }

    taskCombo1->addItem(name);
    taskCombo2->addItem(name);

    nameInput->clear();
    priorityInput->clear();
    descriptionInput->clear();
    durationInput->setValue(1);

    sortTasksByDueDate();
    updateTaskColors();
}
