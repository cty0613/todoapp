#include "subwindow.h"
#include "ui_subwindow.h"
#include "model/todo.h"
#include "widgets/voidwidget.h"
#include "widgets/todowidget.h"
#include "widgets/subtodowidget.h"

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

    connect(ui->addSubTodoBtn, &QPushButton::clicked,
            this, &SubWindow::onAddSubTodoBtn);

    updateSubList(true);

}

SubWindow::~SubWindow()
{
    delete ui;
}

void SubWindow::deleteSubTodo(const int &todoId, const int &parentId){
    // 부모에서 자식들의 todoId 삭제
    QJsonObject targetTodo = ToDo().getTodoById(parentId);
    QJsonArray subTasks = targetTodo["subTasks"].toArray();
    for (int i = 0; i < subTasks.size(); ++i) {
        if (subTasks[i].toInt() == todoId) {
            subTasks.removeAt(i);  // 해당 인덱스에서 삭제
            break;  // 중복이 없다는 가정하에 break
        }
    }
    targetTodo["subTasks"] = subTasks;
    ToDo(targetTodo).updateToDoJSON();


    // 자식(subToDo) 삭제
    ToDo().deleteToDoJSON(todoId);

    // 서브리스트 업데이트
    updateSubList(false);
}

void SubWindow::chkSubTodo(const int &todoId){
    QJsonObject targetTodo = ToDo().getTodoById(todoId);
    targetTodo["complete"] = true;
    ToDo(targetTodo).updateToDoJSON();

    updateSubList(false);
}

void SubWindow::onSubTodoChanged(QString title, const int &todoId, const int &parentId){
    QJsonObject targetTodo = ToDo().getTodoById(todoId);
    targetTodo["title"] = title;
    ToDo(targetTodo).updateToDoJSON();

    updateSubList(false);
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

void SubWindow::onAddSubTodoBtn() {
    ToDo* newTodo = new ToDo("", " ");
    newTodo->setParentTask(todoObj["id"].toInt());
    newTodo->insertToDoJSON();

    QJsonObject targetTodo = ToDo().getTodoById(todoObj["id"].toInt());
    QJsonArray subTasks = targetTodo["subTasks"].toArray();
    subTasks.append(newTodo->Id());
    targetTodo["subTasks"] = subTasks;
    ToDo(targetTodo).updateToDoJSON();

    updateSubList(false);

    // SubTodoWidget* newSubTodo = new SubTodoWidget(
    //     ToDo().getMaxId(), // SubTodo Id
    //     todoObj["id"].toInt(), // SubTodo's ParnetId
    //     false); // complete = false
    // ui->subTodosLayout->addWidget(newSubTodo);
}

void SubWindow::updateSubList(bool initLoad){
    // [1] UI를 모두 비운다음
    // [2] JSON 으로부터
    // 지금 todoObj에 해당되는 SubTodo들을 끌고와서
    // 그 SubTodo 어레이를 루프를 돌리는 동안
    // SubTodoWidget 생성

    if(!initLoad){ // [1]
        // layout에 남아 있는 모든 항목을 순차적으로 제거
        while (QLayoutItem* item = ui->subTodosLayout->takeAt(0)) {
            // layout에서 위젯을 가져옴
            QWidget* widget = item->widget();
            if (widget) {
                widget->setParent(nullptr);
                delete widget;   // 위젯 삭제
            }
            delete item;  // 레이아웃도 삭제
        }
    }

    disconnectWidgetsInLayout();

    todoObj = ToDo().getTodoById(todoObj["id"].toInt());
    QJsonArray subTasksArray = todoObj["subTasks"].toArray();  //[2] 배열 가져오기

    for (const QJsonValue &val : subTasksArray) {
        if (val.isDouble()) {  // JSON에서는 숫자가 double로 들어옴
            qDebug() << "hhh";
            QJsonObject subTask = ToDo().getTodoById(val.toInt());
            int _id = subTask["id"].toInt();
            int _pid = subTask["parentTask"].toInt();
            bool _complete = subTask["complete"].toBool();
            QString _title = subTask["title"].toString();
            QString _iconPath = subTask["iconPath"].toString();
            SubTodoWidget* newSubTodoWidget = new SubTodoWidget(_id, _pid, _complete, _title, _iconPath, this);
            ui->subTodosLayout->addWidget(newSubTodoWidget);
        }
    }

    if ( ui->subTodosLayout->count() < 1){ // 완료된 Todo가 비어있을 경우
        VoidWidget* emptyDisplay = new VoidWidget();
        ui->subTodosLayout->addWidget(emptyDisplay);
    }

    connectWidgetsInLayout();

}

void SubWindow::connectWidgetsInLayout(){
    int count = ui->subTodosLayout->count();  // layout에 들어있는 항목 수
    for (int i = 0; i < count; ++i) {
        QLayoutItem* item = ui->subTodosLayout->itemAt(i);  // i번째 항목
        QWidget* widget = item->widget();       // 위젯 가져오기
        if (widget) {
            // 예: TodoWidget 클래스인지 확인하고 연결
            SubTodoWidget* todo = qobject_cast<SubTodoWidget*>(widget);
            if (todo) {
                // 예시: todo 위젯의 특정 시그널에 connect
                connect(todo, &SubTodoWidget::deleteBtnClicked,
                        this, &SubWindow::deleteSubTodo);

                connect(todo, &SubTodoWidget::chkBtnClicked,
                        this, &SubWindow::chkSubTodo);

                connect(todo, &SubTodoWidget::titleChanged,
                        this, &SubWindow::onSubTodoChanged);

            }
        }
    }
}

void SubWindow::disconnectWidgetsInLayout(){

    int count = ui->subTodosLayout->count();  // layout에 들어있는 항목 수
    for (int i = 0; i < count; ++i) {
        QLayoutItem* item = ui->subTodosLayout->itemAt(i);  // i번째 항목
        QWidget* widget = item->widget();       // 위젯 가져오기
        if (widget) {
            // 예: TodoWidget 클래스인지 확인하고 연결
            SubTodoWidget* todo = qobject_cast<SubTodoWidget*>(widget);
            if (todo) {
                // 예시: todo 위젯의 특정 시그널에 connect
                disconnect(todo, &SubTodoWidget::deleteBtnClicked,
                           this, &SubWindow::deleteSubTodo);

                disconnect(todo, &SubTodoWidget::chkBtnClicked,
                           this, &SubWindow::chkSubTodo);

                disconnect(todo, &SubTodoWidget::titleChanged,
                           this, &SubWindow::onSubTodoChanged);

            }
        }
    }
}
