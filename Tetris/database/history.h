#ifndef HISTORY_H
#define HISTORY_H

#include <QDateTime>
#include <QFile>
#include <QtXml>

// 分数数据
struct ScoreData
{
    QString name; // 用户名
    int score;    // 分数

    // 分数比较
    bool operator<(const ScoreData& other) const
    {
        return score > other.score;
    }
};

//
// 历史记录
//

class History
{
public:
    History();

    // 添加一个记录
    void add(QString name, int score);

    // 清空
    void clear();

    // 返回数量
    int size() const;

    // 返回记录
    ScoreData getData(int id) const;

    // 保存
    bool save(QString filename);

    // 加载
    bool load(QString filename);

private:
    QVector<ScoreData> m_data; // 记录数据
};

extern History history;

#endif // HISTORY_H
