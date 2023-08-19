#ifndef USERS_H
#define USERS_H

#include <QDateTime>
#include <QFile>
#include <QtXml>

// 游戏设置
struct GameSetting
{
    QString user;       // 当前用户

    QString background; // 背景图片
    QString bgm;        // 背景音乐

    Qt::Key keyUp;      // 按键设置
    Qt::Key keyDown;
    Qt::Key keyLeft;
    Qt::Key keyRight;

    Qt::Key keyPause; // 暂停键
};

// 用户信息
struct UserData
{
    QString name;     // 用户名
    QString password; // 密码
};

//
// 用户管理类
//

class Users
{
public:
    Users();

    // 添加一个用户
    bool add(QString name, QString password);

    // 清空
    void clear();

    // 返回数量
    int size() const;

    // 查找用户
    int find(QString name) const;

    // 返回用户
    UserData getUser(int id) const;

    // 保存
    bool save(QString filename);

    // 加载
    bool load(QString filename);

private:
    QVector<UserData> m_data;
};

extern Users users;

#endif // USERS_H
