#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>

namespace Ui {
class SubWindow;
}

class SubWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SubWindow(QWidget *parent = nullptr);
    ~SubWindow();

private:
    Ui::SubWindow *ui;
    QJsonObject* todoObj;
};

#endif // SUBWINDOW_H
