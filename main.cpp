#include "mainwindow.h"
#include <QApplication>
#include <config_sqlconnect.h>
#include <tablemodel_sv.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    config_sqlconnect n;
    n.connectsql();//init connect sql before
    MainWindow w;
    w.show();
    return a.exec();
}
