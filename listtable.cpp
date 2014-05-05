#include "listtable.h"

listtable::listtable(QWidget *parent) :
    QTableView(parent)
{
    model = new QSqlQueryModel();
    model->setQuery("SELECT TABLE_NAME,TABLE_ROWS FROM INFORMATION_SCHEMA.TABLES where TABLE_SCHEMA = 'db_ktx'");
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("Tên bảng"));
    this->setModel(model);
}
