#include "dlg_addstu.h"
#include "ui_dlg_addstu.h"
#include"stusql.h"
#include<QMessageBox>


dlg_addstu::dlg_addstu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_addstu)
{
    ui->setupUi(this);
}

dlg_addstu::~dlg_addstu()
{
    delete ui;
}


void dlg_addstu::settype(bool isadd,stuinfo info)
{
    m_isadd=isadd;
    ui->le_id->setText(QString::number(info.id));
    if(!isadd){
        ui->le_id->setReadOnly(true);
    }
    ui->sb_age->setValue(info.age);
    ui->le_grade->setText(QString::number(info.grade));
    ui->le_class->setText(QString::number(info.uiclass));
    ui->le_name->setText(info.name);
    ui->le_phone->setText(info.phone);
    ui->le_number->setText(info.phone);
    ui->le_wechat->setText(info.wechat);

}



void dlg_addstu::on_pushButton_2_clicked()
{
    this->hide();
}


void dlg_addstu::on_pushButton_clicked()
{
    stuinfo info;
    info.age=ui->sb_age->text().toUInt();
    info.id=ui->le_id->text().toUInt();
    info.grade=ui->le_grade->text().toUInt();
    info.uiclass=ui->le_class->text().toUInt();
    info.name=ui->le_name->text();
    info.phone=ui->le_phone->text();
    info.studentid=ui->le_number->text().toUInt();
    info.wechat=ui->le_wechat->text();


    auto ptr=stusql::getinstance();

    if(m_isadd)
    {

        ptr->addstu(info);
    }
    else
    {
        ui->le_id->setReadOnly(true);
        ptr->updatestuinfo(info);
    }





    QMessageBox::information(nullptr,"信息","储存成功");
    this->hide();


}

