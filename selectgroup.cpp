#include "selectgroup.h"
#include "ui_selectgroup.h"
#include "qdownloader.h"
#include "QtCore"
SelectGroup::SelectGroup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectGroup)
{
    setWindowTitle("Выбор группы");
    ui->setupUi(this);
    ui->listWidget->sortItems(Qt::AscendingOrder);
    loadFile("get_schem.json",(QUrl)"http://cist.nure.ua/ias/app/tt/get_faculties");

    QPixmap image(":/new/ico/ico/Trex2.png");
    ui->image->setPixmap(image);
    ui->image->setVisible(false);
}

SelectGroup::~SelectGroup()
{
    delete ui;
}

void SelectGroup::loadFile(QString filename,QUrl fileUrl)
{
    m_loaded=false;
    downloader = new QDownloader;
    connect(downloader,SIGNAL(fileCreated()),this,SLOT(fileLoaded()));
    connect(downloader,SIGNAL(loadError()),this,SLOT(loadError()));
    downloader->setFileName(filename);
    downloader->setUrl(fileUrl);
    downloader->startDownload();

}

void SelectGroup::fileLoaded()
{
    m_loaded=true;
   if(downloader->getFileName()=="get_schem.json")
      {
            loadList((QString)"get_schem.json",(QString)"faculties",(QString)"faculty_name");
            ui->backButton->setEnabled(false);
            ui->addButton->setEnabled(false);
       }
   else if(downloader->getFileName()=="get_groups.json")
   {
       loadList((QString)"get_groups.json",(QString)"groups",(QString)"group_name");
       ui->backButton->setEnabled(true);
   }
}

void SelectGroup::loadList(QString fileName,QString _docParce,QString _arrayParce)
{
    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        loadError();
        return;
    }
    jSonText = file.readAll();
    file.close();

    ui->listWidget->clear();

    QJsonDocument d = QJsonDocument::fromJson(jSonText.toUtf8());
    QJsonObject documentObject = d.object();

    QJsonArray array = documentObject[_docParce].toArray();
    for(QJsonArray::value_type it:array)
        ui->listWidget->addItem(it.toObject()[_arrayParce].toString().toStdString().c_str());

}


int SelectGroup::getID(QString typeName1,QString typeName2)
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

void SelectGroup::on_listWidget_doubleClicked()
{
    if(downloader->getFileName()=="get_schem.json")
    {
    QString faculties = ui->listWidget->currentItem()->text();
    QString url("http://cist.nure.ua/ias/app/tt/get_groups?faculty_id=");
    ui->listWidget->clear();


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
        close();
    }
}

void SelectGroup::on_listWidget_clicked()
{
    if(downloader->getFileName()=="get_groups.json")
        ui->addButton->setEnabled(true);
}

void SelectGroup::on_backButton_clicked()
{
    loadFile("get_schem.json",(QUrl)"http://cist.nure.ua/ias/app/tt/get_faculties");
}

void SelectGroup::on_addButton_clicked()
{
    on_listWidget_doubleClicked();
}

void SelectGroup::on_refreshButton_clicked()
{
    ui->image->setVisible(false);
    loadFile("get_schem.json",(QUrl)"http://cist.nure.ua/ias/app/tt/get_faculties");

}

void SelectGroup::loadError()
{

    ui->image->setVisible(true);
}

void SelectGroup::on_cancelButton_clicked()
{
    close();
}
