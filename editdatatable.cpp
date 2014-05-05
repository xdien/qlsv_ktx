#include "editdatatable.h"
#include "ui_editdatatable.h"
#include <QModelIndex>


editDatatable::editDatatable(QWidget *parent, QString table_name) :
    QDialog(parent),
    ui(new Ui::editDatatable)
{
    ui->setupUi(this);
    model = new QSqlTableModel();
    model->setTable(table_name);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->database().transaction();//dung che do manualsubmit
    model->select();
    ui->tableView->setModel(model);
}

editDatatable::~editDatatable()
{
    delete ui;
}


/*xu ly cac su kien khi an nut*/
void editDatatable::keyPressEvent(QKeyEvent *e)
{
    if(e->matches(QKeySequence::Italic))
    {
        int rowCount;
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
         rowCount = model->rowCount();
         if(!model->insertRow(rowCount))
         {
             qDebug()<<"Inserows for recoder table: "<<model->lastError().text();
         }
         else
         {
             ui->tableView->selectRow(rowCount);
         }
    }
    if(e->matches(QKeySequence::Delete))
    {
        QModelIndex curent;
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        curent = ui->tableView->currentIndex();
        model->removeRow(curent.row());
        model->submit();
        model->database().transaction();
    }
    if(e->matches(QKeySequence::Save))
    {
        if(model->submitAll())
            model->database().commit();
        else
        {

            thongbaoloi = new QMessageBox;
            thongbaoloi->setText(QString::fromUtf8("Hãy kiểm tra lỗi! \n") + model->lastError().text());
            thongbaoloi->exec();
            model->select();
        }
    }
}

void editDatatable::on_pushButton_clicked()
{
    if(model->submitAll())
    {
        model->database().commit();
    }
    else
    {
        thongbaoloi = new QMessageBox;
        thongbaoloi->setText(QString::fromUtf8("Hãy kiểm tra lỗi! \n") + model->lastError().text());
        thongbaoloi->exec();
        model->select();
    }
}
