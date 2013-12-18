#include "task.h"
#include<QTableWidget>
#include <math.h>
#include <sstream>
#include <ctime>
#include <iostream>

Task::Task() :
    QTreeWidgetItem(), project_name(""), description(""), archived(false), due_date(), work_done(0,0,0,0), time_worked(0), time_estimated(0), pre_task(NULL), custome_fields()
{
    setText(0, "");
    setText(1, "01/01/01 00:00");
    setFlags(flags() & ~Qt::ItemIsDropEnabled);
    return;
}

void Task::setDueDate(unsigned int d_year, unsigned int d_month, unsigned int d_day, unsigned int d_hour, unsigned int d_min)
{
    due_date.setTime(QTime(d_hour, d_min));
    due_date.setDate(QDate(d_year, d_month, d_day));

    setText(1, due_date.toString("MM/dd/yy"));
}

void Task::addWorkTime(unsigned int secs)
{
    time_worked += secs;
}

QString Task::toString()
{
    std::stringstream out_stream;

    out_stream << text(0).toStdString() << "\n";
    out_stream << archived << "\n";
    out_stream << due_date.toString("yy M d h m").toStdString() + "\n";
    out_stream << description.toStdString() << "\n";
    out_stream << project_name.toStdString() << "\n";
    out_stream << time_worked << "\n";
    out_stream << time_estimated << "\n";

    if(pre_task != NULL)
    {
        out_stream << pre_task->text(0).toStdString() << "\n";
    }
    else
    {
        out_stream << "\n";
    }

    out_stream << custome_fields.size() << "\n";

    for(auto iter = custome_fields.begin(); iter != custome_fields.end(); iter++)
    {
        out_stream << iter->first << "\n" << iter->second << "\n";
    }

    return QString::fromStdString(out_stream.str());;
}

void Task::startTime()
{
    work_done.start();
}

void Task::stopTimer()
{
   time_worked += work_done.elapsed();
}
