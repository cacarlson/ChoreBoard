//ChoreBoard
//By Charlie Carlson

#include "mainwindow.h"
#include <QApplication>
#include "task.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Task::Task my_task;

    return a.exec();
}
