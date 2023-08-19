#include "formGame.h"
#include "ui_formGame.h"

#include "mainwindow.h"
#include "formSetting.h"
#include "audio.h"
#include "database/history.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSound>
#include <iostream>
#include <fstream>

FormGame::FormGame(QWidget* parent) :
    QWidget(parent), ui(new Ui::FormGame)
{
    ui->setupUi(this);
    this->setWindowTitle("俄罗斯方块"); // 标题
    this->setFocus();                   // 设置焦点，接受按键输入

    // 组件事件
    connect(ui->buttonPause, &QToolButton::clicked, [=] { // 暂停
        setPause(!m_pause);
    });

    connect(ui->buttonSave, &QToolButton::clicked, [=] { // 保存
        bool ok = this->save("save.xml");
        qDebug() << "save:" << ok;
    });

    connect(ui->buttonLoad, &QToolButton::clicked, [=] { // 加载
        bool ok = this->load("save.xml");
        qDebug() << "load:" << ok;
    });

    connect(ui->buttonSetting, &QToolButton::clicked, [=] { // 设置
        bool pause = m_pause;
        m_pause    = true;

        FormSetting setting(this);
        setting.exec();

        m_pause = pause;
    });

    connect(ui->buttonExit, &QToolButton::clicked, [=] { // 退出
        MainWindow* form = new MainWindow();
        form->show();
        close();
    });
}

FormGame::~FormGame()
{
    m_timer.stop();

    if (m_currentBlock) {
        delete m_currentBlock;
    }

    if (m_nextBlock) {
        delete m_nextBlock;
    }

    delete ui;
}

// 按键按下
void FormGame::keyPressEvent(QKeyEvent* event)
{
    const GameSetting setting = FormSetting::currentSetting();

    if (!m_currentBlock) {
        return;
    }

    QPoint pos = m_currentBlock->pos();

    if (event->key() == setting.keyUp) {
        m_currentBlock->rotateLeft();
        if (m_currentBlock->intersect(&m_board)) {
            m_currentBlock->rotateRight();
        }
    }
    else if (event->key() == setting.keyDown) {
        // 快速下落
        m_timer.setInterval(16);
        QSound::play(":/assets/sound_collect.wav");
    }
    else if (event->key() == setting.keyLeft) {
        m_currentBlock->setPos(pos.x() - 1, pos.y());
        if (m_currentBlock->intersect(&m_board)) {
            m_currentBlock->setPos(pos);
        }
        QSound::play(":/assets/sound_click.wav");
    }
    else if (event->key() == setting.keyRight) {
        m_currentBlock->setPos(pos.x() + 1, pos.y());
        if (m_currentBlock->intersect(&m_board)) {
            m_currentBlock->setPos(pos);
        }
        QSound::play(":/assets/sound_click.wav");
    }
    else if (event->key() == setting.keyPause) {
        setPause(!m_pause);
    }

    this->update(); // 刷新显示
}

// 按键弹起
void FormGame::keyReleaseEvent(QKeyEvent* event)
{
}

// 计时器事件
void FormGame::timerEvent(QTimerEvent*)
{
}

void FormGame::onTimer()
{
    // 是否暂停
    if (m_pause || m_end) {
        return;
    }

    // 执行清理
    if (m_cleaning) {
        if (this->clean()) {
            ui->labelScore->setText(QString::number(m_score));
            QSound::play(":/assets/sound_e_clean.wav");
        }
        else {
            // 标记停止清理
            m_cleaning = false;

            // 随机下一个
            randomBlock();

            // 判断游戏是否结束
            if (m_currentBlock->intersect(&m_board)) {
                m_end = true;

                // 添加排行榜
                history.add(FormSetting::currentSetting().user, m_score);
                history.save("scores.xml");
            }
        }

        this->update(); // 刷新显示
        return;         // 返回
    }

    // 当前方块下落
    if (blockDown() == false) {
        m_board.blt(m_currentBlock);

        // 还原计时器速度
        if (m_timer.interval() != m_speed) {
            m_timer.setInterval(m_speed);
        }

        // 标记开始清理逻辑
        m_cleaning = true;
    }


    this->update(); // 刷新显示
}

