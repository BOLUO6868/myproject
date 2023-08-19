#include "blockT.h"

BlockT::BlockT() : Block("BlockT", 3, 2)
{
    this->setColor(Qt::magenta);

    this->set(0, 0, 1);
    this->set(1, 0, 1);
    this->set(2, 0, 1);

    this->set(1, 1, 1);
}
