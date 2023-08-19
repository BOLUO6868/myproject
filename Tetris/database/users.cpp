#include "users.h"

#include <QMessageBox>
#include <QDebug>

Users users; // 用户管理对象

Users::Users()
{
}

// 添加一个用户
bool Users::add(QString name, QString password)
{
    if (this->find(name) == -1) {
        UserData ud = { name, password };
        m_data.push_back(ud);
        return true;
    }
    return false;
}

// 清空
void Users::clear()
{
    m_data.clear();
}

// 返回数量
int Users::size() const
{
    return m_data.size();
}

// 查找用户
int Users::find(QString name) const
{
    for (int i = 0; i < m_data.size(); ++i) {
        const UserData& u = m_data[i];
        if (u.name == name) {
            return i;
        }
    }
    return -1;
}

// 返回用户
UserData Users::getUser(int id) const
{
    return m_data[id];
}

// 保存
bool Users::save(QString filename)
{
    // 打开文件
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(nullptr, "错误", "文件创建失败。");
        return false;
    }

    // 创建 xml
    QDomDocument doc;

    // 初始化 xml 头
    QDomProcessingInstruction ins;
    ins = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(ins);

    // 添加根节点
    QDomElement root = doc.createElement("users");
    doc.appendChild(root);

    // 保存所有用户
    QDomElement subItem;
    for (auto data: m_data) {
        QDomElement item = doc.createElement("user");
        root.appendChild(item);

        subItem = doc.createElement("name");
        subItem.appendChild(doc.createTextNode(data.name));
        item.appendChild(subItem);

        subItem = doc.createElement("password");
        subItem.appendChild(doc.createTextNode(data.password));
        item.appendChild(subItem);
    }

    // 保存到文件
    QTextStream stm(&file);
    doc.save(stm, 4); // 缩进 4 格
    file.close();

    return true;
}

// 加载
bool Users::load(QString filename)
{
    QDomDocument doc;

    // 打开文件
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(nullptr, "错误", "文件打开失败。");
        return false;
    }

    if (!doc.setContent(&file)) {
        QMessageBox::warning(nullptr, "错误", "XML 解析失败。");
        file.close();
        return false;
    }
    file.close();

    // 检查根节点
    QDomElement root = doc.documentElement();
    if (root.isNull() || root.nodeName() != "users") {
        QMessageBox::warning(nullptr, "错误", "XML 格式不正确。");
        return false;
    }

    // 清空
    this->clear();

    // 遍历解析子节点
    QDomNode item = root.firstChildElement("user");
    QDomNode subItem;
    while (!item.isNull()) {
        // qDebug() << item.nodeName();
        UserData data;

        subItem = item.firstChildElement("name");
        if (!subItem.isNull()) {
            data.name = subItem.firstChild().toText().data();
        }

        subItem = item.firstChildElement("password");
        if (!subItem.isNull()) {
            data.password = subItem.firstChild().toText().data();
        }

        qDebug() << "user:" << data.name << data.password;

        // 添加到列表
        m_data.push_back(data);

        // 下一个节点
        item = item.nextSiblingElement("user");
    }

    qDebug() << "load users: " << m_data.size();

    return true;
}
