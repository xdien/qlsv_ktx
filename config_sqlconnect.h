#ifndef CONFIG_SQLCONNECT_H
#define CONFIG_SQLCONNECT_H
#include <QtSql>


class config_sqlconnect
{
public:

    //khai bao bien chung
    QString nameconnect;//khai bao ten ket noi
    QSqlDatabase db;
    config_sqlconnect();
    //funtion connect to sqlserver;
    QSqlDatabase connectsql();
    void disconnectsql();
};

#endif // CONFIG_SQLCONNECT_H