// 绘制事件
void FormGame::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制背景
    QImage bg = QImage(FormSetting::currentSetting().background);
    painter.drawImage(this->rect(), bg);

    m_board.draw(painter, 20, 20);

    // 绘制下一个
    int w = m_board.width();
    w *= BOX_SIZE;
    w += 60;

    painter.fillRect(QRect(w - 4, 50 - 4, 4 * BOX_SIZE + 8, 4 * BOX_SIZE + 8), QColor(0, 0, 0, 128));
    if (m_nextBlock) {
        m_nextBlock->draw(painter, w, 50);
    }

    if (!m_cleaning && m_currentBlock) {
        m_currentBlock->draw(painter, 20, 20);
    }

    // 显示分数
    /*
    QString str = QString("分数：%0").arg(m_score);
    painter.setFont(QFont("msyh", 20));
    painter.setPen(Qt::black);
    painter.drawText(w, 250, "分数");
    painter.drawText(w, 300, "分数");
    */
}

// 开始游戏
void FormGame::start(int w, int h, int speed)
{
    srand(QDateTime::currentDateTime().toTime_t());

    this->resetSize(w, h);

    // 面板大小
    m_board = Board(w, h);

    // 初始化形状
    this->randomBlock();
    this->randomBlock();

    setPause(false);
    m_end      = false;
    m_cleaning = false;
    m_score    = 0;

    // 开始计时器
    m_speed = speed;
    m_timer.start(speed);
    connect(&m_timer, &QTimer::timeout, this, &FormGame::onTimer);

    // 播放音乐
    musicPlay(FormSetting::currentSetting().bgm);
}

// 重置窗口大小
void FormGame::resetSize(int w, int h)
{
    // 计算窗口大小
    QSize size = QSize(w * BOX_SIZE + 200, h * BOX_SIZE + 40);
    this->setFixedSize(size);

    // 按钮位置
    ui->widgetButtons->move(this->width() - ui->widgetButtons->width() - 20, this->height() - ui->widgetButtons->height());
}

// 保存游戏
bool FormGame::save(QString filename)
{
    if (!m_currentBlock || !m_nextBlock) {
        qDebug() << "block 不能是空";
        return false;
    }

    // 打开文件
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(nullptr, "错误", "文件创建失败。");
        return false;
    }

    // 创建 xml
    QDomDocument doc;

    // 初始化 xml 头
    QDomProcessingInstruction ins;
    ins = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(ins);

    // 添加根节点
    QDomElement root = doc.createElement("game");
    doc.appendChild(root);

    // 保存当前所有状态
    QDomElement state = doc.createElement("state");
    state.setAttribute("timer", m_timer.interval());
    state.setAttribute("speed", m_speed);
    state.setAttribute("pause", m_pause);
    state.setAttribute("end", m_end);
    state.setAttribute("cleaning", m_cleaning);
    state.setAttribute("score", m_score);

    root.appendChild(state);

    // 保存当前 block
    QDomElement currentNode = m_currentBlock->save(root);
    currentNode.setAttribute("usage", "current");

    // 下一个 block
    QDomElement nextNode = m_nextBlock->save(root);
    nextNode.setAttribute("usage", "next");

    // 保存面板
    QDomElement boardNode = m_board.save(root);
    boardNode.setAttribute("usage", "board");

    // 保存到文件
    QTextStream stm(&file);
    doc.save(stm, 4); // 缩进 4 格
    file.close();

    return true;
}

