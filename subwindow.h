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

    void updateSubList(bool initLoad);
    void connectWidgetsInLayout();
    void disconnectWidgetsInLayout();

private slots:

    void deleteSubTodo(const int &todoId, const int &parentId);
    void chkSubTodo(const int &todoId);
    void onSubTodoChanged(const int &todoId);

    void onSaveBtn();
    void onCancelBtn();
};

#endif // SUBWINDOW_H
