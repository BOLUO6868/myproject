#include "sign_up.h"
#include "ui_sign_up.h"
#include"stusql.h"
#include<QMessageBox>
#include<QDebug>
#include<QInputDialog>



sign_up::sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);

    my_stusql=stusql::getinstance();

    ui->le_password->setEchoMode(QLineEdit::Password);
    ui->le_passwordcheck->setEchoMode(QLineEdit::Password);



}

sign_up::~sign_up()
{
    delete ui;
}

void sign_up::on_pushButton_2_clicked()
{
    exit(0);
}


void sign_up::on_btn_confirm_clicked()
{
    QString textname=ui->le_name->text();
    QString password1=ui->le_password->text();
    QString password2=ui->le_passwordcheck->text();


    my_stusql=stusql::getinstance();

    if(my_stusql->isexit(textname)){
        QMessageBox::information(nullptr,"错误","该用户名已存在");
        //qDebug()<<"成功";
        return;
    }
    if(password1!=password2){
        QMessageBox::information(nullptr,"错误","两次密码不一样");
        return;
    }

    if(textname==NULL){
        QMessageBox::information(nullptr,"错误","未填写用户名");
        return;
    }
    if(password1==NULL){
        QMessageBox::information(nullptr,"错误","未填写密码");
        return;
    }
    if(password2==NULL){
        QMessageBox::information(nullptr,"错误","未确认密码");
        return;
    }

    if(ui->rb_stu->isChecked()==false&&ui->rb_man->isChecked()==false){
        QMessageBox::information(nullptr,"错误","未选择身份");
        return;
    }


    if(ui->rb_stu->isChecked()==true){
        userinfo info;
        info.username=ui->le_name->text();
        info.password=ui->le_password->text();
        info.aut="学生";

        my_stusql->adduser(info);

        QMessageBox::information(nullptr,"提示","成功注册学生账号");
        this->hide();
    }


    if(ui->rb_man->isChecked()==true){
        bool ok;
        QString adminPassword = QInputDialog::getText(this, "输入管理员密码", "管理员密码:", QLineEdit::Password, QString(), &ok);

        if(adminPassword=="pzx11620"){
            userinfo info;
            info.username=ui->le_name->text();
            info.password=ui->le_password->text();
            info.aut="管理员";

            my_stusql->adduser(info);

            QMessageBox::information(nullptr,"提示","成功注册管理员账号");
            this->hide();

        }

        else{
            QMessageBox::information(nullptr,"错误","管理员密码错误");
        }

    }


}

