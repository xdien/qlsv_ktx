#include "tablemodlall.h"

tablemodlall::tablemodlall(QWidget *parent, QString table_name) :
    QTableView(parent)
{
    model = new QSqlTableModel();
    model->setTable(table_name);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->setModel(model);
}
