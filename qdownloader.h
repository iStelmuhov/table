#ifndef QDOWNLOADER_H
#define QDOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtCore>
#include <QUrl>
#include <QDebug>


class QDownloader
        :public QObject
{
    Q_OBJECT
public:
    QDownloader();
    void setUrl(QUrl _url);
    void setFileName(QString _name);
    void startDownload();
    void cancelDownload();
    QString getFileName() {return fileName;}
    QUrl getUrl(){return url;}

private slots:
    void httpReadyRead();
    void downloadProgressUpadte(qint64, qint64);
    void downloadFinished();
    void downloadError(QNetworkReply::NetworkError);
signals:
    void downloadProgress(qint64,qint64);
    void fileCreated();
    void loadError();
    void downloadComplete();
private:
    QUrl url;
    QNetworkAccessManager * manager;
    QNetworkReply * reply;
    QFile *file;
    QString fileName;
    bool httpRequestAborted;

    void startRequest();

};

#endif // QDOWNLOADER_H
