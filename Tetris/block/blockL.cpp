#include "blockL.h"

// X
// X
// X X

BlockL::BlockL() : Block("BlockL", 2, 3)
{
    this->setColor(QColor(255, 128, 0, 255));

    this->set(0, 0, 1);
    this->set(0, 1, 1);
    this->set(0, 2, 1);
    this->set(1, 2, 1);
}

//   X
//   X
// X X

BlockJ::BlockJ() : Block("BlockJ", 2, 3)
{
    this->setColor(Qt::yellow);

    this->set(0, 2, 1);
    this->set(1, 0, 1);
    this->set(1, 1, 1);
    this->set(1, 2, 1);
}
