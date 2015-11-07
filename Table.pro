TEMPLATE = app

QT += qml quick network widgets

SOURCES += main.cpp \
    daydata.cpp \
    groupbuilder.cpp \
    groupsdata.cpp \
    groupyeardata.cpp \
    lesson.cpp \
    qdownloader.cpp \
    selectgroup.cpp \
    configuration.cpp

RESOURCES += qml.qrc \
    res.qrc

CONFIG +=c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    daydata.h \
    groupbuilder.h \
    groupsdata.h \
    groupyeardata.h \
    lesson.h \
    qdownloader.h \
    selectgroup.h \
    configuration.h

FORMS += \
    selectgroup.ui

DISTFILES +=
