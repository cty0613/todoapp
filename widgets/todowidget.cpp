#include "todowidget.h"
#include "ui_todowidget.h"

TodoWidget::TodoWidget(int Id, QString title, QString iconPath,  QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TodoWidget)
{
    QPixmap icon(iconPath);

    todoId = Id;

    ui->setupUi(this);
    ui->icon->setPixmap(icon);
    ui->todoTitle->setText(title);

    connect(ui->deleteBtn, &QPushButton::clicked,
            this, &TodoWidget::onDeleteBtnClicked);

    connect(ui->doneBtn, &QPushButton::clicked,
            this, &TodoWidget::onChkBtnClicked);

    connect(ui->editBtn, &QPushButton::clicked,
            this, &TodoWidget::onEditBtnClicked);


}

TodoWidget::~TodoWidget()
{
    delete ui;
}

void TodoWidget::onDeleteBtnClicked(){
    emit deleteBtnClicked(todoId);
}

void TodoWidget::onChkBtnClicked(){
    emit chkBtnClicked(todoId);
}

void TodoWidget::onEditBtnClicked(){
    emit editBtnClicked(todoId);
}

