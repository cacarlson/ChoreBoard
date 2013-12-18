#include "tasklist.h"
#include <iostream>
#include <sstream>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include "Task.h"

TaskList::TaskList(QTreeWidget* m_tree) :
    num_active(0), num_archived(0), top_task(NULL)
{
    task_list = m_tree;
    return;
}

QString TaskList::toString()
{
    std::stringstream out_stream;

    QTreeWidgetItemIterator it(task_list);
    while (*it) {
        out_stream << ((Task*)*it)->toString().toStdString();
        ++it;
    }

    return QString::fromStdString(out_stream.str());
}

bool TaskList::saveToFile()
{
    QFile file("database.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out_stream(&file);

    out_stream << toString();

    file.close();
    return true;
}

void TaskList::loadFromFile()
{
    QFile file("database.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_stream(&file);

    while(!in_stream.atEnd())
    {
        Task* temp_task = new Task();
        temp_task->setText(0,in_stream.readLine());

        int temp_bucket = 0;
        in_stream >> temp_bucket;
        temp_task->archived = (bool)temp_bucket;

        if(temp_task->archived)
            temp_task->colorRow(Qt::cyan, 2);
        else
           temp_task->colorRow(Qt::transparent, 2);

        unsigned int due[5];
        in_stream >> due[0];
        in_stream >> due[1];
        in_stream >> due[2];
        in_stream >> due[3];
        in_stream >> due[4];

        temp_task->setDueDate(due[0], due[1], due[2], due[3], due[4]);
        in_stream.readLine();

        temp_task->description = in_stream.readLine();
        temp_task->project_name = in_stream.readLine();

        in_stream >> temp_task->time_worked;
        temp_task->addWorkTime(0);

        in_stream >> temp_task->time_estimated;

        in_stream.readLine();
        QString task_name("");

        if(task_list->findItems(task_name,Qt::MatchExactly,0).size() > 0)
        {
            temp_task->pre_task = (Task*)(task_list->findItems(task_name,Qt::MatchExactly,0).first());
        }

        in_stream >> temp_bucket;
        in_stream.readLine();

        for(int hh = 0; hh < temp_bucket; hh++)
        {
            temp_task->custome_fields[in_stream.readLine().toStdString()] = in_stream.readLine().toStdString();
        }

        task_list->addTopLevelItem(temp_task);
    }

    task_list->resizeColumnToContents(0);
    task_list->resizeColumnToContents(1);
    task_list->resizeColumnToContents(2);
    file.close();
}

void TaskList::markTaskTop()
{
    Task* old_task = top_task;

    top_task = (Task*)task_list->currentItem();

    if(top_task != NULL)
        top_task->colorRow(Qt::red);

    if(old_task != NULL)
    {
        if(old_task->archived)
            old_task->colorRow(Qt::cyan);
        else
            old_task->colorRow(Qt::transparent);
    }
}
