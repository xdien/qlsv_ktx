#ifndef ADD_LOP_H
#define ADD_LOP_H

#include <QDialog>

namespace Ui {
class add_lop;
}

class add_lop : public QDialog
{
    Q_OBJECT

public:
    explicit add_lop(QWidget *parent = 0);
    ~add_lop();

private:
    Ui::add_lop *ui;
};

#endif // ADD_LOP_H
