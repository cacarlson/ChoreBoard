#ifndef TASKLIST_H
#define TASKLIST_H

#include <ui_mainwindow.h>
#include <QListWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <Task.h>
#include <string>

class TaskList
{
public:
    explicit TaskList(QTreeWidget * m_tree);

    unsigned int num_active;
    unsigned int num_archived;

    QTreeWidget* task_list;
    Task* top_task;

    QString toString();

    bool saveToFile();
    void loadFromFile();

    void markTaskTop();

private:

signals:

public slots:

};

#endif // TASKLIST_H
