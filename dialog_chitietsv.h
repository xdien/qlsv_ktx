#ifndef DIALOG_CHITIETSV_H
#define DIALOG_CHITIETSV_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "math.h"

namespace Ui {
class Dialog_chitietSV;
}

class Dialog_chitietSV : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_chitietSV(QWidget *parent, QString st);
    ~Dialog_chitietSV();
    QString reciveString, temp,ma_ssv;
    int soluong;
    float giatri;
    QSqlQuery query;

    //them model
    QSqlQueryModel *querymodel, *querymodel1;
    void setvalue(QString st);
private slots:

private:
    Ui::Dialog_chitietSV *ui;
};

#endif // DIALOG_CHITIETSV_H
