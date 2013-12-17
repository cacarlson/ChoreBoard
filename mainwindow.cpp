#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_taskList = new TaskList(ui, ui->FindME);
}

MainWindow::~MainWindow()
{
    delete m_taskList;
    delete ui;
}
