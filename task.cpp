#include "task.h"
#include <math.h>
#include <sstream>

Task::Task(QListWidget * parent) :
    QListWidgetItem(parent), task_name(""), archived(false), due_day(0), due_month(0), due_hour(0), due_min(0), description(""), hours_estimated(0), hours_worked(0), mins_worked(0), pre_task(NULL), custome_fields()
{
}

//Returns string of due date in form
// <due month> <due time> <due_hour> : <due_min>
std::string Task::getDueDate()
{
    std::stringstream ret_value;

    ret_value << due_month << " " << due_day << " " << due_hour << ":" << due_min;

    return ret_value.str();
}

std::string Task::toString()
{
    return " ";
}

void Task::startTime()
{

}

void Task::stopTimer()
{

}
