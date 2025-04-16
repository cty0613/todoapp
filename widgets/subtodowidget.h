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
    void titleChanged(QString changed, int todoId, int parentId );

private:
    Ui::SubTodoWidget *ui;
    int todoId;
    int parentId;
    bool textMod = false;

private slots:
    void onTextModified(const QString &text);
    void onLineEdited();
    void onDeleteBtnClicked();
    void onChkBtnClicked();
};

#endif // SUBTODOWIDGET_H
