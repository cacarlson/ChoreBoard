//ChoreBoard
//By Charlie Carlson

#include "mainwindow.h"
#include <QApplication>
#include "task.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //A little TDD or just unit testing
    Task::Task my_task;
    my_task.task_name = "Charlie's Test Task";
    my_task.archived = true;
    my_task.description = "An example task to make sure that the toString function is working";
    my_task.project_name = "CS 471";
    my_task.hours_estimated = 2;
    my_task.mins_estimated = 0;
    my_task.hours_worked = 0;
    my_task.mins_worked = 30;
    my_task.custome_fields["awesomenss"] = "somewhat";

    std::cout << my_task.toString() << std::endl;

    return a.exec();
}
