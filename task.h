#ifndef TASK_H
#define TASK_H

#include <QListWidgetItem>
#include <ctime>
#include <memory>
#include <QTreeWidgetItem>
#include <QDateTime>

class Task : public QTreeWidgetItem
{

public:
    explicit Task();

    void addWorkTime(unsigned int secs = 0);
    void setDueDate(unsigned int d_year = 1, unsigned int d_month = 1, unsigned int d_day = 1, unsigned int d_hour = 0, unsigned int d_min = 0);

    QString toString();
    void startTime();
    void stopTimer();

    QString project_name;
    QString description;

    bool archived;

    std::clock_t begin_time;

    QDateTime due_date;
    QTime work_done;

    unsigned int time_worked;
    unsigned int time_estimated;

    Task* pre_task;
    std::map<std::string, std::string> custome_fields;
};


#endif // TASK_H
