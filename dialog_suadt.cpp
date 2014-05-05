#include "dialog_suadt.h"
#include "ui_dialog_suadt.h"
#include <QModelIndex>
Dialog_suaDT::Dialog_suaDT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_suaDT)
{
    ui->setupUi(this);
    model_dt = new QSqlQueryModel();
    model_sv = new QSqlQueryModel();
    model_sv->setQuery("select mssv as '"+QString::fromUtf8("MSSV")+"',ho_ten as '"+QString::fromUtf8("Họ tên")+"' from SINH_VIEN");
    ui->treeView_listsv->setModel(model_sv);
    newq = new QSqlQuery();
    newq->exec("select * from DOI_TUONG");
    while (newq->next()) {
        ui->comboBox_dt->addItem(newq->value(1).toString(),newq->value(0).toString());
    }
}

Dialog_suaDT::~Dialog_suaDT()
{
    delete ui;

}

void Dialog_suaDT::on_pushButton_add_clicked()
{
    newq->exec("insert into THUOC_DT values('"+luumssv+"','"+ui->comboBox_dt->itemData(ui->comboBox_dt->currentIndex()).toString()+"')");
    model_dt->submit();
    this->loaddt(luumssv);
}

void Dialog_suaDT::on_treeView_listsv_clicked(const QModelIndex &index)
{
   luumssv = ui->treeView_listsv->currentIndex().sibling(index.row(),0).data().toString();
   ui->lineEdit_hoten->setText(ui->treeView_listsv->currentIndex().sibling(index.row(),1).data().toString());
   this->loaddt(luumssv);
}

void Dialog_suaDT::loaddt(QString mssv)
{
    QString query;
    query = "select DOI_TUONG.ten_dt as '"+QString::fromUtf8("Thuộc đối tượng")+"', DOI_TUONG.ma_dt as '"+QString::fromUtf8("Mã đối tượng")+"' from SINH_VIEN " \
            "left join THUOC_DT " \
                "on SINH_VIEN.mssv = THUOC_DT.mssv " \
                "left join DOI_TUONG " \
                "on THUOC_DT.ma_dt = DOI_TUONG.ma_dt " \
            "where SINH_VIEN.mssv = '"+mssv+"'";
    model_dt->setQuery(query);
    ui->treeView_dt->setModel(model_dt);
}

void Dialog_suaDT::on_pushButton_delete_clicked()
{
    newq->exec("delete from THUOC_DT where mssv = '"+luumssv+"' and ma_dt = '"+luumadt+"'");
    loaddt(luumssv);
}

void Dialog_suaDT::on_treeView_dt_clicked(const QModelIndex &index)
{
    luumadt = ui->treeView_dt->currentIndex().sibling(index.row(),1).data().toString();
}
void Dialog_suaDT::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up || e->key()==Qt::Key_Down)
    {
    idx = ui->treeView_listsv->currentIndex();
    luumssv = ui->treeView_listsv->currentIndex().sibling(idx.row(),0).data().toString();
    ui->lineEdit_hoten->setText(ui->treeView_listsv->currentIndex().sibling(idx.row(),1).data().toString());
    this->loaddt(luumssv);
    }
}
