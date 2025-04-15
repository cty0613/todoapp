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
    w.setAttribute(Qt::WA_QuitOnClose, false);
    w.show();

    for(int i = 0; i < 10; i++){
        ToDo todo("todo" + QString::number(i), "todo "+ QString::number(i) + " is urgent!!");

        QDateTime rmd = QDateTime::currentDateTime().addDays(i);
        todo.setReminder(rmd);
        todo.setDate(rmd);

        todo.insertToDoJSON();
        //arrDebug(todo.readToDoJSON());
    }

    ToDo todo(-1);
    //todo.deleteToDoJSON(QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(10), "");

    QJsonArray arr = todo.readToDoJSON(QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(3), "");
    QJsonArray sorted = sortJSONByDate(arr);
    arrDebug(sorted);

    //Reminder rmd;
    //rmd.setReminder(&todo);

    return a.exec();
}

/* 반드시 실행 파일이랑 같은 폴더 안에 둘 것*/

