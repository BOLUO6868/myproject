#include "history.h"

#include <QMessageBox>
#include <QDebug>

History history; // 历史记录对象

History::History()
{
}

// 添加一个记录
void History::add(QString name, int score)
{
    ScoreData d;
    d.name  = name;
    d.score = score;

    m_data.push_back(d);

    // 排序
    std::sort(m_data.begin(), m_data.end());

    // 删除 10 个以上的数据
    while (m_data.size() > 10) {
        m_data.pop_back();
    }
}

// 清空
void History::clear()
{
    m_data.clear();
}

// 返回数量
int History::size() const
{
    return m_data.size();
}

// 返回记录
ScoreData History::getData(int id) const
{
    return m_data[id];
}

// 保存
bool History::save(QString filename)
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
    QDomElement root = doc.createElement("history");
    doc.appendChild(root);

    // 保存所有任务
    QDomElement subItem;
    for (auto data: m_data) {
        QDomElement item = doc.createElement("item");
        root.appendChild(item);

        subItem = doc.createElement("name");
        subItem.appendChild(doc.createTextNode(data.name));
        item.appendChild(subItem);

        subItem = doc.createElement("score");
        subItem.appendChild(doc.createTextNode(QString::number((int) data.score)));
        item.appendChild(subItem);
    }

    // 保存到文件
    QTextStream stm(&file);
    doc.save(stm, 4); // 缩进 4 格
    file.close();

    return true;
}

// 加载
bool History::load(QString filename)
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
    if (root.isNull() || root.nodeName() != "history") {
        QMessageBox::warning(nullptr, "错误", "XML 格式不正确。");
        return false;
    }

    // 清空
    this->clear();

    // 遍历解析子节点
    QDomNode item = root.firstChildElement("item");
    QDomNode subItem;
    while (!item.isNull()) {
        // qDebug() << item.nodeName();
        ScoreData data;

        subItem = item.firstChildElement("name");
        if (!subItem.isNull()) {
            data.name = subItem.firstChild().toText().data();
        }

        QDomNode subItem = item.firstChildElement("score");
        if (!subItem.isNull()) {
            data.score = subItem.firstChild().toText().data().toInt();
        }

        qDebug() << "score:" << data.name << data.score;

        // 添加到列表
        m_data.push_back(data);

        // 下一个节点
        item = item.nextSiblingElement("item");
    }

    qDebug() << "load scores: " << m_data.size();

    return true;
}
