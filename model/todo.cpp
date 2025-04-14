#include "todo.h"

/*QJsonArray -> QJsonObject*/

/*literally for debug - comment it when release mode*/
#define DEBUG_MODE
#ifdef DEBUG_MODE
#include <QDebug>
void Debug(QString str){
    qDebug() << str;
}
/*
#ifdef DEBUG_MODE
Debug(str)
#endif
*/
#endif

int ToDo::defaultId = 0;

ToDo::ToDo(QObject *parent)
    : QObject{parent}
{
    id = defaultId++;
}

ToDo::ToDo(int id) : id{id}{
    //id를 이용하여 맴버 채우기
}

ToDo::ToDo(QString title,
           QDateTime date = QDateTime::currentDateTime(), QString detail = "")
    : title{title}, date{date}, detail{detail}
{
    if(title.length() == 0)
        title = "";
    id = defaultId++;
}

/*public function*/
/*getter and setter*/
int ToDo::Id() const
{
    return id;
}
void ToDo::setId(int newId)
{
    id = newId;
}

QString ToDo::Title() const
{
    return title;
}
void ToDo::setTitle(const QString &newTitle)
{
    title = newTitle;
}


bool ToDo::Complete() const
{
    return complete;
}
void ToDo::toggleComplete()
{
    complete = ~complete;
}

QDateTime ToDo::Reminder() const
{
    return reminder;
}
void ToDo::setReminder(const QDateTime &newReminder)
{
    reminder = newReminder;
}

QString ToDo::Detail() const
{
    return detail;
}
void ToDo::setDetail(const QString &newDetail)
{
    detail = newDetail;
}

int ToDo::ParentTask() const
{
    return parentTask;
}
void ToDo::setParentTask(int newParentTask)
{
    parentTask = newParentTask;
}

QVector<int> ToDo::SubTasks() const
{
    return subTasks;
}
void ToDo::setSubTasks(const QVector<int> &newSubTasks)
{
    subTasks = newSubTasks;
}

/*JSON File CRUD*/
/*return JSONObj*/
QJsonObject ToDo::toDoJSONObj(){
    QJsonObject obj;

    obj["id"] = id;
    obj["title"] = title;
    obj["complete"] = complete;
    obj["iconPath"] = iconPath;
    obj["date"] = date.toString("yyyy:MM:dd:HH:mm");
    obj["reminder"] = reminder.toString("yyyy:MM:dd:HH:mm");
    obj["detail"] = detail;
    obj["parentTask"] = parentTask;

    QJsonArray sub;
    for(auto id : subTasks){
        sub.append(id);
    }
    obj["subTasks"] = sub;

    return obj;
}

/*JSON File Insert*/
void ToDo::insertToDoJSON()
{
    /*
     * Open JSON File
     * Add new todo list - json form
     * write on the json file
     * close json file
     * duplicated 함수 만들 것, 파일을 읽어들이는 함수는 별도로 만들 것(완), 갱신하는 것도 별도로 만들 것
     */

    QJsonArray todolist = readToDoJSON();
}

/*JSON File Read*/
QJsonArray ToDo::readToDoJSON(){
    QFile file(JSONDATAPATH);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Append)){
        qWarning() << "파일이 존재하지 않습니다:" << file.errorString();
        return QJsonArray();
    }
    QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(fileData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON 파싱 오류:" << parseError.errorString();
        return QJsonArray();
    }
    if (!doc.isObject()) {
        qWarning() << "JSON 최상위 객체가 Object가 아닙니다.";
        return QJsonArray();
    }

    return doc.array();
}

QJsonArray ToDo::readToDoJSON(QString title, QDateTime from, QDateTime to){
    return QJsonArray();
}

/*JSON File Update*/
void ToDo::updateToDoJSON()
{
    /*
     * Open JSON File
     * Get JSONArray Object
     * Find JSONObj using id
     */
}

/*JSON File Delete*/
void ToDo::deleteToDoJSON(QString title)
{

}

