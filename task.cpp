#include "task.h"
#include <math.h>
#include <sstream>
#include <ctime>

Task::Task(QListWidget * parent) :
    QListWidgetItem(parent), project_name(""), description(""), archived(false), begin_time(0), due_day(0), due_month(0), due_hour(0), due_min(0),  hours_estimated(0), hours_worked(0), mins_worked(0), pre_task(NULL), custome_fields()
{
    return;
}

//Returns string of due date in form
// <due month> <due time> <due_hour> : <due_min>
std::string Task::getDueDate()
{
    std::stringstream ret_value;

    ret_value << due_month << " " << due_day << " " << due_hour << ":" << due_min;

    return ret_value.str();
}

QString Task::toString()
{
    std::stringstream out_stream;

    out_stream << text().toStdString() << "\n";
    out_stream << archived << "\n";
    out_stream << due_month << " " << due_day << " " << due_hour << " " << due_min << "\n";
    out_stream << description.toStdString() << "\n";
    out_stream << project_name.toStdString() << "\n";
    out_stream << hours_estimated << " " << mins_estimated << "\n";
    out_stream << hours_worked << " " << mins_worked << "\n";

    if(pre_task != NULL)
    {
        out_stream << pre_task->text().toStdString() << "\n";
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
    begin_time = std::clock();
}

void Task::stopTimer()
{
    std::clock_t stop_time = std::clock();

    unsigned int w_secs = double(stop_time - begin_time) / CLOCKS_PER_SEC;

    hours_worked = (w_secs % 360) / 60;

    hours_worked += w_secs / 360;
}
