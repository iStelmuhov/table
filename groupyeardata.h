#ifndef YEARDATA_H
#define YEARDATA_H

#include <QObject>
#include <QtCore>

class DayData;

class GroupYearData : public QObject
{
    Q_OBJECT

private:
    QList<DayData*> m_dates;
    QString groupName;

public:
    GroupYearData(QObject *parent = 0);
    GroupYearData(QString _name,QObject *parent = 0);

    Q_PROPERTY(QList<QObject*> list READ listAsQObjects NOTIFY listChanged)
    const QList<DayData*> &list() const;
    QList<QObject*> listAsQObjects() const;

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    int count() const {return m_dates.count();}

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    void setName(QString _name) {groupName=_name;}
    QString name() const {return groupName;}

    void addDate(DayData * _data) {m_dates.append(_data);}

    Q_PROPERTY(int getNumberMax READ getNumberMax NOTIFY getNumberMaxChanged)
    int getNumberMax();
    Q_PROPERTY(int getNumberMin READ getNumberMin NOTIFY getNumberMinChanged)
    int getNumberMin();

private:
    GroupYearData (const GroupYearData &);
    GroupYearData & operator = (const GroupYearData &);
signals:
    void listChanged();
    void countChanged();
    void nameChanged();
    void getNumberMinChanged();
    void getNumberMaxChanged();
public slots:
};

#endif // YEARDATA_H
