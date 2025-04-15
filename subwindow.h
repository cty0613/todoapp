#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QJsonObject>
namespace Ui {
class SubWindow;
}

class SubWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SubWindow(
        QJsonObject todo,
        QWidget *parent = nullptr
        );
    ~SubWindow();

private:
    Ui::SubWindow *ui;
    QJsonObject todoObj;
};

#endif // SUBWINDOW_H
