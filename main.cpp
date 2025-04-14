#include "mainwindow.h"

#include <QApplication>
#include "model/todo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*
     * 반드시 실행 파일이랑 같은 폴더 안에 둘 것
    qDebug() << "현재 경로:" << QCoreApplication::applicationDirPath();
    QFile file = QFile(QCoreApplication::applicationDirPath()+ "/data/todo.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "파일 열기 실패";
    }
    else{
        qDebug() << "성공";
    }
    */

    return a.exec();
}
