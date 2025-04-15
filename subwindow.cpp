#include "subwindow.h"
#include "ui_subwindow.h"

SubWindow::SubWindow(QJsonObject todo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubWindow)
{
    ui->setupUi(this);
}

SubWindow::~SubWindow()
{
    delete ui;
}
