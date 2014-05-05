#ifndef DIALOG_SUADT_H
#define DIALOG_SUADT_H

#include <QDialog>
#include <QtSql>
#include <QTreeView>
#include <QKeyEvent>

namespace Ui {
class Dialog_suaDT;
}

class Dialog_suaDT : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_suaDT(QWidget *parent = 0);
    ~Dialog_suaDT();

private slots:
    void on_pushButton_add_clicked();
    void on_treeView_listsv_clicked(const QModelIndex &index);

    void on_pushButton_delete_clicked();

    void on_treeView_dt_clicked(const QModelIndex &index);
    void keyReleaseEvent(QKeyEvent *e);
private:
    QSqlQueryModel *model_dt;
    QSqlQueryModel *model_sv;
    QString luumssv,luumadt;
    QSqlQuery *newq;
    QTreeView *treeView;
    Ui::Dialog_suaDT *ui;
    QModelIndex idx;
    void loaddt(QString mssv);
};

#endif // DIALOG_SUADT_H
