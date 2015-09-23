#include "groupbuilder.h"

GroupBuilder::GroupBuilder(QObject *parent)
    :QObject(parent),id(-1),loadFromInternet(false)
{
    QDate time(QDateTime::currentDateTime().date().year(),QDateTime::currentDateTime().date().month(),QDateTime::currentDateTime().date().day());
    time=time.addMonths(-6);

    for(int i=0;i<QDate::currentDate().daysInYear()+90;i++)
    {
        m_days[time]=new DayData(time);
        time=time.addDays(1);
     }
}

GroupBuilder::GroupBuilder(int group_id,QString group_name,bool internet,QObject *parent)
    : QObject(parent),id(group_id),name(group_name),loadFromInternet(internet)
{
    QDate time(QDateTime::currentDateTime().date().year(),QDateTime::currentDateTime().date().month(),QDateTime::currentDateTime().date().day());
    time=time.addMonths(-6);

    for(int i=0;i<QDate::currentDate().daysInYear()+90;i++)
    {
        m_days[time]=new DayData(time);
        time=time.addDays(1);
     }
}

GroupBuilder::~GroupBuilder(){

    delete downloader;
}

void GroupBuilder::getJSon()
{
    assert(id>=0 && !name.isEmpty());
    if(loadFromInternet)
        loadFileFromInternet();
    else
        fileLoaded();
}

void GroupBuilder::loadFileFromInternet()
{
    downloader = new QDownloader;
    connect(downloader,SIGNAL(fileCreated()),this,SLOT(fileLoaded()));
    downloader->setFileName(name+".json");
    downloader->setUrl("http://cist.nure.ua/ias/app/tt/P_API_EVENT_JSON?timetable_id="+QString::number(id));
    downloader->startDownload();
}


void GroupBuilder::fileLoaded()
{
    QFile file;
    file.setFileName(name+".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray  jSonText = file.readAll();
    file.close();

    QTextCodec *codec = QTextCodec::codecForName("windows-1251");
    QString utf8Str = codec->toUnicode(jSonText);

    QJsonDocument d = QJsonDocument::fromJson(utf8Str.toUtf8());
    documentObject = d.object();

    build();
}

void GroupBuilder::buildRequest(QString _name, int _id,bool internet)
{
    setName(_name);
    setId(_id);
    setLoadFromInternet(internet);
    getGroup();
}


QJsonValue findItem(QJsonArray &_array,QString whereFind,int id,QString whatFind)
{
    for(auto it:_array)
        if(it.toObject()[whereFind].toInt()==id)
               return it.toObject()[whatFind];

    return -1;
}

QJsonValue findItems(QJsonArray &_array,QString whereFind,QJsonArray id,QString whatFind)
{
    QJsonArray tmp;
    for(auto it:_array)
        for( auto it2:id)
            if(it.toObject()[whereFind].toInt()==it2.toInt())
               tmp.append(it.toObject()[whatFind]);

    return tmp;
}

QList<Teacher> findTeachers(QJsonArray &_array,QString whereFind,QJsonArray id,QString fullName,QString shortName)
{
    QList<Teacher> tmp;
    Teacher tmpT;
    for(auto it:_array)
        for( auto it2:id)
            if(it.toObject()[whereFind].toInt()==it2.toInt())
               {
                tmpT.full_name=it.toObject()[fullName].toString();
                tmpT.short_name=it.toObject()[shortName].toString();
                tmp.append(tmpT);
                }
    return tmp;
}

void GroupBuilder::build()
{

    QJsonArray arrayEvents = documentObject["events"].toArray();
    QJsonArray arrayGroups = documentObject["groups"].toArray();
    QJsonArray arrayTeachers= documentObject["teachers"].toArray();
    QJsonArray arraySubjects = documentObject["subjects"].toArray();
    QJsonArray arrayTypes = documentObject["types"].toArray();


    int max=INT_MIN,min=INT_MAX;

    for(QJsonArray::value_type it:arrayEvents)
    {
        if( it.toObject()["number_pair"].toInt()>max)
            max=it.toObject()["number_pair"].toInt();

        if(it.toObject()["number_pair"].toInt()<min)
            min=it.toObject()["number_pair"].toInt();
    }

    for(auto it:m_days)
    {
        int i=max-min+1;
        while (i!=0)
        {
            it->addLesson(new Lesson());
            i--;
        }
    }

    for(QJsonArray::value_type it:arrayEvents)
    {
        m_days[QDateTime::fromTime_t(it.toObject()["start_time"].toInt(),QTimeZone::systemTimeZone()).date()]->setLesson(new Lesson(
        findItem(arraySubjects,(QString)"id",it.toObject()["subject_id"].toInt(),(QString)"brief").toString(),
        findItem(arraySubjects,(QString)"id",it.toObject()["subject_id"].toInt(),(QString)"title").toString(),
        QDateTime::fromTime_t(it.toObject()["start_time"].toInt(),QTimeZone::systemTimeZone()),
        QDateTime::fromTime_t(it.toObject()["end_time"].toInt(),QTimeZone::systemTimeZone()),
        findItem(arrayTypes,(QString)"id",it.toObject()["type"].toInt(),(QString)"short_name").toString(),
        findItem(arrayTypes,(QString)"id",it.toObject()["type"].toInt(),(QString)"full_name").toString(),
        it.toObject()["type"].toInt(),
        it.toObject()["number_pair"].toInt(),
        it.toObject()["auditory"].toString(),
        findItems(arrayGroups,(QString)"id",it.toObject()["groups"].toArray(),(QString)"name").toVariant().toList(),
        findTeachers(arrayTeachers,(QString)"id",it.toObject()["teachers"].toArray(),(QString)"full_name",(QString)"short_name")
        ),it.toObject()["number_pair"].toInt()-min);
    }
    emit rePaint();
}

GroupYearData *GroupBuilder::getGroup()
{
    getJSon();

    resultGroup=new GroupYearData;
    assert(!m_days.isEmpty() && !name.isEmpty());

    for(auto it:m_days)
        resultGroup->addDate(it);

    resultGroup->setName(name.toUpper());
    resultGroup->setId(id);

    emit groupReady(resultGroup);
    return resultGroup;
}

bool GroupBuilder::getLoadFromInternet() const
{
    return loadFromInternet;
}

void GroupBuilder::setLoadFromInternet(bool value)
{
    loadFromInternet = value;
}

QString GroupBuilder::getName() const
{
    return name;
}

void GroupBuilder::setName(const QString &value)
{
    name = value;
}

int GroupBuilder::getId() const
{
    return id;
}

void GroupBuilder::setId(int value)
{
    id = value;
}


