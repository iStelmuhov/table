#include "groupsdata.h"
#include "daydata.h"
#include "lesson.h"
#include "groupbuilder.h"

GroupsData::GroupsData(QObject *parent) :
    QObject(parent),m_groups(QList<GroupYearData*>()),activeGroup(nullptr),m_isUpading(false)
{

}

GroupsData::~GroupsData()
{
    for(auto it:m_groups)
        delete it;
}

const QList<GroupYearData *> &GroupsData::gropsList() const
{
    return m_groups;
}

QList<QObject *> GroupsData::listAsQObjects() const
{
    QList<QObject *> res;
    res.reserve(m_groups.count());
    for(auto i : m_groups)
       res.append(i);
    return res;
}

void GroupsData::setActive(int index)
{
     if(index>=0 && index<=m_groups.count())
        activeGroup=m_groups[index];

     emit activeChanched();
}

void GroupsData::deleteGroup(QString name)
{
    for(int i=0;i<m_groups.count();i++)
        if(m_groups[i]->name()==name)

        {
            if(activeGroup!=nullptr)
                if(activeGroup->name()==name)
                    setActive(0);

            QFile file;
            file.setFileName(name+".json");
            if(QFile::exists(file.fileName()))
                file.remove();

            delete m_groups[i];
            m_groups.removeAt(i);
            emit listChanged();
        }
}

void GroupsData::deleteGroup(int _index)
{
    if(_index>=0 && _index<=m_groups.count())
    {
        if(activeGroup->name()==m_groups.at(_index)->name())
           setActive(0);

        delete m_groups[_index];
        m_groups.removeAt(_index);
        emit listChanged();
    }
}

void GroupsData::updateGroup(QString name)
{
    for(int i=0;i<m_groups.count();i++)
        if(m_groups[i]->name()==name)
        {
            newGroup(m_groups[i]->name(),m_groups[i]->getId(),true);
            return;
        }
}

void GroupsData::rePaintList()
{
    emit activeChanched();
}

void GroupsData::update(QString _name, int _id)
{
    if(!m_isUpading){
    m_isUpading=true;
    builder=new GroupBuilder;
    connect(builder,SIGNAL(groupReady(GroupYearData*)),this,SLOT(addNewGroup(GroupYearData*)));
    connect(builder,SIGNAL(rePaint()),this,SLOT(rePaintList()));
    connect(builder,SIGNAL(downloadFullyComplete()),this,SLOT(changeStatus()));
    for(auto it:m_groups)
       if(_name.toUpper()==it->name())
            deleteGroup(it->name());

    builder->buildRequest(_name,_id);
    }
}



int GroupsData::index()
{
    if(activeGroup->list().isEmpty())
        return 0;

    QDate date=QDate::currentDate();

    for(int i=0;i<activeGroup->list().count();i++)
       if(activeGroup->list()[i]->dateTime()==date)
           return i;

    return 0;
}

int GroupsData::findGroup(QString name)
{
    for(int i=0;i<m_groups.count();i++)
        if(m_groups[i]->name()==name)
        {
            return i;
        }

    return -1;
}

void GroupsData::getNewIndex(int _index)
{
    setActive(_index);
}

void GroupsData::getNewIndex(QString name)
{
    getNewIndex(findGroup(name));
}

void GroupsData::addNewGroup(GroupYearData *_group)
{
    addGroup(_group);
    emit listChanged();
    emit groupLoaded();
}

void GroupsData::newGroup(QString _name, int _id, bool internet)
{
    for(auto it:m_groups)
       if(_name.toUpper()==it->name())
            return;

    builder=new GroupBuilder;
    connect(builder,SIGNAL(groupReady(GroupYearData*)),this,SLOT(addNewGroup(GroupYearData*)));
    connect(builder,SIGNAL(rePaint()),this,SLOT(rePaintList()));

    builder->buildRequest(_name,_id,internet);

}

void GroupsData::newGroupFromFile(QString _name)
{
    for(auto it:m_groups)
       if(_name.toUpper()==it->name())
            return;

    builder=new GroupBuilder;
    connect(builder,SIGNAL(groupReady(GroupYearData*)),this,SLOT(addNewGroup(GroupYearData*)));
    connect(builder,SIGNAL(rePaint()),this,SLOT(rePaintList()));

    builder->buildRequest(_name,-1,false);

}

void GroupsData::changeStatus()
{
    m_isUpading=false;
}
