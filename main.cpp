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
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{    
    QApplication *app =new QApplication(argc, argv);
    app->setWindowIcon(QIcon(":/new/ico/ico/calendar-icons.png"));

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    GroupsData * Data = new GroupsData;
    Data->addGroup(new GroupYearData());
    Data->setActive(0);

    Configuration * conf = new Configuration((QString)"conf.json",Data);
    conf->readFromFile();
    QObject::connect(conf,SIGNAL(newGroup(QString,int,bool)),Data,SLOT(newGroup(QString,int,bool)));
    conf->loadInformationToGroupsData();

    SelectGroup * selectWindow=new SelectGroup;

    QObject::connect(selectWindow,SIGNAL(groupSelected(QString,int)),Data,SLOT(newGroup(QString,int)));

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("programmModel", Data);
    ctxt->setContextProperty("selectWindow", selectWindow);

    QObject::connect(app,SIGNAL(aboutToQuit()),conf,SLOT(writeToFile()));


    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                                 QObject::tr("I couldn't detect any system tray "
                                             "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    QObject *root = 0;
       if (engine.rootObjects().size() > 0)
       {
           root = engine.rootObjects().at(0);

           QAction *minimizeAction = new QAction(QObject::tr("Minimize"), root);
           root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
           QAction *maximizeAction = new QAction(QObject::tr("Maximize"), root);
           root->connect(maximizeAction, SIGNAL(triggered()), root, SLOT(showMaximized()));
           QAction *restoreAction = new QAction(QObject::tr("Restore"), root);
           root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(showNormal()));
           QAction *quitAction = new QAction(QObject::tr("Quit"), root);
           root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

           QMenu *trayIconMenu = new QMenu();
           trayIconMenu->addAction(minimizeAction);
           trayIconMenu->addAction(maximizeAction);
           trayIconMenu->addAction(restoreAction);
           trayIconMenu->addSeparator();
           trayIconMenu->addAction(quitAction);


           QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
           trayIcon->setContextMenu(trayIconMenu);
           trayIcon->setIcon(QIcon(":/new/ico/ico/calendar-icons.png"));
           trayIcon->show();
       }
    return app->exec();
}


