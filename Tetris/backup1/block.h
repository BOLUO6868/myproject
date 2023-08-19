#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>

//
// 基础方块类
//

class Block
{
public:
    Block(int w, int h);

    bool empty() const; // 判断是否为空
    int width() const;  // 返回宽度
    int height() const; // 返回高度

    // 返回颜色
    QColor color() const;

    // 设置颜色
    void setColor(QColor color);

    // 旋转
    void rotate();

    // 绘制
    virtual void draw(QPainter& painter) = 0;

private:
    QVector<QVector<char>> m_data; // 方格数据
    QColor m_color;                // 颜色

    // 更改大小
    void resize(QVector<QVector<char>>& a, int w, int h);
};

#endif // BLOCK_H
