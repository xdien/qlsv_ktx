#include "dialogform.h"
#include "ui_dialogform.h"
#include "dialog_chitietsv.h"

DialogForm::DialogForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogForm)
{
    ui->setupUi(this);
}

DialogForm::~DialogForm()
{
    delete ui;
}

void DialogForm::on_buttonBox_accepted()
{
    //tim kiem sinh vien va mo form moi
    QString mssv;
    mssv = ui->lineserch->text();
    Dialog_chitietSV dimoi(NULL,mssv);
    dimoi.exec();
}

