#ifndef TABLEMODLALL_H
#define TABLEMODLALL_H

#include <QTableView>
#include <QSqlTableModel>
#include <QtSql>

class tablemodlall : public QTableView
{
    Q_OBJECT
public:
    explicit tablemodlall(QWidget *parent, QString table_name);
    QSqlTableModel *model;



signals:

public slots:

};

#endif // TABLEMODLALL_H
