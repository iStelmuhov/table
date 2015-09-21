#ifndef SELECTGROUP_H
#define SELECTGROUP_H

#include <QMainWindow>
#include <QTCore>
#include <QMessageBox>
#include <QFileDialog>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QFileInfo>
#include "qdownloader.h"

namespace Ui {
class SelectGroup;
}

class SelectGroup : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectGroup(QWidget *parent = 0);
    ~SelectGroup();
    void loadList(QString fileName,QString _docParce,QString _arrayParce);

    void loadFile(QString filename,QUrl fileUrl);
private slots:
    void fileLoaded();
    void on_listWidget_doubleClicked();

    void on_listWidget_clicked();

    void on_backButton_clicked();

    void on_addButton_clicked();

signals:
    void groupSelected(QString,int);
private:
    Ui::SelectGroup *ui;
    QDownloader * downloader;
    QString jSonText;

    void loadFile();
    int getID(QString typeName1,QString typeName2);
};

#endif // SELECTGROUP_H
