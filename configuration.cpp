#include "configuration.h"

Configuration::Configuration(QString _fileName, GroupsData * _data, QObject *parent)
    : QObject(parent),m_fileName(_fileName),m_data(_data)
{

}

void Configuration::readFromFile()
{
    QFile file(m_fileName);

    if(file.open(QIODevice::ReadOnly))
    {
        QString jSonText=file.readAll();
        file.close();

        QJsonDocument doc=QJsonDocument::fromJson(jSonText.toUtf8());
        documentObject=doc.object();
    }
    else
    {
        qDebug()<<"Failed to open file!";
    }
}

void Configuration::loadInformationToGroupsData()
{
    if(!documentObject.isEmpty() && m_data!=nullptr)
    {
        QJsonArray arrayGroupsName=documentObject["groups"].toArray();
        for(auto it:arrayGroupsName)
            if(it.toObject()["id"].toInt()!=-1)
                emit newGroup(it.toObject()["name"].toString(),it.toObject()["id"].toInt(),false);
    }
}

void Configuration::writeToFile()
{
    QFile file(m_fileName);
    QJsonObject jSonWrite;
    if(file.open(QIODevice::WriteOnly))
    {
        QJsonArray groupsArray;
        for(auto it:m_data->gropsList())
           {
                QJsonObject groupObj;
                groupObj["name"]=it->name();
                groupObj["id"]=it->getId();
                groupsArray.append(groupObj);
            }
        jSonWrite["groups"]=groupsArray;
        QJsonDocument doc(jSonWrite);

        file.write(doc.toJson());
        file.close();
    }
}

