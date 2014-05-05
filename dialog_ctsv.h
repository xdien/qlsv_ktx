#ifndef DIALOG_CTSV_H
#define DIALOG_CTSV_H

#include <QDialog>

namespace Ui {
class Dialog_CTSV;
}

class Dialog_CTSV : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_CTSV(QWidget *parent = 0);
    ~Dialog_CTSV();

private:
    Ui::Dialog_CTSV *ui;
};

#endif // DIALOG_CTSV_H
