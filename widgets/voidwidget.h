#ifndef VOIDWIDGET_H
#define VOIDWIDGET_H

#include <QWidget>

namespace Ui {
class VoidWidget;
}

class VoidWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VoidWidget(QWidget *parent = nullptr);
    ~VoidWidget();

private:
    Ui::VoidWidget *ui;
};

#endif // VOIDWIDGET_H
