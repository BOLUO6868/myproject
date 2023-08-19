#ifndef BOARD_H
#define BOARD_H

#include "block/block.h"
#include "block/blockT.h"
#include "block/blockZ.h"
#include "block/blockI.h"
#include "block/blockL.h"

// 面板
class Board : public Block
{
public:
    // 初始化默认 10x20
    Board(int w = 10, int h = 20);

    // 绘制
    void draw(QPainter &painter, float posX, float posY) override;
};

#endif // BOARD_H
