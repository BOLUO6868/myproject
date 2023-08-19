#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>

//
// 基础方块类
//

class Block
{
public:
    Block();

    bool empty() const;                       // 判断是否为空

    virtual int width() const            = 0; // 返回宽度
    virtual int height() const           = 0; // 返回高度
    virtual bool get(int x, int y) const = 0; // 获取格子的值
    virtual QColor color() const         = 0; // 返回颜色
    virtual void rotate()                = 0; // 旋转

    // 绘制
    void draw(QPainter& painter, int x, int y);
};

#endif // BLOCK_H
