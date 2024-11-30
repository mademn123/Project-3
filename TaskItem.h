
#ifndef TASKSCHEDULERTEMP_TASKITEM_H
#define TASKSCHEDULERTEMP_TASKITEM_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include "Task.h"

class TaskItem : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    TaskItem(Task* task, QGraphicsItem* parent = nullptr);

    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void addEdge(TaskItem* endItem);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void updateEdges();

    Task* task;
    QList<TaskItem*> edges;
};

#endif // TASKITEM_H
