#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include"stusql.h"

namespace Ui {
class sign_up;
}

class sign_up : public QDialog
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = nullptr);
    ~sign_up();

private slots:
    void on_pushButton_2_clicked();

    void on_btn_confirm_clicked();

private:
    Ui::sign_up *ui;
    stusql  *my_stusql;

};

#endif // SIGN_UP_H
