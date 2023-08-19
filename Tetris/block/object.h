#ifndef OBJECT_H
#define OBJECT_H

#include <QPainter>
#include <QtXml> // xml 支持

class Object
{
public:
    Object();
    virtual ~Object();

    // 纯虚函数，绘制
    virtual void draw(QPainter& painter, float posX, float posY) = 0;

};

#endif // OBJECT_H
