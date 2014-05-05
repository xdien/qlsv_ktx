#ifndef TABELMODELALL_H
#define TABELMODELALL_H

#include <QSqlTableModel>

class tabelmodelAll : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit tabelmodelAll(QObject *parent = 0);

signals:

public slots:

};

#endif // TABELMODELALL_H
