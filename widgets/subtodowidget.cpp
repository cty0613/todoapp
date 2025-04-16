#include "subtodowidget.h"
#include "ui_subtodowidget.h"

SubTodoWidget::SubTodoWidget(int id,
                             int pid,
                             bool completed,
                             QString title,
                             QString iconPath,
                             QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubTodoWidget)
{
    ui->setupUi(this);

    QPixmap icon(iconPath);

    todoId = id;
    parentId = pid;

    ui->lineEdit->setText(title);

    if(completed){
        ui->lineEdit->setStyleSheet("text-decoration: line-through; color:grey;");

    }

    connect(ui->deleteBtn, &QPushButton::clicked,
            this, &SubTodoWidget::onDeleteBtnClicked);

    connect(ui->doneBtn, &QPushButton::clicked,
            this, &SubTodoWidget::onChkBtnClicked);

    connect(ui->lineEdit, &QLineEdit::textChanged,
            this, &SubTodoWidget::onTextModified);

    connect(ui->lineEdit, &QLineEdit::editingFinished,
            this, &SubTodoWidget::onLineEdited);

}

SubTodoWidget::~SubTodoWidget()
{
    delete ui;
}

void SubTodoWidget::onTextModified(const QString &text){
    textMod = true;
}

void SubTodoWidget::onLineEdited(){
    if(textMod) { emit titleChanged(ui->lineEdit->text(), todoId, parentId); }

}

void SubTodoWidget::onDeleteBtnClicked(){
    emit deleteBtnClicked(todoId, parentId);
}

void SubTodoWidget::onChkBtnClicked(){
    emit chkBtnClicked(todoId);
}