// 加载游戏
bool FormGame::load(QString filename)
{
    QDomDocument doc;

    // 打开文件
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(nullptr, "错误", "文件打开失败。");
        return false;
    }

    if (!doc.setContent(&file)) {
        QMessageBox::warning(nullptr, "错误", "XML 解析失败。");
        file.close();
        return false;
    }
    file.close();

    // 检查根节点
    QDomElement root = doc.documentElement();
    if (root.isNull() || root.nodeName() != "game") {
        QMessageBox::warning(nullptr, "错误", "XML 格式不正确。");
        return false;
    }

    // 重置游戏
    m_timer.stop();
    if (m_currentBlock) {
        delete m_currentBlock;
    }
    if (m_nextBlock) {
        delete m_nextBlock;
    }

    // 读取 block
    QDomElement blockNode = root.firstChildElement("block");
    while (!blockNode.isNull()) {
        QString usage = blockNode.attribute("usage");

        if (usage == "board") {
            m_board.load(blockNode);
        }
        else if (usage == "current") {
            m_currentBlock = createFromName(blockNode.attribute("name"));
            if (m_currentBlock) {
                m_currentBlock->load(blockNode);
            }
        }
        else if (usage == "next") {
            m_nextBlock = createFromName(blockNode.attribute("name"));
            if (m_nextBlock) {
                m_nextBlock->load(blockNode);
            }
        }

        // 下一个节点
        blockNode = blockNode.nextSiblingElement("block");
    }

    // 读取游戏状态
    QDomElement state = root.firstChildElement("state");
    if (!state.isNull()) {
        m_speed    = state.attribute("speed", "1000").toInt();
        m_pause    = state.attribute("pause", "1").toInt();
        m_end      = state.attribute("end", "0").toInt();
        m_cleaning = state.attribute("cleaning", "0").toInt();
        m_score    = state.attribute("score", "0").toInt();

        m_timer.start(state.attribute("timer").toInt());
    }
    else {
        return false;
    }

    // 重置窗口大小
    resetSize(m_board.width(), m_board.height());

    this->setPause(m_pause);

    return true;
}

// 根据名字创建 block
Block* FormGame::createFromName(QString name)
{
    if (name == "BlockI") {
        return new BlockI;
    }
    else if (name == "BlockO") {
        return new BlockO;
    }
    else if (name == "BlockL") {
        return new BlockL;
    }
    else if (name == "BlockJ") {
        return new BlockJ;
    }
    else if (name == "BlockZ") {
        return new BlockZ;
    }
    else if (name == "BlockS") {
        return new BlockS;
    }
    else if (name == "BlockT") {
        return new BlockT;
    }

    return nullptr;
}

// 暂停
void FormGame::setPause(bool value)
{
    m_pause = value;
    if (m_pause) {
        ui->labelPause->move((this->width() - ui->labelPause->width()) / 2, (this->height() - ui->labelPause->height()) / 2);
        ui->labelPause->setVisible(true);
    }
    else {
        ui->labelPause->setVisible(false);
    }
}

// 随机一个方块
Block* FormGame::randomBlock()
{
    // 交换当前形状
    if (m_currentBlock) {
        delete m_currentBlock;
    }

    m_currentBlock = m_nextBlock;
    if (m_currentBlock) {
        m_currentBlock->setPos((m_board.width() - m_currentBlock->width()) / 2, 0);
    }

    // 随机形状
    int n = rand() % 7;
    // n = 0;
    switch (n) {
    case 0:
        m_nextBlock = new BlockI();
        break;
    case 1:
        m_nextBlock = new BlockL();
        break;
    case 2:
        m_nextBlock = new BlockJ();
        break;
    case 3:
        m_nextBlock = new BlockZ();
        break;
    case 4:
        m_nextBlock = new BlockS();
        break;
    case 5:
        m_nextBlock = new BlockO();
        break;
    case 6:
        m_nextBlock = new BlockT();
        break;
    default:
        break;
    }

    // 随机旋转
    n = rand() % 4;
    for (int i = 0; i < n; ++i) {
        m_nextBlock->rotateLeft();
    }
    m_nextBlock->setPos((4 - m_nextBlock->width()) / 2, (4 - m_nextBlock->height()) / 2);

    return m_nextBlock;
}

// 方块下落
bool FormGame::blockDown()
{
    if (!m_currentBlock) {
        return false;
    }

    QPoint pos = m_currentBlock->pos();

    // 下落一步
    m_currentBlock->setPos(pos.x(), pos.y() + 1);

    // 判断是否发生碰撞
    if (m_currentBlock->intersect(&m_board)) {
        // 还原位置
        m_currentBlock->setPos(pos);
        return false;
    }

    return true;
}

// 消除，从最底一行检测，如果有可以消除的行，消除并返回 true
// 如果没有可以消除的行，返回 false
bool FormGame::clean()
{
    for (int i = m_board.height() - 1; i > 0; --i) {
        if (m_board.checkLine(i)) {
            // 把这行往上的所有行往下移动
            for (int j = i - 1; j >= 0; --j) {
                m_board.moveLine(j, j + 1);
            }

            // 加分，一个方块 10 分
            m_score += m_board.width() * 10;

            return true;
        }
    }

    return false;
}
