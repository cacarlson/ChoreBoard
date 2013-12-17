#include "tasklist.h"
#include <iostream>
#include <sstream>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include "Task.h"

TaskList::TaskList(QWidget *parent) :
    QListWidget(parent), num_active(0), num_archived(0), top_task(NULL)
{
    return;
}

QString TaskList::toString()
{
    std::stringstream out_stream;
    for(int ii = 0; ii < count(); ii++)
    {
        //Well....this is a little dangerous...
        //However, this will only be called on this list, which will only hold
        //items that are actually Task*....should probably write my own
        //takeItem function
        out_stream << ((Task*)item(ii))->toString().toStdString();
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
        temp_task->setText( in_stream.readLine());

        int temp_bucket = 0;
        in_stream >> temp_bucket;
        temp_task->archived = (bool)temp_bucket;

        in_stream >> temp_task->due_month;
        in_stream >> temp_task->due_day;
        in_stream >> temp_task->due_hour;
        in_stream >> temp_task->due_min;
        in_stream.readLine();

        temp_task->description = in_stream.readLine();
        temp_task->project_name = in_stream.readLine();

        in_stream >> temp_task->hours_estimated;
        in_stream >> temp_task->mins_estimated;

        in_stream >> temp_task->hours_worked;
        in_stream >> temp_task->mins_worked;

        in_stream.readLine();
        QString task_name("");

        for(int jj = 0; jj < count(); jj++)
        {
            if(!QString::compare(task_name, item(jj)->text(),Qt::CaseSensitive))
            {
                temp_task->pre_task = (Task*)item(jj);
                break;
            }
        }

        in_stream >> temp_bucket;
        in_stream.readLine();
        for(int hh = 0; hh < temp_bucket; hh++)
        {
            temp_task->custome_fields[in_stream.readLine().toStdString()] = in_stream.readLine().toStdString();
        }

        addItem(temp_task);
    }

    file.close();
}

void TaskList::markTaskTop()
{

}
