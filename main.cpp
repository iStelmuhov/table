#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QtQuick>
#include "daydata.h"
#include "lesson.h"
#include "groupsdata.h"
#include <QDebug>
#include "selectgroup.h"
#include "groupbuilder.h"
#include "configuration.h"

int main(int argc, char *argv[])
{    
    QApplication *app =new QApplication(argc, argv);
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:main.qml"));
    view.setIcon(QIcon(":/new/ico/ico/calendar-icons.png"));
    view.setTitle((QString)"TimeTable");


    GroupsData * Data = new GroupsData;
    Data->addGroup(new GroupYearData());
    Data->setActive(0);

    Configuration * conf = new Configuration((QString)"conf.json",Data);
    conf->readFromFile();
    QObject::connect(conf,SIGNAL(newGroup(QString,int,bool)),Data,SLOT(newGroup(QString,int,bool)));
    conf->loadInformationToGroupsData();

    SelectGroup * selectWindow=new SelectGroup;

    QObject::connect(selectWindow,SIGNAL(groupSelected(QString,int)),Data,SLOT(newGroup(QString,int)));

    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("programmModel", Data);
    ctxt->setContextProperty("selectWindow", selectWindow);
    view.show();

    QObject::connect(app,SIGNAL(aboutToQuit()),conf,SLOT(writeToFile()));

    return app->exec();
}
