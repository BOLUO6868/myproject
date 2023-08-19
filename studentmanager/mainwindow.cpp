#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,my_ptrstusql(nullptr)
{
    ui->setupUi(this);

    my_login.show();

    //测试


    auto f=[&](){
        this->show();
    };
    //如果登陆成功跳到主界面
    connect(&my_login,&page_login::loginSuccess,this,f);
    connect(&my_login,&page_login::loginstring,this,&MainWindow::showpage);
    connect(&my_login,&page_login::loginaut,this,&MainWindow::setaut);


    QStringList l;
    l<<"学生管理系统";
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);

    QTreeWidgetItem *p=new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->addTopLevelItem(p);

    l.clear();
    l<<"学生管理";
    QTreeWidgetItem *p1=new QTreeWidgetItem(p,l);
    l.clear();
    l<<"管理员管理";
    QTreeWidgetItem *p2=new QTreeWidgetItem(p,l);

    p->addChild(p1);
    p->addChild(p2);


    my_ptrstusql=stusql::getinstance();



    updatetable();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    exit(0);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_F6)
    {
        QFile f;
        auto str=QCoreApplication::applicationDirPath();
        f.setFileName(str+"//"+"stuqss.css");
        f.open(QIODevice::ReadOnly);
        QString st=f.readAll();
        this->setStyleSheet(st);
        my_login.setStyleSheet(st);
    }
    else{

    }
}


void MainWindow::on_btn_sim_clicked()
{
    // 姓氏列表
    QStringList surnames = {"赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋", "沈", "韩", "杨", "朱", "秦", "尤", "许", "何", "吕", "施", "张", "孔", "曹", "严", "华", "金", "魏", "陶", "姜", "戚", "谢", "邹", "喻", "柏", "水", "窦", "章", "云", "苏", "潘", "葛", "奚", "范", "彭", "郎", "鲁", "韦", "昌", "马", "苗", "凤", "花", "方", "俞", "任", "袁", "柳", "酆", "鲍", "史", "唐", "费", "廉", "岑", "薛", "雷", "贺", "倪", "汤", "滕", "殷", "罗", "毕", "郝", "邬", "安", "常", "乐", "于", "时", "傅", "皮", "卞", "齐", "康", "伍", "余", "元", "卜", "顾", "孟"};

    // 男性名列表
    QStringList maleNames = {"伟", "超", "强", "良", "敏", "杰", "辉", "勇", "磊", "军", "洪", "志", "宏", "鹏", "浩", "涛", "明", "亮", "刚", "昌", "俊", "斌", "慧", "静", "娟", "玲", "平", "丽", "燕", "荣", "红", "博", "欣", "梅", "莉", "秀", "华", "文", "彬", "秋", "润", "帆", "福", "年", "正", "中", "光", "霞", "薇", "婷", "露", "琪", "丹", "晖", "娜", "鸿", "凤", "颖", "雨", "靖", "峰", "安", "坤", "松", "洁", "咏", "琴", "阿", "梓", "泽", "翔", "琳", "彦", "欢", "苗", "家", "千", "珊", "春", "义", "全", "航", "思", "严", "兴", "奇", "岩", "升"};

                              // 女性名列表
                              QStringList femaleNames = {"娜", "芳", "婷", "秀", "英", "霞", "丽", "敏", "洁", "燕", "红", "佳", "玲", "华", "梅", "静", "琳", "文", "莉", "颖", "薇", "雪", "琪", "涵", "晶", "倩", "雅", "慧", "婧", "荣", "欣", "青", "媛", "怡", "宁", "瑶", "甜", "怡", "蓉", "婕", "凝", "楠", "钰", "馨", "露", "瑾", "晓", "倪", "晓", "钔", "紫", "钰", "云", "璐", "柔", "嘉", "妍", "晴", "淼", "蓝", "之", "雪", "蔚", "琇", "珍", "演", "菁", "昱", "姿", "艺", "劢", "梦", "沛", "宾", "菲", "怡", "燕", "萌", "薇", "卓", "伊", "玲", "泽", "宁", "茹", "蓝", "璐"};

    QStringList names;
    for (int i = 0; i < 1000; ++i) {
        // 随机选择一个姓氏
        QString surname = surnames.at(QRandomGenerator::global()->bounded(surnames.size()));

        // 随机选择一个性别，并根据性别选择对应的名字列表
        QString name;
        if (QRandomGenerator::global()->bounded(2) == 0) {
            // 男性
            name = maleNames.at(QRandomGenerator::global()->bounded(maleNames.size()));
        } else {
            // 女性
            name = femaleNames.at(QRandomGenerator::global()->bounded(femaleNames.size()));
        }

        // 组合姓氏和名字
        QString fullName = surname + name;
        names.append(fullName);
    }


    QRandomGenerator g;

    int i=0;
    //制作1000条
    for( i=0;i<1000;i++)
    {
        stuinfo info;
        info.name=names[i];
        auto grade=g.bounded(1,9);
        auto uiclass=g.bounded(1,8);


        if(i%3){
            info.age=20;
        }

        if(i%7){
            info.age=18;
        }

        if(i%2){
            info.age=27;
        }

        info.grade=grade;
        info.uiclass=uiclass;
        info.wechat="123456789";
        info.phone="10086";
        info.id=i;

    my_ptrstusql->addstu(info);
    }

    updatetable();

}


