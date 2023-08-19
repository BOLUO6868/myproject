#include "blockZ.h"

// X X
//   X X
BlockZ::BlockZ() : Block("BlockZ", 3, 2)
{
    this->setColor(Qt::red);

    this->set(0, 0, 1);
    this->set(1, 0, 1);
    this->set(1, 1, 1);
    this->set(2, 1, 1);
}

//   X X
// X X
BlockS::BlockS() : Block("BlockS", 3, 2)
{
    this->setColor(Qt::green);

    this->set(0, 1, 1);
    this->set(1, 0, 1);
    this->set(1, 1, 1);
    this->set(2, 0, 1);
}
