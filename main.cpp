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

int main(int argc, char *argv[])
{    
    QApplication app(argc, argv);
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:main.qml"));
    view.setIcon(QIcon(":/new/ico/ico/calendar-icons.png"));
    view.setTitle((QString)"TimeTable");
    GroupsData * Data = new GroupsData;
    SelectGroup * selectWindow=new SelectGroup;
    Data->addGroup(new GroupYearData());
    Data->setActive(0);
    QObject::connect(selectWindow,SIGNAL(groupSelected(QString,int)),Data,SLOT(newGroup(QString,int)));

    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("programmModel", Data);
    ctxt->setContextProperty("selectWindow", selectWindow);
    view.show();

    return app.exec();
}
