#ifndef TODOWIDGET_H
#define TODOWIDGET_H

#include <QWidget>

namespace Ui {
class TodoWidget;
}

class TodoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TodoWidget(
        int Id,
        QString title=" ",
        QString iconPath = ":/icon/data/Bookmark.png",
        QWidget *parent = nullptr);
    ~TodoWidget();

signals:
    void deleteBtnClicked(int todoId);
    void chkBtnClicked(int todoId);
    void editBtnClicked(int todoId);

private:
    Ui::TodoWidget *ui;
    int todoId;

private slots:
    void onDeleteBtnClicked();
    void onChkBtnClicked();
    void onEditBtnClicked();

};

#endif // TODOWIDGET_H
