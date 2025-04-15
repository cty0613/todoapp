#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QJsonObject>
#include <QDateTime>

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

signals:
    void todoSave();
    void todoCancel();

private:
    Ui::SubWindow *ui;
    QJsonObject todoObj;

private slots:
    void onSaveBtn();
    void onCancelBtn();
};

#endif // SUBWINDOW_H
