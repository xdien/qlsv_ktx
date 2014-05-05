
#ifndef LISTTABLE_H
#define LISTTABLE_H

#include <QTableView>
#include <QtSql>

class listtable : public QTableView
{
    Q_OBJECT
public:
    explicit listtable(QWidget *parent = 0);
    QSqlQueryModel *model;
signals:

public slots:

};

#endif // LISTTABLE_H
