#include "dialog_setting.h"
#include "ui_dialog_setting.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>


Dialog_setting::Dialog_setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_setting)
{
    ui->setupUi(this);
    QSettings loadSet("connect.conf",QSettings::IniFormat);
    loadSet.beginGroup("Default");//set group truoc khi dung
    //set value fro linedialog_*
    ui->linedialog_ip->setText(loadSet.value("ip").toString());
    ui->linedialog_user->setText(loadSet.value("user").toString());
    ui->linedialog_pass->setText(loadSet.value("pass").toString());
    ui->linedialog_db->setText(loadSet.value("db").toString());
}

Dialog_setting::~Dialog_setting()
{
    delete ui;
}

void Dialog_setting::on_pushButton_clicked()
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");//remove old connect
    diaDB = QSqlDatabase::addDatabase("QMYSQL");
    diaDB.setHostName(ui->linedialog_ip->text());
    diaDB.setDatabaseName(ui->linedialog_db->text());
    diaDB.setPassword(ui->linedialog_pass->text());
    diaDB.setUserName(ui->linedialog_user->text());
    if(diaDB.open())
    {
        QMessageBox n;
        n.setText("Ket noi thanh cong!!");
        n.exec();
    }
    else
    {
        qDebug()<<diaDB.lastError();
    }
    diaDB.close();
}

void Dialog_setting::on_buttonBox_accepted()
{
    QSettings settings("connect.conf",QSettings::IniFormat);
    settings.beginGroup("Default");
    settings.setValue("ip",ui->linedialog_ip->text());
    settings.setValue("user",ui->linedialog_user->text());
    settings.setValue("pass",ui->linedialog_pass->text());
    settings.setValue("db",ui->linedialog_db->text());
}
