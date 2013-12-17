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
    my_task->setText(0,"Charlie's Test Task");
    my_task->archived = true;
    my_task->description = "An example task to make sure that the toString function is working";
    my_task->project_name = "CS 471";
    my_task->hours_estimated = 2;
    my_task->mins_estimated = 0;
    my_task->hours_worked = 0;
    my_task->mins_worked = 30;
    my_task->custome_fields["awesomenss"] = "somewhat";

    std::cout << my_task->toString().toStdString() << std::endl;

    w.m_taskList->task_list->addTopLevelItem(my_task);

    //check saving list of one
    w.m_taskList->saveToFile();

    std::cout << " file saved" << std::endl;
    //add a few more and check
    Task* a_task = new Task(*my_task);
    a_task->setText(0,"not that task");
    Task* b_task = new Task(*my_task);
    b_task->setText(0, "different yet again");

    std::cout << "It is going to add some tasks" << std::endl;

     w.m_taskList->task_list->addTopLevelItem(a_task);
     w.m_taskList->task_list->addTopLevelItem(b_task);

    std::cout << "It is going to save" << std::endl;
     w.m_taskList->saveToFile();

     QTreeWidget* m_tree = new QTreeWidget;
     TaskList* other_list = new TaskList(NULL, m_tree);
    other_list->loadFromFile();

    std::cout << "check if files where loaded and printed correctly...also saved I guess";
    std::cout << other_list->toString().toStdString() << std::endl;

    return a.exec();
}
