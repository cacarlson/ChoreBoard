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
    explicit TaskList(Ui::MainWindow *ui, QTreeWidget * m_tree);

    unsigned int num_active;
    unsigned int num_archived;

    QTreeWidget* task_list;
    QTreeWidgetItem* top_task;

    QString toString();

    bool saveToFile();
    void loadFromFile();

    void markTaskTop();

private:
    Ui::MainWindow *myUi;

signals:

public slots:

};

#endif // TASKLIST_H
