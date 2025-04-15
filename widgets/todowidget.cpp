#include "todowidget.h"
#include "ui_todowidget.h"

TodoWidget::TodoWidget(QString title, QString iconPath, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TodoWidget)
{
    QPixmap icon(iconPath);

    ui->setupUi(this);
    ui->icon->setPixmap(icon);
    ui->todoTitle->setText(title);
}

TodoWidget::~TodoWidget()
{
    delete ui;
}
