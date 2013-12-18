#ifndef TASK_H
#define TASK_H

#include <QListWidgetItem>
#include <ctime>
#include <memory>
#include<QTreeWidgetItem>

class Task : public QTreeWidgetItem
{

public:
    explicit Task();

    std::string getDueDate();
    void setDueDate(unsigned int d_month = 1, unsigned int d_day = 1, unsigned int d_hour = 0, unsigned int d_min = 0);

    QString toString();
    void startTime();
    void stopTimer();

    QString project_name;
    QString description;
    QString due_date;

    bool archived;

    std::clock_t begin_time;

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
