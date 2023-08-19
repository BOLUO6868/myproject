#include "board.h"

// 初始化默认 10x20
Board::Board(int w, int h) :
    Block("Board", w, h)
{
    this->setColor(QColor(255, 255, 255, 220));

    for (int y = 0; y < this->height(); ++y) {
        for (int x = 0; x < this->width(); ++x) {
        }
    }
}

// 绘制
void Board::draw(QPainter& painter, float posX, float posY)
{
    int w = this->width() * BOX_SIZE;
    int h = this->height() * BOX_SIZE;

    // 绘制背景
    QRectF rect = QRectF(posX - 4.0f, posY - 4.0f, w + 8.0f, h + 8.0f);
    //painter.fillRect(rect, QColor(255, 255, 255, 128));
    painter.fillRect(rect, QColor(0, 0, 0, 128));

    Block::draw(painter, posX, posY);
}
