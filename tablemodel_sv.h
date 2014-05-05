#ifndef TABLEMODEL_SV_H
#define TABLEMODEL_SV_H

#include <QTableView>
#include <QtSql>
#include <QSqlRecord>
#include <QKeyEvent>
 #include <QKeySequence> //dung cho so sanh cac key
#include <QMessageBox>
#include <QStyledItemDelegate>
#include "config_sqlconnect.h"


class tablemodel_sv : public QTableView
{
    Q_OBJECT
public:
    explicit tablemodel_sv(QWidget *parent = 0);
    QSqlTableModel *model;
    QString tableName;
    int rowCount;
    QSqlRecord rec; //bien chung cho bang them du lieu moi

signals:
public slots:

};

#endif // TABLEMODEL_SV_H
