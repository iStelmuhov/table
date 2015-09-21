#ifndef GROUPSDATA_H
#define GROUPSDATA_H

#include <QObject>
#include "groupyeardata.h"
#include <QtCore>

class GroupBuilder;

class GroupsData : public QObject
{
    Q_OBJECT

private:
    QList<GroupYearData*> m_groups;
    GroupYearData * activeGroup;
    GroupBuilder * builder;
public:
    explicit GroupsData(QObject *parent = 0);

    Q_PROPERTY(QList<QObject*> gropsList READ listAsQObjects NOTIFY listChanged)
    const QList<GroupYearData*> &gropsList() const;
    QList<QObject*> listAsQObjects() const;

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    QString name() {return activeGroup->name();}

    Q_PROPERTY(GroupYearData * active READ active NOTIFY activeChanched)
    GroupYearData * active() {return activeGroup;}
    void setActive(int index);

    void addGroup(GroupYearData * _data) {m_groups.append(_data);}



    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    int index();


signals:
    void nameChanged();
    void activeChanched();
    void listChanged();
    void indexChanged();

public slots:
    void getNewIndex(int _index);
    void addNewGroup(GroupYearData * _group);
    void newGroup(QString,int);
    void deleteGroup(QString name);
    void deleteGroup(int _index);
};

#endif // GROUPSDATA_H
