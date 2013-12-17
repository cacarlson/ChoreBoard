#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tasklist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    TaskList *m_taskList;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:

};

#endif // MAINWINDOW_H
