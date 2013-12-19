#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "task.h"
#include <QComboBox>
#include <QTreeWidget>
#include <QDateTime>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_taskList = new TaskList(ui->taskList);
    m_taskList->loadFromFile();
    m_combobox = new QComboBox(ui->taskList);
    m_timer = new QTimer();
    m_begin_work = false;
    m_work_seconds = 0;

    Name = new QTreeWidgetItem();
    Archived = new QTreeWidgetItem();
    DueDate = new QTreeWidgetItem();
    Project = new QTreeWidgetItem();
    TimeEst = new QTreeWidgetItem();
    TimeWorked = new QTreeWidgetItem();
    Pre_req = new QTreeWidgetItem();

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
    connect(ui->description, SIGNAL(textChanged()), this, SLOT(DescriptionChanged()));
    connect(m_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboBoxChange()));
    connect(ui->CreateTask, SIGNAL(clicked()), this, SLOT(CreateTask()));
    connect(ui->DeleteTask, SIGNAL(clicked()), this, SLOT(DeleteTask()));
    connect(ui->MoveDown, SIGNAL(clicked()), this, SLOT(MoveDown()));
    connect(ui->MoveUp, SIGNAL(clicked()), this, SLOT(MoveUp()));
    connect(ui->MakeTop, SIGNAL(clicked()), this, SLOT(MakeTop()));
    connect(ui->Start, SIGNAL(clicked()), this, SLOT(StartTimer()));
    connect(ui->Stop, SIGNAL(clicked()), this, SLOT(StopTimer()));

    ui->lcdNumber->setSegmentStyle(QLCDNumber::Filled);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(UpdateCounter()));
    m_timer->start(1000);

    UpdateCounter();
}

void MainWindow::UpdateCounter()
{
    QTime time = QTime::QTime::currentTime();
    QString text;
    if(m_taskList->top_task != NULL && m_begin_work)
    {
        m_taskList->top_task->addWorkTime(1);
        text = QDateTime::fromTime_t(m_taskList->top_task->time_worked).toString("mm:ss");
        m_taskList->top_task->setText(2, m_taskList->top_task->workedToString());
        TimeWorked->setText(1,((Task*)m_taskList->task_list->currentItem())->workedToString());
    }
    else
        text = QDateTime::fromTime_t(0).toString("mm:ss");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdNumber->display(text);
    if(m_taskList->top_task != NULL)
    {
        m_taskList->top_task->colorRow(Qt::red,2);
    }
}

void MainWindow::TaskListItemChanged()
{
    Task* m_task = (Task*)ui->taskList->currentItem();

    if(m_task != NULL)
    {
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

        /*if(m_task->pre_task != NULL)
            Pre_req->setText(1, m_task->pre_task->text(0));
        else*/
        Pre_req->setText(1, "None");

        Archived->setText(0, "Archived:");

        if(m_task->archived)
        {
            m_combobox->setCurrentIndex(0);
            m_task->colorRow(Qt::cyan, 2);
        }
        else
        {
            m_combobox->setCurrentIndex(1);
            m_task->colorRow(Qt::transparent, 2);
        }

        ui->description->setPlainText(m_task->description);

        m_currentTask = m_task;
    }

    m_taskList->saveToFile();
}

void MainWindow::DateUpdated(QTreeWidgetItem *, int col)
{
    Task* m_task = (Task*)ui->taskList->currentItem();
    if(col == 1 && m_task != NULL && m_task == m_currentTask)
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
        //if(Pre_req->text(1) != "None")
        //    m_task->pre_task = ((Task*)ui->taskList->findItems(Pre_req->text(1),Qt::MatchCaseSensitive, 0).first());
    }

    m_taskList->saveToFile();
}

void MainWindow::CreateTask()
{
    Task* new_task = new Task();
    new_task->setText(0,"unknown task");
    new_task->due_date = QDateTime::currentDateTime();
    new_task->setText(1,new_task->due_date.toString("MM/dd/yy HH:mm"));
    new_task->setText(2,new_task->workedToString());

    ui->taskList->insertTopLevelItem(0,new_task);

    m_taskList->task_list->resizeColumnToContents(0);
    m_taskList->task_list->resizeColumnToContents(1);
    m_taskList->task_list->resizeColumnToContents(2);

    m_taskList->saveToFile();
}

void MainWindow::DeleteTask()
{
    if( ui->taskList->currentIndex().row() >= 0 && ui->taskList->currentItem() != m_taskList->top_task)
        ui->taskList->takeTopLevelItem(ui->taskList->currentIndex().row());

    m_taskList->saveToFile();
}

void MainWindow::DescriptionChanged()
{
    ((Task*)ui->taskList->currentItem())->description = ui->description->toPlainText();

    m_taskList->saveToFile();
}

void MainWindow::ComboBoxChange()
{
    Task* m_task = (Task*)ui->taskList->currentItem();
    m_task->archived = !m_combobox->currentIndex();

    if(m_task->archived)
        m_task->colorRow(Qt::cyan, 2);
    else
       m_task->colorRow(Qt::transparent, 2);

    m_taskList->saveToFile();
}

void MainWindow::MoveDown()
{
    int old_row = ui->taskList->currentIndex().row();
    if (old_row+1 < ui->taskList->topLevelItemCount())
    {
        Task* task = (Task*)(ui->taskList->takeTopLevelItem(old_row));
        ui->taskList->insertTopLevelItem(old_row + 1, task);
        ui->taskList->setCurrentItem(task);
    }
    m_taskList->saveToFile();
}

void MainWindow::MoveUp()
{
    int old_row = ui->taskList->currentIndex().row() ;
    if (old_row > 0)
    {
        Task* task = (Task*)(ui->taskList->takeTopLevelItem(old_row));
        ui->taskList->insertTopLevelItem(old_row - 1, task);
        ui->taskList->setCurrentItem(task);
    }
    m_taskList->saveToFile();
}

void MainWindow::MakeTop()
{
    if(m_taskList->task_list->currentItem() != m_taskList->top_task)
        m_taskList->markTaskTop();
    else
    {
        StopTimer();
        m_taskList->top_task = NULL;
        ((Task*)m_taskList->task_list->currentItem())->colorRow(Qt::transparent, 2);
    }
}

void MainWindow::StartTimer()
{
    if(m_taskList->top_task != NULL && m_begin_work == false)
    {
        m_begin_work = true;
    }
}

void MainWindow::StopTimer()
{
    if(m_taskList->top_task != NULL && m_begin_work == true)
    {
        m_begin_work = false;
    }
    m_taskList->saveToFile();
}

MainWindow::~MainWindow()
{
    delete m_taskList;
    delete ui;
}
