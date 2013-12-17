//ChoreBoard
//By Charlie Carlson

#include "mainwindow.h"
#include <QApplication>
#include "task.h"
#include "tasklist.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //A little TDD or just unit testing
    Task* my_task = new Task();
    my_task->setText("Charlie's Test Task");
    my_task->archived = true;
    my_task->description = "An example task to make sure that the toString function is working";
    my_task->project_name = "CS 471";
    my_task->hours_estimated = 2;
    my_task->mins_estimated = 0;
    my_task->hours_worked = 0;
    my_task->mins_worked = 30;
    my_task->custome_fields["awesomenss"] = "somewhat";

    std::cout << my_task->toString().toStdString() << std::endl;

    TaskList::TaskList my_list;

    my_list.addItem(my_task);

    //check saving list of one
    my_list.saveToFile();

    //add a few more and check
    Task* a_task = new Task(*my_task);
    a_task->setText("not that task");
    Task* b_task = new Task(*my_task);
    b_task->setText( "different yet again");

    my_list.addItem(a_task);
    my_list.addItem(b_task);

    my_list.saveToFile();

    return a.exec();
}
