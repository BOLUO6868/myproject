#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include"sign_up.h"

namespace Ui {
class page_login;
}

class page_login : public QWidget
{
    Q_OBJECT

public:
    explicit page_login(QWidget *parent = nullptr);
    ~page_login();

private slots:
    void on_btn_exit_clicked();

    void on_btn_login_clicked();

    void on_btn_sign_clicked();

signals:
   void loginSuccess();
   QString loginstring(const QString &str);
   QString loginaut(const QString &aut);
private:
    Ui::page_login *ui;
    sign_up my_sign;
    stusql  *my_stusql;

};

#endif // PAGE_LOGIN_H
