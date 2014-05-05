#ifndef FORM_LISTSTBYPHONG_H
#define FORM_LISTSTBYPHONG_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class Form_listSTbyPhong;
}

class Form_listSTbyPhong : public QWidget
{
    Q_OBJECT

public:
    explicit Form_listSTbyPhong(QWidget *parent = 0);
    ~Form_listSTbyPhong();
    QSqlQueryModel *listsv;
private slots:
    void on_treeView_phong_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::Form_listSTbyPhong *ui;

    QSqlQueryModel *querymodel_room;
};

#endif // FORM_LISTSTBYPHONG_H
