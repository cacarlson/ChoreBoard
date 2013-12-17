#include "tasklist.h"
#include <iostream>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

TaskList::TaskList(QWidget *parent) :
    QListWidget(parent), num_active(0), num_archived(0), top_task(NULL)
{
    return;
}

bool TaskList::saveToFile()
{
    QFile file("database.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out_stream(&file);

    for(int ii = 0; ii < count(); ii++)
    {
        //Well....this is a little dangerous...
        //However, this will only be called on this list, which will only hold
        //items that are actually Task*....should probably write my own
        //takeItem function
        out_stream << ((Task*)item(ii))->toString();
    }

    return true;
}

void TaskList::loadFromFile()
{

}

void TaskList::markTaskTop()
{

}
