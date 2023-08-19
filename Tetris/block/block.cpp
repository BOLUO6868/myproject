#include "block.h"
#include "../formSetting.h"

Block::Block(QString name, int w, int h) :
    m_name(name),
    m_data(),
    m_pos(0, 0),
    m_color(Qt::black)
{
    this->resize(m_data, w, h);
}

// 返回名字
QString Block::name() const
{
    return m_name;
}

// 判断是否为空
bool Block::empty() const
{
    return width() == 0 || height() == 0;
}

// 更改大小
void Block::resize(QVector<QVector<int>>& a, int w, int h)
{
    a.resize(h);
    for (auto& line: a) {
        line.resize(w);
    }
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

// 返回位置
QPoint Block::pos() const
{
    return m_pos;
}

// 设置位置
void Block::setPos(QPoint value)
{
    m_pos = value;
}

void Block::setPos(int x, int y)
{
    m_pos = QPoint(x, y);
}

// 返回颜色
QColor Block::color() const
{
    return m_color;
}

// 设置颜色
void Block::setColor(QColor color)
{
    m_color = color;
}

// 检测坐标是否在范围内
bool Block::checkPos(int x, int y) const
{
    return x >= 0 && x < this->width() && y >= 0 && y < this->height();
}

// 获取格子的值
int Block::get(int x, int y) const
{
    if (checkPos(x, y)) {
        return m_data[y][x];
    }
    else {
        // 范围外的返回 -1
        return -1;
    }
}

// 设置格子的值
void Block::set(int x, int y, int value)
{
    if (checkPos(x, y)) {
        m_data[y][x] = value;
    }
}

// 左旋转
void Block::rotateLeft()
{
    int w = this->width();
    int h = this->height();

    if (w == 0 || h == 0) { // empty
        return;
    }

    // 构造一个临时数据
    QVector<QVector<int>> temp;
    resize(temp, h, w);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            temp[w - x - 1][y] = m_data[y][x];
        }
    }

    m_pos += QPoint((w - h) / 2, (h - w) / 2);

    // 交换
    m_data.swap(temp);
}

// 左旋转
void Block::rotateRight()
{
    int w = this->width();
    int h = this->height();

    if (w == 0 || h == 0) { // empty
        return;
    }

    // 构造一个临时数据
    QVector<QVector<int>> temp;
    resize(temp, h, w);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            temp[x][h - y - 1] = m_data[y][x];
        }
    }

    m_pos += QPoint((w - h) / 2, (h - w) / 2);

    // 交换
    m_data.swap(temp);
}

// 碰撞测试
bool Block::intersect(Block* other) const
{
    int tx, ty;
    int b1, b2;

    if (!other) {
        return false;
    }

    for (int y = 0; y < this->height(); ++y) {
        for (int x = 0; x < this->width(); ++x) {
            // 计算本方块的坐标，在另外一个方块哪里
            tx = m_pos.x() + x - other->pos().x();
            ty = m_pos.y() + y - other->pos().y();

            b1 = m_data[y][x];
            b2 = other->get(tx, ty);

            if (b2 < 0) { // 超出了范围
                return true;
            }
            else {
                // 两个方块是否都不为空
                if (b1 && b2) {
                    return true;
                }
            }
        }
    }

    return false;
}

// 判断一行是否全部是方块
bool Block::checkLine(int y) const
{
    if (checkPos(0, y)) {
        for (int i = 0; i < this->width(); ++i) {
            if (m_data[y][i] == 0) {
                return false;
            }
        }

        return true;
    }
    else {
        return false;
    }
}

// from 行移动到 to 行
void Block::moveLine(int yFrom, int yTo)
{
    if (checkPos(0, yFrom) && checkPos(0, yTo)) {
        m_data[yTo] = m_data[yFrom];
    }
}

// 将另外一个性质复制到这个形状
void Block::blt(Block* other)
{
    int tx, ty;

    if (!other) {
        return;
    }

    for (int y = 0; y < other->height(); ++y) {
        for (int x = 0; x < other->width(); ++x) {
            tx = other->pos().x() + x - m_pos.x();
            ty = other->pos().y() + y - m_pos.y();

            if (other->get(x, y)) {
                this->set(tx, ty, 1);
            }
        }
    }
}

// 绘制
void Block::draw(QPainter& painter, float posX, float posY)
{
    QRectF rect  = QRectF(0.0f, 0.0f, BOX_SIZE, BOX_SIZE);
    QBrush brush = QBrush(m_color);

    posX += m_pos.x() * BOX_SIZE;
    posY += m_pos.y() * BOX_SIZE;

    for (int y = 0; y < this->height(); ++y) {
        for (int x = 0; x < this->width(); ++x) {
            if (m_data[y][x]) {
                rect.moveTo(posX + x * BOX_SIZE, posY + y * BOX_SIZE);
                painter.fillRect(rect.adjusted(0.5f, 0.5f, -0.5f, -0.5f), brush);
            }
            else {
                // rect.moveTo(posX + x * BOX_SIZE, posY + y * BOX_SIZE);
                // painter.drawRect(rect.adjusted(0.5f, 0.5f, -0.5f, -0.5f));
            }
        }
    }
}

// 转换成字符串
QString Block::dataToString() const
{
    // return m_name + "|" +
    QString str;
    // str.push_back('{');
    for (int y = 0; y < this->height(); ++y) {
        for (int x = 0; x < this->width(); ++x) {
            if (m_data[y][x]) {
                str.push_back('1');
            }
            else {
                str.push_back('0');
            }

            if (x == this->width() - 1) {
                str.push_back(';');
            }
            else {
                str.push_back(',');
            }
        }
    }
    // str.push_back('}');

    return str;
}

// 从字符串解析 data
bool Block::dataFromString(int w, int h, QString str)
{
    if (str.size() < (w + 1) * h) {
        return false;
    }

    resize(m_data, w, h);
    QStringList lines = str.split(';');          // 拆分行
    for (int y = 0; y < h; ++y) {
        QStringList items = lines[y].split(','); // 拆分列
        for (int x = 0; x < w; ++x) {
            m_data[y][x] = items[x] == '0' ? 0 : 1;
        }
    }

    return true;
}

// 保存到一个 xml 节点中
QDomElement Block::save(QDomElement node)
{
    QDomDocument doc = node.ownerDocument();

    if (doc.isNull()) {
        return QDomElement();
    }

    // block
    QDomElement blockNode = doc.createElement("block");

    // 属性
    blockNode.setAttribute("name", m_name);
    blockNode.setAttribute("x", QString::number(m_pos.x()));
    blockNode.setAttribute("y", QString::number(m_pos.y()));
    blockNode.setAttribute("color", QString::number(m_color.rgba()));

    blockNode.setAttribute("w", QString::number(this->width()));
    blockNode.setAttribute("h", QString::number(this->height()));
    QDomNode dataNode = doc.createTextNode(this->dataToString());
    blockNode.appendChild(dataNode);

    node.appendChild(blockNode);

    return blockNode;
}

// 从一个 xml 节点读取
bool Block::load(QDomElement node)
{
    if (node.isNull()) {
        return false;
    }

    int x        = node.attribute("x", 0).toInt();
    int y        = node.attribute("y", 0).toInt();
    int w        = node.attribute("w", 0).toInt();
    int h        = node.attribute("h", 0).toInt();
    QColor color = node.attribute("color").toUInt();
    QString data = node.firstChild().toText().data();

    if (w == 0 || h == 0) {
        return false;
    }

    m_pos   = QPoint(x, y);
    m_color = color;

    return dataFromString(w, h, data);
}
