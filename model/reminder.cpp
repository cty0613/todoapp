#include "reminder.h"
#include <QApplication>
#include <QStyle>
#include <QDebug>

Reminder::Reminder(MainWindow& wnd, QObject *parent)
    : QObject(parent), rwToDo(new ToDo()),
    trayIcon(new QSystemTrayIcon(this)),
    timer(new QTimer(this)), wnd(wnd)
{

    QIcon icon(":/icon/data/DarkClock.png");
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("TODO LIST 알림");

    // 트레이 메뉴 구성
    trayMenu = new QMenu();
    showAction = new QAction("열기", this);
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

/*void Reminder::setReminder(ToDo* rwToDo)
{
    if(rwToDo != nullptr)
        this->rwToDo = rwToDo;
}*/

void Reminder::checkReminder()
{
    QJsonArray array = rwToDo->readToDoJSONAlarm(QDateTime::currentDateTime().addSecs(-1800), QDateTime::currentDateTime().addDays(1), "");

    //qDebug() << (array.size());

    if(!array.empty()){
        for(int i = 0; i < array.size(); i++){
            QJsonValue value = array.at(i);
            if(!value.isObject()) continue;

            QJsonObject obj = value.toObject();
            QDateTime target = QDateTime::fromString(obj.value("reminder").toString(), "yyyy-MM-dd hh:mm");

            if(target <= QDateTime::currentDateTime()
                && (!obj.value("reminded").toBool())
                && (!obj.value("complete").toBool())){

                //qDebug() << target.toString();
                //qDebug() << QDateTime::currentDateTime().toString();

                QString iconPath = obj.value("iconPath").toString();
                QFileInfo iconFile(iconPath);
                QIcon customIcon(iconPath);

                trayIcon->showMessage(
                    "ToDo App Alarm",
                    obj.value("title").toString(),
                    customIcon, //QSystemTrayIcon::Information,
                    10000
                    );

                qDebug() << "check";
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
    wnd.show();
}

void Reminder::onQuitApp()
{
    trayIcon->hide();
    QApplication::quit();
}
