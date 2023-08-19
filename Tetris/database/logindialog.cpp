#include "logindialog.h"
#include "ui_logindialog.h"

#include "users.h"
#include "registerdialog.h"

#include <QMessageBox>
#include <QToolTip>

LoginDialog::LoginDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// 注册
void LoginDialog::on_buttonRegister_clicked()
{
    // 显示注册窗口
    RegisterDialog dialog(this);
    dialog.exec();
}

// 登陆
void LoginDialog::on_buttonOK_clicked()
{
    QString name;
    QString password;
    QPoint pos;

    // 用户名
    name = ui->lineEditName->text();
    if (name.isEmpty()) {
        ui->lineEditName->setFocus();
        pos = ui->lineEditName->mapToGlobal(QPoint(20, 10));
        QToolTip::showText(pos, "用户名不能为空。", ui->lineEditName);
        return;
    }

    // 密码
    password = ui->lineEditPassword->text();
    if (password.isEmpty()) {
        ui->lineEditPassword->setFocus();
        pos = ui->lineEditPassword->mapToGlobal(QPoint(20, 10));
        QToolTip::showText(pos, "密码不能为空。", ui->lineEditPassword);
        return;
    }

    // 查找用户信息
    int id = users.find(name);

    if (id < 0) {
        QMessageBox::warning(this, "错误", "用户名不存在。");
    }
    else {
        UserData data = users.getUser(id);

        // 判断密码是否正确
        if (data.password == password) {
            // 记录用户名
            m_userName = name;

            // 成功返回
            this->accept();
        }
        else {
            QMessageBox::warning(this, "错误", "密码不正确！");
        }
    }
}

// 取消
void LoginDialog::on_buttonCancel_clicked()
{
    this->reject();
}

// 返回登陆用户名
QString LoginDialog::userName()
{
    return m_userName;
}
