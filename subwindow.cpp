#include "subwindow.h"
#include "ui_subwindow.h"
#include "model/todo.h"

SubWindow::SubWindow(QJsonObject todo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubWindow)
    , todoObj(todo)
{
    ui->setupUi(this);
    // Todo Title
    ui->lineEdit->setText(todoObj.value("title").toString());

    // Todo Icon
    QPixmap icon = QPixmap(todoObj.value("iconPath").toString());
    ui->todoIcon->setPixmap(icon);

    // Todo Date
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(todoObj.value("date").toString(), "yyyy-MM-dd"));

    // Reminder Edit
    if (todoObj.value("reminder") == "") {
        ui->reminderEdit->setStyleSheet("color: lightgrey;");
        ui->reminderLabel->setText("No reminder set.");
    } else {
        ui->reminderEdit->setDateTime(QDateTime::fromString(todoObj.value("reminder").toString(), "yyyy-MM-dd HH:mm"));
    }


    // Details
    ui->detailTextEdit->setText(todoObj.value("detail").toString());


    connect(ui->saveBtn, &QPushButton::clicked,
            this, &SubWindow::onSaveBtn);

    connect(ui->cancelBtn, &QPushButton::clicked,
            this, &SubWindow::onCancelBtn);

}

SubWindow::~SubWindow()
{
    delete ui;
}

void SubWindow::onSaveBtn(){
    // title
    todoObj["title"] = ui->lineEdit->text();
    // date
    todoObj["date"] = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd");
    // reminder
    QDateTime reminderValue = ui->reminderEdit->dateTime();
    // 날짜가 설정된 경우만 저장
    if (reminderValue.isValid() && reminderValue != QDateTime()) {
        todoObj["reminder"] = reminderValue.toString("yyyy-MM-dd HH:mm");
        todoObj["reminded"] = false;
    } else {
        todoObj["reminder"] = "";  // 기본값이라면 공백으로 저장
        todoObj["reminded"] = false;
    }
    // details
    todoObj["detail"] = ui->detailTextEdit->toPlainText();

    ToDo(todoObj).updateToDoJSON();

    emit todoSave();
}

void SubWindow::onCancelBtn() {
    emit todoCancel();
}
