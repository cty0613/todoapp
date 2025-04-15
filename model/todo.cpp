#include "todo.h"

int ToDo::defaultId = 0;

ToDo::ToDo(QObject *parent)
    : QObject{parent}
{
    id = defaultId++;
}

ToDo::ToDo(int id) : id{id}{
    //id를 이용하여 맴버 채우기
    //reading하는 용도로 선언, 다른 용도인 경우 id를 직접 선언하지 말 것
}

ToDo::ToDo(QString title, QString detail, QDateTime date)
    : title{title}, date{date}, detail{detail}
{
    if(title.length() == 0)
        title = "";
    id = defaultId++;
}

ToDo::ToDo(QJsonObject& obj){
    setDataUsingObj(obj);
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

QDateTime ToDo::Date() const
{
    return date;
}

void ToDo::setDate(const QDateTime &newDate)
{
    date = newDate;
}

bool ToDo::Complete() const
{
    return complete;
}
void ToDo::toggleComplete()
{
    complete = !complete;
}

QDateTime ToDo::Reminder() const
{
    return reminder;
}
void ToDo::setReminder(const QDateTime &newReminder)
{
    reminder = newReminder;
}

bool ToDo::Reminded(){
    return reminded;
}
void ToDo::toggleReminded(){
    reminded = !reminded;
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
void ToDo::appendSubTasks(int id){
    this->subTasks.append(id);
}

void ToDo::setDataUsingObj(QJsonObject& obj){
    id = obj.value("id").toInt();
    title = obj.value("title").toString();
    complete = obj.value("complete").toBool();
    iconPath = obj.value("iconPath").toString();
    date = QDateTime::fromString(obj.value("date").toString(), "yyyy:MM:dd");
    reminder = QDateTime::fromString(obj.value("reminder").toString(), "yyyy:MM:dd:hh:mm");
    reminded = obj.value("reminded").toBool();
    detail = obj.value("detail").toString();
    parentTask = obj.value("parentTask").toInt();

    QVector<int> vec;
    QJsonArray array = obj.value("subTasks").toArray();
    if(!array.empty()){
        for(int i = 0; i < array.size(); i++){
            QJsonValue value = array.at(i);
            vec.append(static_cast<int>(value.toInt()));
        }
    }
    subTasks = vec;
}

/*JSON File CRUD*/
/*return JSONObj*/
QJsonObject ToDo::toDoJSONObj(){
    QJsonObject obj;

    obj["id"] = id;
    obj["title"] = title;
    obj["complete"] = complete;
    obj["iconPath"] = iconPath;
    obj["date"] = date.toString("yyyy:MM:dd");
    obj["reminder"] = reminder.toString("yyyy:MM:dd:hh:mm");
    obj["reminded"] = reminded;
    obj["detail"] = detail;
    obj["parentTask"] = parentTask;

    QJsonArray sub;
    for(auto id : subTasks){
        sub.append(id);
    }
    obj["subTasks"] = sub;

    return obj;
}
int ToDo::duplicated(QJsonArray& arr, int id){
    int index = -1;

    for(int i = 0; i < arr.size(); i++){
        QJsonValue value = arr.at(i);
        if(!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        if(obj.value("id").toInt() == id)
            return i;
    }

    return -1;
}
void ToDo::overwriteToDoJSONArray(QJsonArray& arr){
    QJsonDocument newDoc(arr);

    QFile file(JSONDATAPATH);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "파일 열기 실패(쓰기):" << file.errorString();
        return;
    }

    file.write(newDoc.toJson());
    file.close();
}
void ToDo::overwriteToDoJSONArray(QJsonArray& arr, int pos, QJsonObject& obj){
    if(pos > -1)
        arr[pos] = obj;
    else
        arr.append(obj);

    overwriteToDoJSONArray(arr);
}

/*JSON File Insert*/
void ToDo::insertToDoJSON()
{
    QJsonArray array = readToDoJSON();

    int index = duplicated(array, id);

    QJsonObject newObj = toDoJSONObj();

    overwriteToDoJSONArray(array, index, newObj);
}

/*JSON File Read*/
QJsonArray ToDo::readToDoJSON(){

    QFile file(JSONDATAPATH);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "파일을 열 수 없습니다:" << file.errorString();
        return QJsonArray(); // 빈 배열 반환
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);

    //qDebug() << doc.toJson();

    return doc.array();
}

QJsonArray ToDo::readToDoJSON(QDateTime from, QDateTime to, QString title){

    QJsonArray wholeArray = readToDoJSON();
    QJsonArray wantedArray;

    // 시간 정규화
    from.setTime(QTime(0, 0, 0));
    to.setTime(QTime(23, 59, 59));

    for (const QJsonValue &value : wholeArray) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        QString dateStr = obj.value("date").toString();
        QDateTime dt = QDateTime::fromString(dateStr, "yyyy:MM:dd");

        if (!dt.isValid()) {
            qWarning() << "Invalid date format:" << dateStr;
            continue;
        }

        if ((from <= dt) && (dt <= to)) {
            if (!title.isEmpty()) {
                if (obj.value("title").toString() == title)
                    wantedArray.append(obj);
            } else {
                wantedArray.append(obj);
            }
        }
    }

    return wantedArray;
}

