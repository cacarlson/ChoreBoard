#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "task.h"
#include <QComboBox>
#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Name = new QTreeWidgetItem();
    Archived = new QTreeWidgetItem();
    DueDate = new QTreeWidgetItem();
    Project = new QTreeWidgetItem();
    TimeEst = new QTreeWidgetItem();
    TimeWorked = new QTreeWidgetItem();
    Pre_req = new QTreeWidgetItem();

    m_combobox = new QComboBox(ui->taskList);

    m_combobox->addItem("Archived","Archived");
    m_combobox->addItem("Not Archived", "Not Archived");

    Name->setFlags(Name->flags() | Qt::ItemIsEditable);
    ui->dataTable->addTopLevelItem(Name);

    ui->dataTable->addTopLevelItem(Archived);
    ui->dataTable->setItemWidget(Archived,1,m_combobox);

    DueDate->setFlags(DueDate->flags() | Qt::ItemIsEditable);
    ui->dataTable->addTopLevelItem(DueDate);

    Project->setFlags(Project->flags() | Qt::ItemIsEditable);
    ui->dataTable->addTopLevelItem(Project);

    TimeEst->setFlags(TimeEst->flags() | Qt::ItemIsEditable);
    ui->dataTable->addTopLevelItem(TimeEst);

    TimeWorked->setFlags(TimeWorked->flags() | Qt::ItemIsEditable);
    ui->dataTable->addTopLevelItem(TimeWorked);

    Pre_req->setFlags(Pre_req->flags() | Qt::ItemIsEditable);
    ui->dataTable->addTopLevelItem(Pre_req);

    connect(ui->taskList, SIGNAL(itemSelectionChanged()), this, SLOT(TaskListItemChanged()));
    connect(ui->dataTable, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(DateUpdated(QTreeWidgetItem*,int)));
    connect(m_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboBoxChange()));
    m_taskList = new TaskList(ui, ui->taskList);
}

void MainWindow::TaskListItemChanged()
{
    Task* m_task = (Task*)ui->taskList->currentItem();

    Name->setText(0, "Name:");
    Name->setText(1,  ui->taskList->currentItem()->text(0));

    DueDate->setText(0, "Due Date:");
    DueDate->setText(1, ui->taskList->currentItem()->text(1));

    Project->setText(0, "Project:");
    Project->setText(1, m_task->project_name);

    TimeEst->setText(0, "Time Est.");
    TimeEst->setText(1, m_task->estToString());

    TimeWorked->setText(0, "Time Worked:");
    TimeWorked->setText(1,m_task->workedToString());

    Pre_req->setText(0, "Pre-Req:");

    if(m_task->pre_task != NULL)
        Pre_req->setText(1, m_task->pre_task->text(0));
    else
        Pre_req->setText(1, "None");

    Archived->setText(0, "Archived:");

    if(m_task->archived)
    {
        m_combobox->setCurrentIndex(0);
    }
    else
    {
        m_combobox->setCurrentIndex(1);
    }

    m_currentTask = m_task;
}

void MainWindow::DateUpdated(QTreeWidgetItem *, int col)
{
    Task* m_task = (Task*)ui->taskList->currentItem();
    if(col == 1 && m_task == m_currentTask)
    {
        m_task->setText(0, Name->text(1));
        QDateTime m_date = QDateTime::fromString(DueDate->text(1), "MM/dd/yy HH:ss");
        if(m_date.isValid())
        {
            m_task->due_date = m_date;
            m_task->setText(1,m_date.toString("MM/dd/yy HH:ss"));
        }

        m_task->project_name = Project->text(1);
        QStringList m_stringList = TimeEst->text(1).split(':');
        m_task->time_estimated = m_stringList[0].toUInt(NULL,10)*3600 + m_stringList[1].toUInt(NULL,10)*60 + m_stringList[2].toUInt(NULL,10);
        m_stringList = TimeWorked->text(1).split(':');
        m_task->time_worked = m_stringList[0].toUInt(NULL,10)*3600 + m_stringList[1].toUInt(NULL,10)*60 + m_stringList[2].toUInt(NULL,10);
        m_task->setText(2, m_task->workedToString());
        if(Pre_req->text(1) != "None")
            m_task->pre_task = ((Task*)ui->taskList->findItems(Pre_req->text(1),Qt::MatchCaseSensitive, 0).first());
    }
}

void MainWindow::ComboBoxChange()
{
    Task* m_task = (Task*)ui->taskList->currentItem();
    m_task->archived = !m_combobox->currentIndex();
}

MainWindow::~MainWindow()
{
    delete m_taskList;
    delete ui;
}
