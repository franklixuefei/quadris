#ifndef __IBLOCK_H__
#define __IBLOCK_H__
#include <iostream>
#include "block.h"

class IBlock : public Block {//IBlock is a derived class of the Block
  public:
   IBlock(int level, char blockType = 'I');//constructor
   Vector* genBlock();
};

#endif
