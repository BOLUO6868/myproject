#include "blockO.h"

BlockO::BlockO() : Block("BlockO", 2, 2)
{
    this->setColor(Qt::cyan);

    this->set(0, 0, 1);
    this->set(0, 1, 1);
    this->set(1, 0, 1);
    this->set(1, 1, 1);
}
