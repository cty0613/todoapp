#ifndef SUBTODOWIDGET_H
#define SUBTODOWIDGET_H

#include <QWidget>

namespace Ui {
class SubTodoWidget;
}

class SubTodoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubTodoWidget(
        int id,
        int pid,
        bool completed,
        QString title = "",
        QString iconPath = ":/icon/data/Bookmark.png",
        QWidget *parent = nullptr);
    ~SubTodoWidget();

signals:
    void deleteBtnClicked(int todoId, int parnetId);
    void chkBtnClicked(int todoId);

private:
    Ui::SubTodoWidget *ui;
    int todoId;
    int parentId;

private slots:
    void onLineEdited(const QString &text);
    void onDeleteBtnClicked();
    void onChkBtnClicked();
};

#endif // SUBTODOWIDGET_H
