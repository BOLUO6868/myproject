#ifndef GAME_H
#define GAME_H

#include "block/block.h"
#include "block/blockT.h"
#include "block/blockZ.h"
#include "block/blockI.h"
#include "block/blockL.h"

// 面板
class Game : public Object
{
public:
    Game();

    // 设置宽高
    void setSize(int w, int h);

    // 返回宽度
    int width() const;

    // 返回高度
    int height() const;

    // 绘制
    void draw(QPainter &painter, float posX, float posY) override;

private:
    Block m_block;

    Block* m_currentBlock; // 当前的方块
    Block* m_nextBlock;    // 下一个方块

    // 随机一个方块
    Block* randomBlock();
};

#endif // GAME_H
