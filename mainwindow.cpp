#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/todowidget.h"

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

    // cmdWidget의 시그널 sendText와 MainWindow의 슬롯 onNewTodo를 연결
    // 텍스트 전달 시 새 TodoWidget 추가
    connect(cmdWidget, &CmdWidget::sendText, this, &MainWindow::onNewTodo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewTodo(const QString &text)
{
    // 전달받은 텍스트로 새로운 TodoWidget 생성
    TodoWidget *newTodo = new TodoWidget(text, ":/icon/data/Music.png", this);

    // 생성된 TodoWidget을 TodoListGroupLayout에 추가하여 화면에 표시
    ui->TodoListGroupLayout->addWidget(newTodo);  // 레이아웃에 새 TodoWidget 배치
}
