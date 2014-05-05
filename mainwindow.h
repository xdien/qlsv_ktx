#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QModelIndex>
/*Them tablemodel_sv*/
#include "listtable.h"
#include "tablemodel_sv.h"
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QSqlQuery *query;
    tablemodel_sv table1;
    listtable listmoi;
    QSqlQueryModel modelHopdong;
public slots:
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionThoat_triggered();

    void on_actionCai_dat_triggered();

    void on_comboxLop_tabHopdong_activated(int index);

    void on_actionTim_kiem_triggered();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *);

    void on_tableView_listtable_doubleClicked(const QModelIndex &index);

    void on_actionRefesh_triggered();

    void on_pushButton_3_clicked();

    void on_comboBox_tp_currentIndexChanged(int index);

    void on_comboBox_qh_currentIndexChanged(int index);

    void on_listView_sv_clicked(const QModelIndex &index);

    void on_action_i_t_ng_triggered();

    void on_pushButton_dlsv_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_comboxLop_tabHopdong_activated(const QString &arg1);

    void on_toolButton_clicked();

    void on_actionXemtheophong_triggered();

    void on_pushButton_4_clicked();

private:
    void loadpage();
    Ui::MainWindow *ui;
    QPixmap pix;
    QString tempst;
    QString tempst1,tempst2, linkimg, luumssv;
    QModelIndex clickidxSV;
    int tempint;
    QSqlQuery newq;
    QString thuocdiachi(QString nhapvao);
    QString gomdiachi(QComboBox *b1, QComboBox *b2, QComboBox *b3);
    //set combobox
    void setcombobox(QString madc);
    void loadtabSV(const QModelIndex &index);
};

#endif // MAINWINDOW_H
