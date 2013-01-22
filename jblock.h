#ifndef __JBLOCK_H__
#define __JBLOCK_H__
#include <iostream>
#include "block.h"

class JBlock : public Block {//JBlock is a derived class of the Block
  public:
   JBlock(int level, char blockType = 'J');
   Vector* genBlock();
};

#endif
