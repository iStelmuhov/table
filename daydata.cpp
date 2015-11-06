#include "daydata.h"
#include "lesson.h"


DayData::DayData(QObject *parent)
    :QObject(parent),
      m_lessons(QList<Lesson*>()),m_dateTime(QDate())
{

}

DayData::DayData(QDate _date,QObject* parent)
    :QObject(parent),
      m_lessons(QList<Lesson*>()),m_dateTime(_date)
{

}

DayData::~DayData()
{
    for(auto it:m_lessons)
        delete it;
}



const QList<Lesson *> &DayData::dayList() const
{
    return m_lessons;
}

QList<QObject *> DayData::listAsQObjects() const
{
    QList<QObject *> res;
    res.reserve(m_lessons.count());
    for(auto i : m_lessons)
       res.append(i);
    return res;
}

void DayData::setLesson(Lesson *_les, int pos)
{
   delete  m_lessons[pos];
   m_lessons[pos] = _les;
}

QDate DayData::dateTime() const
{
    return m_dateTime;
}

void DayData::setDateTime(const QDate &dateTime)
{
    m_dateTime = dateTime;
}

QString DayData::dateTimeString() const
{
    return m_dateTime.toString("dd.MM,dddd");
}

int DayData::getNumberMax()
{
    int max=INT_MIN;
    for(auto it:m_lessons)
       if(it->number_pair()>max && it->type()!=-1)
           max=it->number_pair();
    return max;
}

int DayData::getNumberMin()
{
    int min=INT_MAX;
    for(auto it:m_lessons)
       if(it->number_pair()<min && it->type()!=-1)
           min=it->number_pair();
    return min;
}
