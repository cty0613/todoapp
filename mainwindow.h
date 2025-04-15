#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "widgets/cmdwidget.h"
#include "widgets/todowidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    CmdWidget* cmdWidget;
    TodoWidget* todo1;
    TodoWidget* todo2;
    TodoWidget* todo3;
    TodoWidget* todo_d;

};
#endif // WIDGET_H
