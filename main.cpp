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
    SubWindow sw;
    // w.setAttribute(Qt::WA_QuitOnClose, false);
    w.show();
    sw.hide();
  
    return a.exec();
}
