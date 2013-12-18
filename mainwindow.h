#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "tasklist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QTreeWidgetItem* Name;
    QTreeWidgetItem* Archived;
    QTreeWidgetItem* DueDate;
    QTreeWidgetItem* Project;
    QTreeWidgetItem* TimeEst;
    QTreeWidgetItem* TimeWorked;
    QTreeWidgetItem* Pre_req;

    TaskList *m_taskList;
    Task *m_currentTask;
    QComboBox *m_combobox;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void TaskListItemChanged();
    void DateUpdated(QTreeWidgetItem*,int);
    void ComboBoxChange();

private slots:

};

#endif // MAINWINDOW_H
