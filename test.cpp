#include "test.h"
#include "mainwindow.h"
#include <QApplication>
#include "task.h"
#include "tasklist.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::pair<std::string, bool> test;
void Tester::test_me(MainWindow &w)
{
    std::vector< test > tests;

    //A little TDD or just unit testing
    std::cout << "Create Task" << std::endl;
    Task* my_task = new Task();
    my_task->setText(0,"Charlie's Test Task");
    my_task->archived = true;
    my_task->description = "An example task to make sure that the toString function is working";
    my_task->project_name = "CS 471";
    my_task->setDueDate(1,1,1,1,1);
    my_task->addWorkTime(900);
    my_task->time_estimated = 10000;
    my_task->custome_fields["awesomenss"] = "somewhat";

    std::cout << my_task->toString().toStdString() << std::endl;
    bool test_res = my_task->toString().toStdString() == "Charlie's Test Task\n1\n01 1 1 1 1\nAn example task to make sure that the toString function is working\nCS 471\n900\n10000\n\n1\nawesomenss\nsomewhat\n";
    tests.push_back(test("Class Test One: ", test_res));

    //Check if added correctly
    w.m_taskList->task_list->addTopLevelItem(my_task);
    test_res = w.m_taskList->task_list->topLevelItem(0)->text(0) == my_task->text(0);
    test_res *= w.m_taskList->task_list->topLevelItemCount() == 1;
    tests.push_back(test("Add Item Test One: ", test_res));
    //Check save and load from file...
    w.m_taskList->saveToFile();
    w.m_taskList->loadFromFile();

    test_res = w.m_taskList->task_list->topLevelItemCount() == 2;
    tests.push_back(test("Save and Load Test One: ", test_res));

    //add a few more and check
    Task* a_task = new Task(*my_task);
    a_task->setText(0,"Task A");
    Task* b_task = new Task(*my_task);
    b_task->setText(0, "Task B");
    b_task->archived = false;

    w.m_taskList->task_list->addTopLevelItem(a_task);
    w.m_taskList->task_list->addTopLevelItem(b_task);

    test_res = w.m_taskList->task_list->topLevelItemCount() == 4;
    tests.push_back(test("Add Task Two: ", test_res));

    //Check save and load from file...again
    w.m_taskList->saveToFile();
    w.m_taskList->loadFromFile();

    test_res = w.m_taskList->task_list->topLevelItemCount() == 8;
    tests.push_back(test("Save and Load Test Two: ", test_res));

    //clear all tasks

    w.m_taskList->task_list->clear();

    test_res = test_res = w.m_taskList->task_list->topLevelItemCount() == 0;
    tests.push_back(test("Remove Tasks all: ",test_res));

    //stress on objects
    for(int ii = 0; ii < 1000; ii++)
    {
        Task* task = new Task();
        task->setText(0,QString(QString::number(ii)+" task"));
        w.m_taskList->task_list->addTopLevelItem(task);
    }

    test_res = test_res = w.m_taskList->task_list->topLevelItemCount() == 1000;
    tests.push_back(test("Add Tasks: ",test_res));

    w.m_taskList->saveToFile();

    w.m_taskList->task_list->clear();

    w.m_taskList->loadFromFile();

    test_res = test_res = w.m_taskList->task_list->topLevelItemCount() == 1000;
    tests.push_back(test("Add Load and Save 1000 tasks: ",test_res));

    for(auto ii : tests)
    {
        std::cout << ii.first;
        if(ii.second == true)
            std::cout << "Passed!" << std::endl;
        else
        {
            std::cout << "FAILED!!!!!" << std::endl;
        }
    }

}
