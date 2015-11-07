#ifndef GROUPBUILDER_H
#define GROUPBUILDER_H

#include <QObject>
#include <QtCore>
#include <QDateTime>
#include <QVector>
#include "daydata.h"
#include "groupsdata.h"
#include "groupyeardata.h"
#include "lesson.h"
#include "qdownloader.h"
#include <cassert>


class GroupBuilder : public QObject
{
    Q_OBJECT

private:
    int id;
    QString name;
    QJsonObject documentObject;
    QDownloader * downloader;
    bool loadFromInternet;

    GroupYearData * resultGroup;
    QMap<QDate,DayData *> m_days;


public:
    GroupBuilder(QObject *parent=0);
    explicit GroupBuilder(int group_id,QString group_name,bool internet,QObject *parent = 0);
    ~GroupBuilder();

    GroupYearData *getGroup();
    void getJSon();

    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);
    QDownloader *getDownloader() const;
    void setDownloader(QDownloader *value);

protected:

    void build();

    void loadFileFromInternet();

    bool getLoadFromInternet() const;
    void setLoadFromInternet(bool value);

signals:
    void jSonReady();
    void groupReady(GroupYearData * group);
    void rePaint();
    void downloadFullyComplete();
public slots:
    void fileLoaded();
    void buildRequest(QString _name, int _id, bool internet=true);
    void loadFullyComplete();

};

#endif // GROUPBUILDER_H
