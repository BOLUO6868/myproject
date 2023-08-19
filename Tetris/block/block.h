#ifndef BLOCK_H
#define BLOCK_H

#include "object.h"

const int BOX_SIZE = 28;

//
// 基础方块类
//

class Block : public Object
{
public:
    Block(QString name, int w, int h);

    QString name() const;               // 返回名字

    bool empty() const;                 // 判断是否为空
    int width() const;                  // 返回宽度
    int height() const;                 // 返回高度

    QPoint pos() const;                 // 返回位置
    void setPos(QPoint value);          // 设置位置
    void setPos(int x, int y);          // 设置位置

    QColor color() const;               // 返回颜色
    void setColor(QColor color);        // 设置颜色

    bool checkPos(int x, int y) const;  // 检测坐标是否在范围内
    int get(int x, int y) const;        // 获取格子的值
    void set(int x, int y, int value);  // 设置格子的值

    void rotateLeft();                  // 左旋转
    void rotateRight();                 // 右旋转
    bool intersect(Block* other) const; // 碰撞测试

    bool checkLine(int y) const;        // 判断一行是否全部是方块
    void moveLine(int yFrom, int yTo);  // from 行移动到 to 行

    // 将另外一个性质复制到这个形状
    void blt(Block* other);

    // 绘制
    void draw(QPainter& painter, float posX, float posY) override;

    // 保存到一个 xml 节点中
    virtual QDomElement save(QDomElement node);

    // 从一个 xml 节点读取
    virtual bool load(QDomElement node);

private:
    QString m_name;               // 名字
    QVector<QVector<int>> m_data; // 方格数据
    QPoint m_pos;                 // 位置
    QColor m_color;               // 颜色

    // 更改大小
    void resize(QVector<QVector<int>>& a, int w, int h);

    // data 转换成字符串
    QString dataToString() const;

    // 从字符串解析 data
    bool dataFromString(int w, int h, QString str);
};

#endif // BLOCK_H
