#include "stusql.h"
#include<QMessageBox>
#include<QtSql/QSqlQuery>
#include<QtSql>
#include<QtDebug>
#include<QApplication>



stusql *stusql::ptrstusql=nullptr;

stusql::stusql(QObject *parent)
    : QObject{parent}
{

    init();
    //测试代码
    //stuinfo s;
    //s.name="刘福";
    //for(int i=0;i<3;i++){
    //    addstu(s);
    //}

    //测试
    //getstucnt();
    //getpagestu(2,3);
    //QSqlQuery q("",db);
    //q.exec("INSERT INTO student VALUES (NULL,'张三',12,3,2,1,1987896525,'azhang');");
    //delstu(8);

    //stuinfo s;
    //s.id=5;
    //s.name="dd";
    //updatestuinfo(s);

/*
    userinfo info;
    info.username="liufu";
    info.password="123456";
    info.aut="admin";

    adduser(info);
    adduser(info);

    auto l=getalluser();
    qDebug()<<isexit("liufu");

    info.password="666";
    updateuser(info);

    deluser("liufu");
*/




}

//打开数据库
void stusql::init()
{
    if(QSqlDatabase::drivers().isEmpty()){
        qDebug()<<"can not find db";
    }

    my_db=QSqlDatabase::addDatabase("QSQLITE");

/*
    auto str=QCoreApplication::applicationDirPath();
    qDebug()<<str;
*/ //先封上

    my_db.setDatabaseName("D:\\QTproject\\studentmanager\\data.db");
    if(!my_db.open()){
        qDebug()<<"db not open";
    }
}



quint32 stusql::getstucnt()
{
    QSqlQuery sql(my_db);
    sql.exec("select count(id) from student;");
    quint32 cnt=0;
    while(sql.next())//获取字段里面的值
    {
        cnt=sql.value(0).toUInt();

        //qDebug()<<sql.value(0).toUInt();
    }

    return cnt;
}

QList<stuinfo> stusql::getpagestu(quint32 page, quint32 uicnt)
{
    QList<stuinfo> l;
    QSqlQuery sql(my_db);
    QString strsql=QString("select * from student order by id limit %1 offset %2").
                     arg(uicnt).arg(page*uicnt);

    sql.exec(strsql);

    stuinfo info;
    while(sql.next())
    {
        info.id=sql.value(0).toUInt();
        info.name=sql.value(1).toString();
        info.age=sql.value(2).toUInt();
        info.grade=sql.value(3).toUInt();
        info.uiclass=sql.value(4).toUInt();
        info.studentid=sql.value(5).toUInt();
        info.phone=sql.value(6).toString();
        info.wechat=sql.value(7).toString();

        l.push_back(info);
    }

    return l;


}



bool stusql::addstu(stuinfo info)
{
    QSqlQuery sql(my_db);
    QString strsql=QString("insert into student values(null,'%1',%2,%3,%4,%5,'%6','%7')").
                     arg(info.name).
                     arg(info.age).
                     arg(info.grade).
                     arg(info.uiclass).
                     arg(info.studentid).
                     arg(info.phone).
                     arg(info.wechat);

    //测试是否成功
    //qDebug()<<sql.exec(strsql);

    return sql.exec(strsql);
}



bool stusql::delstu(int id)
{
    QSqlQuery sql(my_db);
    QString strsql=QString("delete from student where id = %1").arg(id);


    return sql.exec(strsql);
}


bool stusql::clearstutable()
{
    QSqlQuery sql(my_db);
    QString strsql=QString("delete from student");
    sql.exec(strsql);

    return sql.exec("DELETE FROM sqlite_sequence WHERE name ='student' ");
}

bool stusql::updatestuinfo(stuinfo info)
{
    QSqlQuery sql(my_db);
    QString strsql=QString("update student set name='%1',age=%2, grade=%3, class=%4, studentid=%5, phone='%6', wechat='%7' where id=%8;" ).
                     arg(info.name).
                     arg(info.age).
                     arg(info.grade).
                     arg(info.uiclass).
                     arg(info.studentid).
                     arg(info.phone).
                     arg(info.wechat).
                     arg(info.id);

    //测试是否成功
    //qDebug()<<sql.exec(strsql);

    return sql.exec(strsql);
}


QList<userinfo> stusql::getalluser()
{
    QList<userinfo> l;
    QSqlQuery sql(my_db);
    QString strsql=QString("select * from username");


    sql.exec(strsql);

    userinfo info;
    while(sql.next())
    {
        info.username=sql.value(0).toString();
        info.password=sql.value(1).toString();
        info.aut=sql.value(2).toString();

        l.push_back(info);
    }
    return l;
}



bool stusql::isexit(QString struser)
{
    QSqlQuery sql(my_db);
    QString strsql=QString("select * from username where username='%1'").arg(struser);

    sql.exec(strsql);

    return sql.next();
}

bool stusql::updateuser(userinfo info)
{
    QSqlQuery sql(my_db);
    QString strsql=QString("update username set password='%1', aut='%2' where username='%3';" ).
                     arg(info.password).
                     arg(info.aut).
                     arg(info.username);


    //测试是否成功
    //qDebug()<<sql.exec(strsql);

    return sql.exec(strsql);
}



bool stusql::adduser(userinfo info)
{
    QSqlQuery sql(my_db);
    QString strsql=QString("insert into username values('%1','%2','%3')").
                     arg(info.username).
                     arg(info.password).
                     arg(info.aut);


    //测试是否成功
    //qDebug()<<sql.exec(strsql);

    return sql.exec(strsql);
}


bool stusql::deluser(QString strusername)
{
    QSqlQuery sql(my_db);
    QString strsql=QString("delete from username where username='%1'").arg(strusername);
    return sql.exec(strsql);

}

bool stusql::checkuser(QString user,QString pass)
{
    QSqlQuery sql((my_db));
    QString strsql=QString("select * from username where username='%1'").arg(user);

    sql.exec(strsql);
    userinfo info;

    while (sql.next()) {
        info.username = sql.value("username").toString();
        info.password = sql.value("password").toString();
    }

    if(pass!=info.password){

        return false;
    }

    else{

        return true;
    }

}

QString stusql::getaut(QString user)
{
    QSqlQuery sql((my_db));
    QString strsql=QString("select * from username where username='%1'").arg(user);

    sql.exec(strsql);
    userinfo info;

    while (sql.next()) {
        info.aut = sql.value("aut").toString();
    }

    return info.aut;
}

