#ifndef STUSQL_H
#define STUSQL_H
#include<QtSql>
#include <QObject>
#include<QMessageBox>
#include<QtSql/QSqlDatabase>


//定义学生信息的类
struct stuinfo
{
    int id;
    QString name;
    quint8 age;
    quint16 grade;
    quint16 uiclass;
    quint32 studentid;
    QString phone;
    QString wechat;
};

//定义用户的类
struct userinfo
{
    QString username;
    QString password;
    QString aut;//定义权限
};






class stusql : public QObject
{
    Q_OBJECT
public:
    static stusql *ptrstusql;
    static stusql *getinstance()
    {
        if(ptrstusql==nullptr)
        {
            ptrstusql=new stusql;
        }
        return ptrstusql;
    }



    explicit stusql(QObject *parent = nullptr);

    void init();


    //查询所有学生数量
    quint32 getstucnt();

    //查询第几页学生数据,从第0页开始
    QList<stuinfo> getpagestu(quint32 page,quint32 uicnt);
    //增加一个学生
    bool addstu(stuinfo);
    //删除一个学生
    bool delstu(int id);

    //清空学生表
    bool clearstutable();

    //修改学生
    bool updatestuinfo(stuinfo info);
    //查询用户
    QList<userinfo> getalluser();

    //查询用户名是否存在
    bool isexit(QString struser);

    //更新用户信息
    bool updateuser(userinfo info);

    //添加单个用户
    bool adduser(userinfo info);

    //删除单个用户
    bool deluser(QString strusername);

    bool checkuser(QString user,QString pass);

    QString getaut(QString user);

signals:


private:
    QSqlDatabase my_db;



};

#endif // STUSQL_H
