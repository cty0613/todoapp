#include "todowidget.h"
#include "ui_todowidget.h"

TodoWidget::TodoWidget(QString title, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TodoWidget)
{
    ui->setupUi(this);
    ui->todoTitle->setText(title);
}

TodoWidget::~TodoWidget()
{
    delete ui;
}