QJsonArray ToDo::readToDoJSONAlarm(QDateTime from, QDateTime to, QString title)
{
    QJsonArray wholeArray = readToDoJSON();
    QJsonArray wantedArray;

    for (const QJsonValue &value : wholeArray) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        QString dateStr = obj.value("reminder").toString();
        QDateTime dt = QDateTime::fromString(dateStr, "yyyy:MM:dd:hh:mm");

        if (!dt.isValid()) {
            qWarning() << "Invalid date format:" << dateStr;
            continue;
        }

        if ((from <= dt) && (dt <= to)) {
            if (!title.isEmpty()) {
                if (obj.value("title").toString() == title)
                    wantedArray.append(obj);
            } else {
                wantedArray.append(obj);
            }
        }
    }

    return wantedArray;
}

/*JSON File Update*/
void ToDo::updateToDoJSON()
{
    QJsonArray array = readToDoJSON();

    int index = duplicated(array, id);

    QJsonObject newObj = toDoJSONObj();
    overwriteToDoJSONArray(array, index, newObj);
}

/*JSON File Delete*/
void ToDo::deleteToDoJSON(QJsonArray& array, int id){

    for (int i = array.size() - 1; i >= 0; --i) {
        QJsonValue val = array.at(i);
        if (val.isObject()) {
            QJsonObject obj = val.toObject();
            if (obj.contains("id") && obj.value("id").toInt() == id) {

                //subtask 삭제
                if(obj.contains("subTasks")){
                    QJsonArray subArr = obj.value("subTasks").toArray();
                    if(!subArr.isEmpty()){
                        for(int j = 0; j < subArr.size(); j++){
                            QJsonValue subval = subArr.at(i);
                            if(subval.isObject()){
                                QJsonObject subobj = subval.toObject();
                                deleteToDoJSON(array, subobj.value("id").toInt());
                            }
                        }
                    }
                }

                array.removeAt(i);
            }
        }
    }
}

void ToDo::deleteToDoJSON(QString title)
{
    QJsonArray array = readToDoJSON();

    for (int i = array.size() - 1; i >= 0; --i) {
        QJsonValue val = array.at(i);
        if (val.isObject()) {
            QJsonObject obj = val.toObject();
            if (obj.contains("title") && obj.value("title") == "title") {
                deleteToDoJSON(array, obj.value("id").toInt());
            }
        }
    }

    overwriteToDoJSONArray(array);
}

void ToDo::deleteToDoJSON(QDateTime from, QDateTime to, QString title)
{
    QJsonArray array = readToDoJSON();

    for (int i = array.size() - 1; i >= 0; --i) {
        QJsonValue val = array.at(i);
        if (val.isObject()) {

            QJsonObject obj = val.toObject();
            QString dateStr = obj.value("date").toString();
            QDateTime dt = QDateTime::fromString(dateStr, "yyyy:MM:dd");

            // 시간 정규화
            from.setTime(QTime(0, 0, 0));
            to.setTime(QTime(23, 59, 59));

            if( (from <= dt) && (dt <= to) &&(!obj.value("reminded").toBool())){
                if(title.length() > 0){
                    if(obj.value("title") == title){
                        deleteToDoJSON(array, obj.value("id").toInt());
                    }
                }
                else{
                    deleteToDoJSON(array, obj.value("id").toInt());
                }
            }
        }
    }

    overwriteToDoJSONArray(array);
}

void ToDo::addSubTasksToToDoJSON(ToDo& todo){
    todo.setParentTask(this->Id());
    this->appendSubTasks(todo.Id());

    todo.insertToDoJSON();
}
