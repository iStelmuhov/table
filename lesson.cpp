#include "lesson.h"


int Lesson::type() const
{
    return m_type;
}

void Lesson::setType(int type)
{
    m_type = type;
}

QString Lesson::color()
{
    switch (m_type)
    {
    case -1:return "transparent";break;
    case 0:return "yellow";break;
    case 1:return "yellow";break;
    case 2:return "yellow";break;

    case 10:return "green";break;
    case 11:return "green";break;
    case 12:return "green";break;

    case 20: return "purple";break;
    case 21: return "purple";break;
    case 22: return "purple";break;
    case 23: return "purple";break;
    case 24: return "purple";break;

    case 30: return "white";break;
    case 31: return "white";break;

    case 40:return "brown";break;
    case 41:return "brown";break;

    case 50:return "dark blue";break;
    case 51:return "dark blue";break;
    case 52:return "dark blue";break;
    case 53:return "dark blue";break;
    case 54:return "dark blue";break;
    case 55:return "dark blue";break;
    default:return "red";
    }
}

QString Lesson::lessonStartEndTime()
{
    return m_startTime.time().toString("hh:mm")+" — " + m_endTime.time().toString("hh:mm");
}

Lesson::Lesson()
    :m_type(-1),m_groups(QList<QVariant>()),m_teachers(QList<Teacher>())
{
    
}

Lesson::Lesson(QString _brief, QString _title, QDateTime _start, QDateTime _end,
               QString _typeShort, QString _typeFull, int _type, int _number, QString _auditory,
               QList<QVariant> _groups, QList<Teacher> _teachers)
    :m_brief(_brief),m_title(_title),m_startTime(_start),m_endTime(_end),
      m_typeShort(_typeShort),m_typeFull(_typeFull),m_type(_type),m_number_pair(_number),m_auditory(_auditory),
      m_groups(_groups),m_teachers(_teachers)
{

}


QString Lesson::brief() const
{
    return m_brief;
}

void Lesson::setBrief(const QString &brief)
{
    m_brief = brief;
}

QString Lesson::title() const
{
    return m_title;
}

void Lesson::setTitle(const QString &title)
{
    m_title = title;
}

QDateTime Lesson::startTime() const
{
    return m_startTime;
}

void Lesson::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

QDateTime Lesson::endTime() const
{
    return m_endTime;
}

void Lesson::setEndTime(const QDateTime &endTime)
{
    m_endTime = endTime;
}

QString Lesson::typeShort() const
{
    return m_typeShort;
}

void Lesson::setTypeShort(const QString &typeShort)
{
    m_typeShort = typeShort;
}

QString Lesson::typeFull() const
{
    return m_typeFull;
}

void Lesson::setTypeFull(const QString &typeFull)
{
    m_typeFull = typeFull;
}

int Lesson::number_pair() const
{
    return m_number_pair;
}

void Lesson::setNumber_pair(int number_pair)
{
    m_number_pair = number_pair;
}

QString Lesson::auditory() const
{
    return m_auditory;
}

void Lesson::setAuditory(const QString &auditory)
{
    m_auditory = auditory;
}

QList<QVariant> Lesson::groups() const
{
    return m_groups;
}

void Lesson::setGroups(const QList<QVariant> &groups)
{
    m_groups = groups;
}

QList<Teacher> Lesson::teachers() const
{
    return m_teachers;
}

void Lesson::setTeachers(const QList<Teacher> &teachers)
{
    m_teachers = teachers;
}
