#include "registerdialog.h"
#include "ui_registerdialog.h"

#include "users.h"

#include <QMessageBox>
#include <QToolTip>

RegisterDialog::RegisterDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

// 注册
void RegisterDialog::on_buttonRegister_clicked()
{
    QString name;
    QString password1;
    QString password2;
    QPoint pos;

    // 用户名
    name = ui->lineEditName->text();
    if (name.isEmpty()) {
        ui->lineEditName->setFocus();
        pos = ui->lineEditName->mapToGlobal(QPoint(20, 10));
        QToolTip::showText(pos, "用户名不能为空。", ui->lineEditName);
        return;
    }

    // 密码1
    password1 = ui->lineEditPassword->text();
    if (password1.isEmpty()) {
        ui->lineEditPassword->setFocus();
        pos = ui->lineEditPassword->mapToGlobal(QPoint(20, 10));
        QToolTip::showText(pos, "密码不能为空。", ui->lineEditPassword);
        return;
    }

    // 密码2
    password2 = ui->lineEditPassword2->text();
    if (password2.isEmpty()) {
        ui->lineEditPassword2->setFocus();
        pos = ui->lineEditPassword2->mapToGlobal(QPoint(20, 10));
        QToolTip::showText(pos, "确认密码不能为空。", ui->lineEditPassword2);
        return;
    }

    // 判断密码是否一致
    if (password1 != password2) {
        ui->lineEditPassword2->setFocus();
        pos = ui->lineEditPassword2->mapToGlobal(QPoint(20, 10));
        QToolTip::showText(pos, "密码不一致。", ui->lineEditPassword2);
        return;
    }

    // 添加用户
    if (users.add(name, password1)) {
        users.save("users.xml");
        QMessageBox::warning(this, "消息", "注册成功！");
        this->close();
    }
    else {
        QMessageBox::warning(this, "错误", "用户名已存在。");
    }
}

// 取消
void RegisterDialog::on_buttonCancel_clicked()
{
    this->close();
}
