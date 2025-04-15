#include "mainwindow.h"

#include <QApplication>

#include "model/reminder.h"
//#include "model/todo.h"

void Debug(QString str){
    qDebug() << "-------------------------------";
    qDebug() << str;
};

void arrDebug(QJsonArray array){
    QJsonDocument doc(array);
    QByteArray jsonBytes = doc.toJson(QJsonDocument::Indented);  // 또는 Compact
    QString jsonString = QString::fromUtf8(jsonBytes);

    qDebug() << "-------------------------------";
    qDebug().noquote() << jsonString;
};

void objDebug(QJsonObject obj){
    QJsonDocument doc(obj);
    QByteArray jsonBytes = doc.toJson(QJsonDocument::Indented);  // 또는 Compact
    QString jsonString = QString::fromUtf8(jsonBytes);

    qDebug() << "-------------------------------";
    qDebug().noquote() << jsonString;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setAttribute(Qt::WA_QuitOnClose, false);
    w.show();

    for(int i = 0; i < 100; i++){
        ToDo todo("todo" + QString::number(i), "todo "+ QString::number(i) + " is urgent!!");

        QDateTime rmd = QDateTime::currentDateTime().addDays(i);
        todo.setReminder(rmd);
        todo.setDate(rmd);

        todo.insertToDoJSON();
        //arrDebug(todo.readToDoJSON());
    }

    ToDo todo(0);
    arrDebug(todo.readToDoJSON(
        QDateTime::currentDateTime(),
        QDateTime::currentDateTime().addDays(10),
        ""));
    arrDebug(todo.readToDoJSONAlarm(
        QDateTime::currentDateTime(),
        QDateTime::currentDateTime().addDays(3),
        ""));

    todo.deleteToDoJSON(        QDateTime::currentDateTime(),
                        QDateTime::currentDateTime().addDays(3),
                        "");

    arrDebug(todo.readToDoJSON(
        QDateTime::currentDateTime(),
        QDateTime::currentDateTime().addDays(10),
        ""));
    return a.exec();
}

/* 반드시 실행 파일이랑 같은 폴더 안에 둘 것*/
// qDebug() << "현재 경로:" << QCoreApplication::applicationDirPath();
// QFile file = QFile(QCoreApplication::applicationDirPath()+ "/data/todo.json");
// if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//     qWarning() << "파일 열기 실패";
// }
// else{
//     qDebug() << "성공";
// }
/*
    ToDo todo_1("todo1", "todo 1 is urgent!!");
    todo_1.insertToDoJSON();
    arrDebug(todo_1.readToDoJSON());
    arrDebug(todo_1.readToDoJSON(
        QDateTime::currentDateTime(),
        QDateTime::currentDateTime(),
        "todo1"));

    ToDo todo_2("todo2", "todo 2 is urgent!!");
    todo_2.insertToDoJSON();
    arrDebug(todo_2.readToDoJSON());
    arrDebug(todo_2.readToDoJSON(
        QDateTime::currentDateTime(),
        QDateTime::currentDateTime(),
        "todo2"));

    ToDo todo_3("todo3", "todo 3 is urgent!!");
    todo_3.insertToDoJSON();
    arrDebug(todo_3.readToDoJSON());
    arrDebug(todo_3.readToDoJSON(
        QDateTime::currentDateTime(),
        QDateTime::currentDateTime(),
        "todo3"));

    todo_2.setTitle("I m mm");
    todo_2.updateToDoJSON();

    todo_1.deleteToDoJSON(QDateTime::currentDateTime(),
                          QDateTime::currentDateTime(),
                          "todo1");*/

