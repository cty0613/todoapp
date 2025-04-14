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
    QString detail{""};
    int parentTask = -1;            //-1 for no parent
    QVector<int> subTasks;          // subtask id stored

public:
    explicit ToDo(QObject *parent = nullptr);
    ToDo(int id);
    ToDo(QString title, QDateTime date, QString detail);

    /*setter and getter*/
    int Id() const;
    void setId(int newId);

    QString Title() const;
    void setTitle(const QString &newTitle);

    bool Complete() const;
    void toggleComplete();

    QDateTime Reminder() const;
    void setReminder(const QDateTime &newReminder);

    QString Detail() const;
    void setDetail(const QString &newDetail);

    QVector<int> SubTasks() const;
    void setSubTasks(const QVector<int> &newSubTasks);

    int ParentTask() const;
    void setParentTask(int newParentTask);

    /*File CRUD*/
private:
    QJsonObject toDoJSONObj();
    int duplicated(QJsonArray& arr, int id);
public:
    /*create(insert)*/
    void insertToDoJSON();

    /*read, search*/
    QJsonArray readToDoJSON(); //default(all array)
    QJsonArray readToDoJSON(QString title, QDateTime from, QDateTime to);//(title, period)

    /*update*/
    void updateToDoJSON();

    /*delete*/
    void deleteToDoJSON(QString title);

signals:
    //later connect
};

#endif // TODO_H
