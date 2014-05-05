#include "dialog_ctsv.h"
#include "ui_dialog_ctsv.h"

Dialog_CTSV::Dialog_CTSV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_CTSV)
{
    ui->setupUi(this);
}

Dialog_CTSV::~Dialog_CTSV()
{
    delete ui;
}
