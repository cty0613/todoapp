#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "widgets/cmdwidget.h"

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

private slots:
    void onNewTodo(const QString &text);
    // cmdWidget에서 전달받은 텍스트로 새 TodoWidget 생성하는 슬롯

};
#endif // WIDGET_H
