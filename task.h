#ifndef TASK_H
#define TASK_H

#include <QListWidgetItem>

class Task : public QListWidgetItem
{
public:
    explicit Task(QListWidget *parent = 0);

    std::string getDueDate();
    void setDueDate(unsigned int d_month = 1, unsigned int d_day = 1, unsigned int d_hour = 0, unsigned int d_min = 0);
    std::string toString();
    void startTime();
    void stopTimer();

    std::string task_name;
    std::string description;

    bool archived;

    unsigned int due_day;
    unsigned int due_month;
    unsigned int due_hour;
    unsigned int due_min;


    unsigned int hours_estimated;
    unsigned int mins_estimated;
    unsigned int hours_worked;
    unsigned int mins_worked;

    Task* pre_task;
    std::map<std::string, std::string> custome_fields;

};

#endif // TASK_H
