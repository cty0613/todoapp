#ifndef CMDWIDGET_H
#define CMDWIDGET_H

#include <QWidget>

namespace Ui {
class CmdWidget;
}

class CmdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CmdWidget(QWidget *parent = nullptr);
    ~CmdWidget();

signals:
    void sendText(const QString &text); // 사용자 입력 텍스트를 전달하기 위한 시그널

private:
    Ui::CmdWidget *ui;

private slots:
    void onPushButtonClicked();  // pushButton 클릭 시 실행되는 슬롯
};

#endif // CMDWIDGET_H