void MainWindow::on_pushButton_3_clicked()
{
    my_dlgaddstu.settype(true);
    my_dlgaddstu.exec();
    updatetable();
}


void MainWindow::on_btn_clear_clicked()
{
    my_ptrstusql->clearstutable();
    updatetable();
}

void MainWindow::updatetable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);

    QStringList l;
    l<<"序号"<<"编号"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);


    //只允许整行选中
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不允许编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    auto cnt=my_ptrstusql->getstucnt();
    ui->lb_cnt->setText(QString("数量：%1").arg(cnt));
    QList<stuinfo> lstudents=my_ptrstusql->getpagestu(0,cnt);



    ui->tableWidget->setRowCount(cnt);

    for(int i=0;i<lstudents.size();i++)
    {
    ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
    ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(lstudents[i].id)));
    ui->tableWidget->setItem(i,2,new QTableWidgetItem(lstudents[i].name));
    ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lstudents[i].age)));
    ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(lstudents[i].grade)));
    ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lstudents[i].uiclass)));
    ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(lstudents[i].studentid)));
    ui->tableWidget->setItem(i,7,new QTableWidgetItem(lstudents[i].phone));
    ui->tableWidget->setItem(i,8,new QTableWidgetItem(lstudents[i].wechat));
    }
}


void MainWindow::on_btn_delete_clicked()
{
    int i=ui->tableWidget->currentRow();

    if(i>=0)
    {
    int id=ui->tableWidget->item(i,1)->text().toUInt();
    my_ptrstusql->delstu(id);
    updatetable();
    QMessageBox::information(nullptr,"信息","删除成功");
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    stuinfo info;
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
    info.id=ui->tableWidget->item(i,1)->text().toUInt();

    info.name=ui->tableWidget->item(i,2)->text();
    info.age=ui->tableWidget->item(i,3)->text().toUInt();
    info.grade=ui->tableWidget->item(i,4)->text().toUInt();
    info.uiclass=ui->tableWidget->item(i,5)->text().toUInt();
    info.studentid=ui->tableWidget->item(i,6)->text().toUInt();
    info.phone=ui->tableWidget->item(i,7)->text();
    info.wechat=ui->tableWidget->item(i,8)->text();


    my_dlgaddstu.settype(false,info);
    my_dlgaddstu.exec();
    }



    updatetable();
}


void MainWindow::on_btn_search_clicked()
{
    QString strtext=ui->le_search->text();
    if(strtext.isEmpty())
    {
    updatetable();
    QMessageBox::information(nullptr,"警告","名字筛选为空");
    return;
    }


    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);

    QStringList l;
    l<<"序号"<<"编号"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);


    //只允许整行选中
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不允许编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    auto cnt=my_ptrstusql->getstucnt();
    ui->lb_cnt->setText(QString("数量：%1").arg(cnt));
    QList<stuinfo> lstudents=my_ptrstusql->getpagestu(0,cnt);



    //ui->tableWidget->setRowCount(cnt);

    int index=0;





    for(int i=0;i<lstudents.size();i++)
    {

    if(!lstudents[i].name.contains(strtext)){
            continue;
    }

    ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(index)));
    ui->tableWidget->setItem(index,1,new QTableWidgetItem(QString::number(lstudents[i].id)));
    ui->tableWidget->setItem(index,2,new QTableWidgetItem(lstudents[i].name));
    ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(lstudents[i].age)));
    ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(lstudents[i].grade)));
    ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(lstudents[i].uiclass)));
    ui->tableWidget->setItem(index,6,new QTableWidgetItem(QString::number(lstudents[i].studentid)));
    ui->tableWidget->setItem(index,7,new QTableWidgetItem(lstudents[i].phone));
    ui->tableWidget->setItem(index,8,new QTableWidgetItem(lstudents[i].wechat));
    index++;
    }

    ui->tableWidget->setRowCount(index);

     ui->lb_cnt->setText(QString("数量：%1").arg(index));
}

void MainWindow::showpage(const QString &username)
{
     ui->lb_user->setText(username);

     QFont font("Arial",12);

     ui->lb_user->setFont(font);
}

void MainWindow::setaut(const QString &aut)
{
     if(aut=="学生"){
    ui->btn_clear->setVisible(false);
    ui->btn_delete->setVisible(false);
    ui->btn_sim->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
     }
}



