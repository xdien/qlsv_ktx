#include "add_lop.h"
#include "ui_add_lop.h"

add_lop::add_lop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_lop)
{
    ui->setupUi(this);
}

add_lop::~add_lop()
{
    delete ui;
}
