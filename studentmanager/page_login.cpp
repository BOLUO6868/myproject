#include "page_login.h"
#include "ui_page_login.h"

page_login::page_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_login)
{
    ui->setupUi(this);
    ui->le_password->setEchoMode(QLineEdit::Password);
    my_stusql=stusql::getinstance();
}

page_login::~page_login()
{
    delete ui;
}



//当点击退出的时候直接退出
void page_login::on_btn_exit_clicked()
{
    exit(0);
}


//数据库查找数据和密码
void page_login::on_btn_login_clicked()
{
    QString user=ui->le_user->text();
    QString password=ui->le_password->text();


    if(!my_stusql->isexit(user)){
        QMessageBox::information(nullptr,"错误","用户名不存在");

    }

    else{
        if(my_stusql->checkuser(user,password)){
            //QMessageBox::information(nullptr,"提示","登陆成功");
            this->hide();
            emit loginSuccess();

            QString aut=my_stusql->getaut(user);
            emit loginstring(aut+":  "+user);

            emit loginaut(aut);
        }
        else{
             QMessageBox::information(nullptr,"错误","密码错误");
        }

    }


}





void page_login::on_btn_sign_clicked()
{
    my_sign.show();
}

