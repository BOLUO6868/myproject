#include "game.h"

Game::Game() :
    Object(),
    m_block("Board", 10, 20) // 初始化默认 10x20
{
}

// 设置宽高
void Game::setSize(int w, int h)
{
    m_block = Block("Board", w, h);
}

// 返回宽度
int Game::width() const
{
    return m_block.width();
}

// 返回高度
int Game::height() const
{
    return m_block.height();
}

// 绘制
void Game::draw(QPainter& painter, float posX, float posY)
{
    Block::draw(painter, posX, posY)
}
