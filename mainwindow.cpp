#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // init

    ui->comboBox->addItem(QIcon(":/icon/data/Alphabetical Sorting.png"), "by Title");
    ui->comboBox->addItem(QIcon(":/icon/data/Reversed Numerical Sorting.png"), "by Date");

    cmdWidget = new CmdWidget();
    ui->cmdGroupLayout->addWidget(cmdWidget);

    todo1 = new TodoWidget("Hello", this);
    todo2 = new TodoWidget("Hello", this);
    todo3 = new TodoWidget("Hello", this);
    ui->TodoListGroupLayout->addWidget(todo1);
    ui->TodoListGroupLayout->addWidget(todo2);
    ui->TodoListGroupLayout->addWidget(todo3);


    todo_d = new TodoWidget("Done", this);
    ui->doneListGroupLayout->addWidget(todo_d);

}

MainWindow::~MainWindow()
{
    delete ui;
}
