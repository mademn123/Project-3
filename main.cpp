#include "TaskScheduler.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TaskScheduler scheduler;
    scheduler.show();
    return app.exec();
}
