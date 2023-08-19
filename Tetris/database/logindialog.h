#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    // 返回登陆用户名
    QString userName();

private slots:
    void on_buttonRegister_clicked();

    void on_buttonOK_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::LoginDialog *ui;

    // 记录当前登陆用户名
    QString m_userName;
};

#endif // LOGINDIALOG_H
