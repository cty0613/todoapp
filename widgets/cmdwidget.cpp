#include "cmdwidget.h"
#include "ui_cmdwidget.h"

CmdWidget::CmdWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CmdWidget)
{
    ui->setupUi(this);
}

CmdWidget::~CmdWidget()
{
    delete ui;
}
