#ifndef DAYDATA_H
#define DAYDATA_H

#include <QDate>
#include <QtCore>
#include <QDateTime>

class Lesson;

class DayData : public QObject
{
    Q_OBJECT

private:
    QList<Lesson*> m_lessons;
    QDate m_dateTime;

public:
    DayData(QObject * parent =0);
    DayData(QDate _date,QObject* parent = 0);

    Q_PROPERTY(QList<QObject*> dayList READ listAsQObjects NOTIFY listChanged)
    const QList<Lesson*> &dayList() const;
    QList<QObject*> listAsQObjects() const;

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    int count() const {return m_lessons.count();}

    void addLesson(Lesson * _les) {m_lessons.append(_les);}
    void setLesson(Lesson * _les,int pos);

    Q_PROPERTY(QDate dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    QDate dateTime() const;
    void setDateTime(const QDate &dateTime);

    int getNumberMax();
    int getNumberMin();
signals:
    void listChanged();
    void countChanged();
    void dateTimeChanged();
public slots:
};

#endif // DAYDATA_H
