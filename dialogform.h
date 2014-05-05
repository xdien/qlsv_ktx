#ifndef DIALOGFORM_H
#define DIALOGFORM_H

#include <QDialog>

namespace Ui {
class DialogForm;
}

class DialogForm : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForm(QWidget *parent = 0);
    ~DialogForm();
    QString textquery;

private slots:
    void on_buttonBox_accepted();
private:
    Ui::DialogForm *ui;
};

#endif // DIALOGFORM_H
