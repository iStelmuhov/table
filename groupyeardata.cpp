#include "groupyeardata.h"
#include "DayData.h"

int GroupYearData::getId() const
{
    return m_id;
}

void GroupYearData::setId(int id)
{
    m_id = id;
}


GroupYearData::GroupYearData(QObject *parent) :
    QObject(parent), m_dates(QList<DayData*>()),m_id(-1)
{

}

GroupYearData::GroupYearData(QString _name, int _id, QObject *parent):
QObject(parent), m_dates(QList<DayData*>()),groupName(_name),m_id(_id)
{

}

const QList<DayData *> &GroupYearData::list() const
{
    return m_dates;
}

QList<QObject *> GroupYearData::listAsQObjects() const
{
    QList<QObject *> res;
    res.reserve(m_dates.count());
    for(auto i : m_dates)
       res.append(i);
    return res;
}

int GroupYearData::getNumberMax()
{
    int max=INT_MIN;
    for(auto it:m_dates)
       if(it->getNumberMax()>max && it->getNumberMax()<=15)
           max=it->getNumberMax();
    return max;
}

int GroupYearData::getNumberMin()
{
    int min=INT_MAX;
    for(auto it:m_dates)
       if(it->getNumberMin()<min && it->getNumberMin()>=0)
           min=it->getNumberMin();
    return min;
}
