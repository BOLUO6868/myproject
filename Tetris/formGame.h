#ifndef FORMGAME_H
#define FORMGAME_H

#include <QWidget>
#include "block/block.h"
#include "block/blockT.h"
#include "block/blockZ.h"
#include "block/blockI.h"
#include "block/blockL.h"
#include "block/blockO.h"
#include "block/board.h"

namespace Ui {
class FormGame;
}

class FormGame : public QWidget
{
    Q_OBJECT

public:
    explicit FormGame(QWidget* parent = nullptr);
    ~FormGame();

    // 开始游戏
    void start(int w, int h, int speed);

    // 保存游戏
    bool save(QString filename);

    // 加载游戏
    bool load(QString filename);

protected:
    void keyPressEvent(QKeyEvent* event);   // 按键按下
    void keyReleaseEvent(QKeyEvent* event); // 按键弹起
    void timerEvent(QTimerEvent* event);    // 计时器事件
    void paintEvent(QPaintEvent* event);    // 绘制事件

public slots:
    void onTimer();

private:
    Ui::FormGame* ui;

    QTimer m_timer; // 计时器
    int m_speed;    // 速度（毫秒）

    Board m_board;
    QPointF m_blockPos;              // 面板位置

    Block* m_currentBlock = nullptr; // 当前的方块
    Block* m_nextBlock    = nullptr; // 下一个方块

    bool m_pause;                    // 暂停
    bool m_end;                      // 结束
    bool m_cleaning;                 // 是否正在清理中
    int m_score;                     // 分数

    // 重置窗口大小
    void resetSize(int w, int h);

    // 根据名字创建 block
    Block* createFromName(QString name);

    // 暂停
    void setPause(bool value);

    // 随机一个方块
    Block* randomBlock();

    // 方块下落
    bool blockDown();

    // 消除
    bool clean();
};

#endif // FORMGAME_H
