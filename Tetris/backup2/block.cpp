#include "block.h"

Block::Block()
{
}

// 判断是否为空
bool Block::empty() const
{
    return width() == 0 || height() == 0;
}

// 绘制
void Block::draw(QPainter& painter, int x, int y)
{
    QBrush brush(this->color());

    QRectF rect = QRect(0.0f, 0.0f, 32, 32);

    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            rect.moveTo(x + j * 32, y + i * 32);
            painter.fillRect(rect, brush);
        }
    }
}
