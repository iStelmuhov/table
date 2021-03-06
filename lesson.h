#ifndef LESSON_H
#define LESSON_H


#include <QtCore>
#include <QColor>

struct Teacher{
    QString full_name;
    QString short_name;
};

class Lesson:public QObject
{
     Q_OBJECT

private:
    QString m_brief;
    QString m_title;

    QDateTime m_startTime;
    QDateTime m_endTime;

    QString m_typeShort;
    QString m_typeFull;
    int m_type;

    int m_number_pair;
    QString m_auditory;

    QList<QVariant> m_groups;
    QList<Teacher> m_teachers;

public:
    Lesson();
    Lesson(QString _brief,QString _title,QDateTime _start,QDateTime _end,
           QString _typeShort,QString _typeFull,int _type,
           int _number,QString _auditory,
           QList<QVariant> _groups,QList<Teacher> _teachers);

    Q_PROPERTY(QString brief READ brief WRITE setBrief NOTIFY briefChanged)
    QString brief() const;
    void setBrief(const QString &brief);

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    QString title() const;
    void setTitle(const QString &title);

    Q_PROPERTY(QDateTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    QDateTime startTime() const;
    void setStartTime(const QDateTime &startTime);

    Q_PROPERTY(QDateTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
    QDateTime endTime() const;
    void setEndTime(const QDateTime &endTime);

    Q_PROPERTY(QString typeShort READ typeShort WRITE setTypeShort NOTIFY typeShortChanged)
    QString typeShort() const;
    void setTypeShort(const QString &typeShort);

    Q_PROPERTY(QString typeFull READ typeFull WRITE setTypeFull NOTIFY typeFullChanged)
    QString typeFull() const;
    void setTypeFull(const QString &typeFull);

    Q_PROPERTY(int number_pair READ number_pair WRITE setNumber_pair NOTIFY number_pairChanged)
    int number_pair() const;
    void setNumber_pair(int number_pair);

    Q_PROPERTY(QString auditory READ auditory WRITE setAuditory NOTIFY auditoryChanged)
    QString auditory() const;
    void setAuditory(const QString &auditory);

    Q_PROPERTY(QList<QVariant> groups READ groups WRITE setGroups NOTIFY groupsChanged)
    QList<QVariant> groups() const;
    void setGroups(const QList<QVariant> &groups);

    Q_PROPERTY(QList<Teacher> teachers READ teachers WRITE setTeachers NOTIFY teachersChanged)
    QList<Teacher> teachers() const;
    void setTeachers(const QList<Teacher> &teachers);

    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    int type() const;
    void setType(int type);

    Q_PROPERTY(QString color READ color NOTIFY colorChanged)
    QString color();

    Q_PROPERTY(QString lessonStartEndTime READ lessonStartEndTime NOTIFY lessonStartEndTimeChanged)
    QString lessonStartEndTime();

    Q_PROPERTY(QString teachersToString READ teachersToString NOTIFY teachersToStringChanged)
    QString teachersToString();

    Q_PROPERTY(QString groupsToString READ groupsToString NOTIFY groupsToStringChanged)
    QString groupsToString();

signals:
    void briefChanged();
    void titleChanged();
    void startTimeChanged();
    void endTimeChanged();
    void typeShortChanged();
    void typeFullChanged();
    void number_pairChanged();
    void auditoryChanged();
    void groupsChanged();
    void teachersChanged();
    void typeChanged();
    void colorChanged();
    void lessonStartEndTimeChanged();
    void teachersToStringChanged();
    void groupsToStringChanged();
};

#endif // LESSON_H
