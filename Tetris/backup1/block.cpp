#include "block.h"

Block::Block(int w, int h) :
    m_data()
{
}

// 判断是否为空
bool Block::empty() const
{
    return width() == 0 || height() == 0;
}

// 返回宽度
int Block::width() const
{
    if (m_data.empty()) {
        return 0;
    }
    return m_data[0].size();
}

// 返回高度
int Block::height() const
{
    if (m_data.empty()) {
        return 0;
    }
    return m_data.size();
}

// 旋转
void Block::rotate()
{
    int w = this->width();
    int h = this->height();

    if (w == 0 || h == 0) { // empty
        return;
    }

    // 构造一个临时数据
    QVector<QVector<char>> temp;
    resize(temp, h, w);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            temp[x][y] = m_data[y][x];
        }
    }

    // 交换
    m_data.swap(temp);
}

// 更改大小
void Block::resize(QVector<QVector<char>>& a, int w, int h)
{
    a.resize(h);
    for (auto& line: a) {
        line.resize(w);
    }
}
