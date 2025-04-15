#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subwindow.h"
#include "widgets/todowidget.h"
#include "widgets/voidwidget.h"
#include "model/todo.h"

#include <QScrollArea>
#include <QIcon>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // mainwindow.cpp 또는 setupUi 이후에 추가
    // QScrollArea *scrollArea = new QScrollArea(this);       // 스크롤 영역 생성
    // scrollArea->setStyleSheet("border-radius: 10px; padding:5px;");
    // scrollArea->setWidget(ui->TodoListGroup);                    // 기존 TodoListGroup을 감쌈
    // scrollArea->setWidgetResizable(true);                        // 내부 위젯 크기에 맞게 조절
    // scrollArea->setFixedHeight(300);                             // 원하는 높이로 고정 (예: 300픽셀)

    // ui->verticalLayout_4->insertWidget(2, scrollArea);        // 기존 위치(두 번째 item)에 삽입
    // ui->verticalLayout_4->setAlignment(Qt::AlignCenter);
    // init

    ui->comboBox->addItem(QIcon(":/icon/data/Alphabetical Sorting.png"), "by Title");
    ui->comboBox->addItem(QIcon(":/icon/data/Reversed Numerical Sorting.png"), "by Date");

    cmdWidget = new CmdWidget();
    ui->cmdGroupLayout->addWidget(cmdWidget);

    updateList(true);

    // cmdWidget의 시그널 sendText와 MainWindow의 슬롯 onNewTodo를 연결
    // 텍스트 전달 시 새 TodoWidget 추가
    connect(cmdWidget, &CmdWidget::sendText, this, &MainWindow::onNewTodo);


}

MainWindow::~MainWindow()
{
    delete ui;
}

// SLOTS
void MainWindow::onNewTodo(const QString &text)
{
    ToDo* newTodo = new ToDo(text, " ");
    newTodo->insertToDoJSON();

    updateList(false);

}

void MainWindow::deleteTodo(const int &todoId){
    ToDo().deleteToDoJSON(todoId);
    updateList(false);

}

void MainWindow::chkTodo(const int &todoId){
    QJsonObject targetTodo = ToDo().getTodoById(todoId);
    targetTodo["complete"] = true;
    ToDo(targetTodo).updateToDoJSON();

    updateList(false);
}

void MainWindow::editTodo(const int &todoId){
    QJsonObject targetTodo = ToDo().getTodoById(todoId);
    SubWindow* subw = new SubWindow(targetTodo);
    subw->show();

    // todoSave 시그널이 발생했을 때 subw 닫고 삭제
    connect(subw, &SubWindow::todoSave, this, [subw, this]() {
        subw->close();          // 창 닫기
        subw->deleteLater();    // 안전하게 메모리에서 제거
        this->updateList(false);
    });

    // todoCancel 시그널이 발생했을 때도 동일하게 처리
    connect(subw, &SubWindow::todoCancel, this, [subw]() {
        subw->close();
        subw->deleteLater();
    });
}


// PRIVATE METHODS
void MainWindow::updateList(bool initLoad){
    if(!initLoad){
        // layout에 남아 있는 모든 항목을 순차적으로 제거
        while (QLayoutItem* item = ui->TodoListGroupLayout->takeAt(0)) {
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

    QJsonArray todoObjArray = ToDo().readToDoJSON();
     // Todo가 있는 경우 해당하는 위젯 추가
    for (const QJsonValue &val : todoObjArray) {
        QJsonObject obj = val.toObject();
        if( !(obj.value("complete").toBool()) ) {
            int _id = obj["id"].toInt();
            QString _title = obj["title"].toString();
            QString _iconPath = obj["iconPath"].toString();
            TodoWidget* newTodoWidget = new TodoWidget(_id, _title, _iconPath, this);
            ui->TodoListGroupLayout->addWidget(newTodoWidget);
        }
    }

    if ( ui->TodoListGroupLayout->count() < 1){ // 미완료된 Todo가 비어있을 경우
        VoidWidget* emptyDisplay = new VoidWidget();
        ui->TodoListGroupLayout->addWidget(emptyDisplay);
    }


    // UI를 모두 비운다음
    // JSON으로부터 읽어와서
    // 어레이 루프 동안
    // 각 오브젝트를 뽑고나서
    // TodoWidget 생성

    connectWidgetsInLayout();


}

void MainWindow::connectWidgetsInLayout() {
    int count = ui->TodoListGroupLayout->count();  // layout에 들어있는 항목 수
    for (int i = 0; i < count; ++i) {
        QLayoutItem* item = ui->TodoListGroupLayout->itemAt(i);  // i번째 항목
        QWidget* widget = item->widget();       // 위젯 가져오기
        if (widget) {
            // 예: TodoWidget 클래스인지 확인하고 연결
            TodoWidget* todo = qobject_cast<TodoWidget*>(widget);
            if (todo) {
                // 예시: todo 위젯의 특정 시그널에 connect
                connect(todo, &TodoWidget::deleteBtnClicked,
                        this, &MainWindow::deleteTodo);

                connect(todo, &TodoWidget::chkBtnClicked,
                        this, &MainWindow::chkTodo);

                connect(todo, &TodoWidget::editBtnClicked,
                         this, &MainWindow::editTodo);
            }
        }
    }
}


void MainWindow::disconnectWidgetsInLayout() {
    int count = ui->TodoListGroupLayout->count();  // layout에 들어있는 항목 수
    for (int i = 0; i < count; ++i) {
        QLayoutItem* item = ui->TodoListGroupLayout->itemAt(i);  // i번째 항목
        QWidget* widget = item->widget();       // 위젯 가져오기
        if (widget) {
            // 예: TodoWidget 클래스인지 확인하고 연결
            TodoWidget* todo = qobject_cast<TodoWidget*>(widget);
            if (todo) {
                // 예시: todo 위젯의 특정 시그널에 connect
                disconnect(todo, &TodoWidget::deleteBtnClicked,
                        this, &MainWindow::deleteTodo);

                disconnect(todo, &TodoWidget::chkBtnClicked,
                        this, &MainWindow::chkTodo);

                disconnect(todo, &TodoWidget::editBtnClicked,
                         this, &MainWindow::editTodo);
            }
        }
    }
}
