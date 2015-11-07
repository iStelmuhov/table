#include "qdownloader.h"

QDownloader::QDownloader()
{

}

void QDownloader::setUrl(QUrl _url)
{
    url=_url;
}

void QDownloader::setFileName(QString _name)
{
    fileName=_name;
}

void QDownloader::startDownload()
{
    manager = new QNetworkAccessManager();

    QFileInfo fileInfo(url.path());


    if(fileName.isEmpty())
        fileName="index.html";
    if(QFile::exists(fileName))
    {
        qWarning()<<"File Exists";
        QFile::remove(fileName);
    }

    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly))
    {
        qWarning()<<"File not Open";
        delete file;
        file=0;
        return;
    }

    httpRequestAborted=false;
   startRequest();
}

void QDownloader::startRequest()
{
    reply=manager->get(QNetworkRequest(url));

   connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(downloadError(QNetworkReply::NetworkError)));
   connect(reply, SIGNAL(readyRead()),this, SLOT(httpReadyRead()));
   connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgressUpadte(qint64,qint64)));
   connect(reply, SIGNAL(finished()),this, SLOT(downloadFinished()));
}

void QDownloader::httpReadyRead()
{
    qDebug()<<"httpReadyRead";
    if(file)
        file->write(reply->readAll());
}

void QDownloader::downloadProgressUpadte(qint64 bytesRead, qint64 bytesTotal)
{
    qDebug()<<bytesRead<<" "<<bytesTotal;
    if(bytesRead==bytesTotal)
        emit downloadComplete();
    emit downloadProgress(bytesRead,bytesTotal);
}

void QDownloader::downloadFinished()
{
    if(httpRequestAborted)
    {
        if(file)
        {
            file->close();
            file->remove();
            delete file;
            file=0;
        }
        reply->deleteLater();
        return;
    }

    file->flush();
    file->close();

    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file->remove();
    }
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
    manager = 0;

    emit fileCreated();
}

void QDownloader::downloadError(QNetworkReply::NetworkError _err)
{
    emit loadError();
}

void QDownloader::cancelDownload()
{
    httpRequestAborted = true;
    reply->abort();

}
