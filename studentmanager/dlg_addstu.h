#ifndef DLG_ADDSTU_H
#define DLG_ADDSTU_H

#include <QDialog>
#include"stusql.h"

namespace Ui {
class dlg_addstu;
}

class dlg_addstu : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_addstu(QWidget *parent = nullptr);
    ~dlg_addstu();

    void settype(bool isadd,stuinfo info={});

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::dlg_addstu *ui;
    bool m_isadd;
    stuinfo my_info;
};

#endif // DLG_ADDSTU_H
