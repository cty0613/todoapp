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
    explicit TodoWidget(QString title="Todo...", QWidget *parent = nullptr);
    ~TodoWidget();

private:
    Ui::TodoWidget *ui;


};

#endif // TODOWIDGET_H
