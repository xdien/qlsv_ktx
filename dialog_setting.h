#ifndef DIALOG_SETTING_H
#define DIALOG_SETTING_H

#include <QDialog>
#include <QtSql>
#include <QSettings>

namespace Ui {
class Dialog_setting;
}

class Dialog_setting : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_setting(QWidget *parent = 0);
    ~Dialog_setting();
    QSqlDatabase diaDB;

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_toolButton_clicked();

private:
    QString host,user,pass,db,dir;
    void write_configXML(const QString fileName);
    Ui::Dialog_setting *ui;
};

#endif // DIALOG_SETTING_H
