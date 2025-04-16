#ifndef REMINDER_H
#define REMINDER_H

#include "todo.h"
#include "../mainwindow.h"

#include <QObject>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QMenu>
#include <QDateTime>

class Reminder : public QObject
{
    Q_OBJECT

public:
    explicit Reminder(MainWindow& wnd, QObject *parent = nullptr);
    //void setReminder(ToDo* rwToDo);
    //void updateArray();

private slots:
    void checkReminder();
    void onShowReminderWindow();
    void onQuitApp();

private:
    QSystemTrayIcon *trayIcon;
    QTimer *timer;

    ToDo* rwToDo;
    MainWindow& wnd;

    QMenu *trayMenu;
    QAction *showAction;
    QAction *quitAction;
};

#endif // REMINDER_H
