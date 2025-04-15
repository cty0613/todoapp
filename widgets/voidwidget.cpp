#include "voidwidget.h"
#include "ui_voidwidget.h"

VoidWidget::VoidWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VoidWidget)
{
    ui->setupUi(this);
}

VoidWidget::~VoidWidget()
{
    delete ui;
}
