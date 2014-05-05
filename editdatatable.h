#ifndef EDITDATATABLE_H
#define EDITDATATABLE_H

#include <QDialog>
#include <QtSql>
#include <QKeyEvent>
#include <QMessageBox>

namespace Ui {
class editDatatable;
}

class editDatatable : public QDialog
{
    Q_OBJECT

public:
    explicit editDatatable(QWidget *parent, QString table_name);
    ~editDatatable();
    QSqlTableModel *model;
private slots:
    void on_pushButton_clicked();

private:
    void keyPressEvent(QKeyEvent *e);
    QMessageBox *thongbaoloi;
    Ui::editDatatable *ui;
};

#endif // EDITDATATABLE_H
