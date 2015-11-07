#ifndef QMLSELECTGROUP_H
#define QMLSELECTGROUP_H

#include <QTCore>
#include <QFileDialog>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QFileInfo>
#include "qdownloader.h"
#include <QList>

class QmlSelectGroup
{
public:
    QmlSelectGroup();
    ~QmlSelectGroup();

    Q_PROPERTY(QList<QString> text READ text WRITE SetText NOTIFY textChanged)
    QList<QString> text() const;
    void setText(const QList<QString> &text);
    void loadData(QString fileName, QString _docParce, QString _arrayParce);
    int getID(QString typeName1,QString typeName2);
public slots:
    void loadList();
    void fileLoaded();
    void on_listView_doubleClicked();
private:
    QDownloader * downloader;
    QString jSonText;

    QList<QString> m_text;
    QString rootUrl;
signals:
    void textChanged();
    void groupSelected(QString,int);
};

#endif // QMLSELECTGROUP_H
