#include "cmdwidget.h"
//#include "ui_cmdwidget.h"

CmdWidget::CmdWidget(QWidget *parent)
    : QWidget(parent)
{
}

CmdWidget::~CmdWidget()
{
    delete ui;
}
