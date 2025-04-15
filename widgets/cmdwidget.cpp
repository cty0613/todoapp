#include "cmdwidget.h"
#include "ui_cmdwidget.h"

CmdWidget::CmdWidget(QWidget *parent)
    : QWidget(parent) , ui(new Ui::CmdWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,
            this, &CmdWidget::onPushButtonClicked);

    connect(ui->lineEdit, &QLineEdit::returnPressed,
            this, &CmdWidget::onPushButtonClicked);
}

CmdWidget::~CmdWidget()
{
    delete ui;
}

void CmdWidget::onPushButtonClicked()
{
    // QLineEdit에 입력된 텍스트를 읽음 (ui->lineEdit이 있다고 가정)
    QString inputText = ui->lineEdit->text();
    // 입력된 텍스트를 변수에 저장

    // 텍스트가 비어있지 않으면 시그널을 발생시킴
    if (!inputText.isEmpty()) {     // 텍스트가 있다면
        emit sendText(inputText);   // 입력 텍스트를 전달하는 시그널 발생
    }
}
