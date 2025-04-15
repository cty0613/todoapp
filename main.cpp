#include "mainwindow.h"

#include "subwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SubWindow sw;
    w.show();
    sw.show();
    return a.exec();
}
