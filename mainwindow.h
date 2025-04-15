#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "widgets/cmdwidget.h"
#include "subwindow.h"

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

    void updateList(bool initLoad);
    void connectWidgetsInLayout();
    void disconnectWidgetsInLayout();

private slots:
    void onNewTodo(const QString &text);
    // cmdWidget에서 전달받은 텍스트로 새 TodoWidget 생성하는 슬롯
    void deleteTodo(const int &todoId);
    void chkTodo(const int &todoId);
    void editTodo(const int &todoId);

};
#endif // WIDGET_H
