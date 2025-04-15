#ifndef TODO_H
#define TODO_H

#include <QObject>

#include <QVector>
#include <QString>

#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class ToDo : public QObject
{
    Q_OBJECT

private:

    const QString JSONDATAPATH =
        QCoreApplication::applicationDirPath() + "/data/todo.json";
    int id;
    static int defaultId;
    QString title;
    bool complete{false};
    QString iconPath{""};
    QDateTime date;                 //converted into string before createJSONFILE
    QDateTime reminder;
    bool reminded{false};
    QString detail{""};
    int parentTask = -1;            //-1 for no parent
    QVector<int> subTasks;          // subtask id stored

public:
    explicit ToDo(QObject *parent = nullptr);
    ToDo(int id);
    ToDo(QString title,
         QString detail = "", QDateTime date = QDateTime::currentDateTime());
    ToDo(QJsonObject& obj);


    /*setter and getter*/
    int Id() const;
    void setId(int newId);

    QString Title() const;
    void setTitle(const QString &newTitle);

    QDateTime Date() const;
    void setDate(const QDateTime &newDate);

    bool Complete() const;
    void toggleComplete();

    QDateTime Reminder() const;
    void setReminder(const QDateTime &newReminder);

    bool Reminded();
    void toggleReminded();

    QString Detail() const;
    void setDetail(const QString &newDetail);

    int ParentTask() const;
    void setParentTask(int newParentTask);

    QVector<int> SubTasks() const;
    void setSubTasks(const QVector<int> &newSubTasks);
    void appendSubTasks(int id);

    void setDataUsingObj(QJsonObject& obj); //deep copy

    /*File CRUD*/
private:
    int duplicated(QJsonArray& arr, int id);
    void overwriteToDoJSONArray(QJsonArray& arr);
    void overwriteToDoJSONArray(QJsonArray& arr, int pos, QJsonObject& obj); //-1 for append
public:
    QJsonObject toDoJSONObj();

    /*create(insert)*/
    void insertToDoJSON();

    /*read, search*/
    QJsonArray readToDoJSON(); //default(all array)
    QJsonArray readToDoJSON(QDateTime from, QDateTime to, QString title);
    QJsonArray readToDoJSONAlarm(QDateTime from, QDateTime to, QString title); //for alarm
    /*update*/
    void updateToDoJSON();

    /*delete*/
private:
    void deleteToDoJSON(QJsonArray& array, int id);
public:
    void deleteToDoJSON(QString title);
    void deleteToDoJSON(QDateTime from, QDateTime to, QString title);

    /*SubTask*/
    void addSubTasksToToDoJSON(ToDo& todo); //all contents must be added except parentTask, subTasks

signals:
    //later connect
};


QJsonArray sortJSONByDate(QJsonArray& array);

#endif // TODO_H
