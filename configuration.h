#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QtCore>
#include "groupsdata.h"
#include "groupyeardata.h"
#include "daydata.h"

class Configuration : public QObject
{
    Q_OBJECT

private:
    QString m_fileName;
    GroupsData * m_data;
    QJsonObject documentObject;
public:
    explicit Configuration(QString _fileName,GroupsData * _data,QObject *parent = 0);

    void readFromFile();
    void loadInformationToGroupsData();

signals:
    void newGroup(QString,int,bool);
public slots:
    void writeToFile();

};

#endif // CONFIGURATION_H
