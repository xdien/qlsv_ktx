#include "tablemodel_sv.h"
//#include <QSqlRecord>
#include "mainwindow.h"
#include "dialog_chitietsv.h"
#include <QDebug>


tablemodel_sv::tablemodel_sv(QWidget *parent) :
    QTableView(parent)
{

    tableName = "SINH_VIEN";

    model = new QSqlTableModel();
    model->setTable(tableName);
    model->select();

    //set headerdata
    model->setHeaderData(0,Qt::Horizontal,"MSSV");
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Lớp"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Họ tên"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Số điện thoại"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Địa chỉ"));
    //model->database().transaction();//driver supported, lam cham va khong updata base;
    qDebug()<< model->lastError().text();
    this->setModel(model);
}


