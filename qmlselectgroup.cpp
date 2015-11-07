#include "qmlselectgroup.h"

QmlSelectGroup::QmlSelectGroup()
    :rootUrl("http://cist.nure.ua/ias/app/tt")
{

}

QmlSelectGroup::~QmlSelectGroup()
{
    if(downloader!=NULL)
        delete downloader;
}
QList<QString> QmlSelectGroup::text() const
{
    return m_text;
}

void QmlSelectGroup::setText(const QList<QString> &text)
{
    m_text = text;
}



void QmlSelectGroup::loadList()
{
    downloader = new QDownloader;
    connect(downloader,SIGNAL(fileCreated()),this,SLOT(fileLoaded()));
    downloader->setFileName("get_schem.json");
    downloader->setUrl(rootUrl+"/get_faculties");
    downloader->startDownload();
}

void QmlSelectGroup::fileLoaded()
{
    if(downloader->getFileName()=="get_schem.json")
       {
             loadData((QString)"get_schem.json",(QString)"faculties",(QString)"faculty_name");
        }
    else if(downloader->getFileName()=="get_groups.json")
    {
        loadData((QString)"get_groups.json",(QString)"groups",(QString)"group_name");
    }
}




void QmlSelectGroup::loadData(QString fileName,QString _docParce,QString _arrayParce)
{
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    jSonText = file.readAll();
    file.close();

    m_text.clear();

    QJsonDocument d = QJsonDocument::fromJson(jSonText.toUtf8());
    QJsonObject documentObject = d.object();

    QJsonArray array = documentObject[_docParce].toArray();
    for(QJsonArray::value_type it:array)
        m_text.push_back(it.toObject()[_arrayParce].toString().toStdString().c_str());
}

int QmlSelectGroup::getID(QString typeName1, QString typeName2)
{
    QString selectedItem = ui->listWidget->currentItem()->text();
    QJsonDocument d = QJsonDocument::fromJson(jSonText.toUtf8());
    QJsonObject set = d.object();

    QJsonArray array = set[typeName1].toArray();

    for(QJsonArray::value_type it:array)
    {
        QString _item = it.toObject()[typeName2+"_name"].toString();
        if(_item==selectedItem)
            return it.toObject()[typeName2+"_id"].toInt();
    }
return -1;
}


void QmlSelectGroup::on_listView_doubleClicked()
{
    if(downloader->getFileName()=="get_schem.json")
    {
    QString faculties = ui->listWidget->currentItem()->text();
    QString url("http://cist.nure.ua/ias/app/tt/get_groups?faculty_id=");
    text.clear();


    QJsonDocument d = QJsonDocument::fromJson(jSonText.toUtf8());
    QJsonObject facultiesSet = d.object();

    QJsonArray array = facultiesSet["faculties"].toArray();

    for(QJsonArray::value_type it:array)
    {
        QString _fac = it.toObject()["faculty_name"].toString();
        if(_fac==faculties)
        {
            int fac_id=it.toObject()["faculty_id"].toInt();
            url.append(QString::number(fac_id));
        }
    }
     loadFile("get_groups.json",url);
    }
    else if(downloader->getFileName()=="get_groups.json")
    {
        emit groupSelected(ui->listWidget->currentItem()->text(),getID("groups","group"));
    }
}


