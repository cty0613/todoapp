#include "reminder.h"
#include <QApplication>
#include <QStyle>
#include <QDebug>

Reminder::Reminder(QObject *parent)
    : QObject(parent), rwToDo(nullptr),
    trayIcon(new QSystemTrayIcon(this)),
    timer(new QTimer(this))
{
    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("TODO LIST 알림");

    // 트레이 메뉴 구성
    trayMenu = new QMenu();
    showAction = new QAction("정보", this);
    quitAction = new QAction("종료", this);
    trayMenu->addAction(showAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    connect(showAction, &QAction::triggered, this, &Reminder::onShowReminderWindow);
    connect(quitAction, &QAction::triggered, this, &Reminder::onQuitApp);
    connect(timer, &QTimer::timeout, this, &Reminder::checkReminder);

    timer->start(1000);
}

void Reminder::setReminder(ToDo* rwToDo)
{
    if(rwToDo != nullptr)
        this->rwToDo = rwToDo;
}

void Reminder::checkReminder()
{
    QJsonArray array = rwToDo->readToDoJSONAlarm(QDateTime::currentDateTime().addDays(10),
                                            QDateTime::currentDateTime(), "");
    if(!array.empty()){
        for(int i = 0; i < array.size(); i++){
            QJsonValue value = array.at(i);
            if(!value.isObject()) continue;

            QJsonObject obj = value.toObject();
            QDateTime target = QDateTime::fromString(obj.value("reminder").toString(), "yyyy:MM:dd:HH:mm");
            if(target <= QDateTime::currentDateTime()){
                trayIcon->showMessage(
                    "ToDo App Alarm",
                    obj.value("title").toString(),
                    QSystemTrayIcon::Information,
                    10000
                );

                ToDo toUpdate(obj);
                toUpdate.toggleReminded();
                toUpdate.updateToDoJSON();
            }
        }

        // if (reminderSet && QDateTime::currentDateTime() >= targetTime) {
        //     qDebug() << "checked";
        //     trayIcon->showMessage(
        //         reminderTitle,
        //         reminderMessage,
        //         QSystemTrayIcon::Information,
        //         10000
        //         );
        //     reminderSet = false;
        // }
    }
}

void Reminder::onShowReminderWindow()
{
    trayIcon->showMessage("Reminder 상태", "트레이에서 실행 중입니다.");
}

void Reminder::onQuitApp()
{
    trayIcon->hide();
    QApplication::quit();
}
