#ifndef TASKLIST_H
#define TASKLIST_H

#include <QListWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <Task.h>
#include <string>

class TaskList : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TaskList(QWidget *parent = 0);

    unsigned int num_active;
    unsigned int num_archived;

    QTreeWidgetItem* top_task;

    //No need to implement add, remove, archive as they are handled by listwidget
    QString toString();

    bool saveToFile();
    void loadFromFile();

    void markTaskTop();

signals:

public slots:

};

#endif // TASKLIST_H
