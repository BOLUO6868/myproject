#include "blockI.h"

BlockI::BlockI() : Block("BlockI", 4, 1)
{
    this->setColor(Qt::cyan);

    this->set(0, 0, 1);
    this->set(1, 0, 1);
    this->set(2, 0, 1);
    this->set(3, 0, 1);
}
