#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include <iostream>
#include "block.h"

class SBlock : public Block {
  public:
   SBlock(int level, char blockType = 'S');
   Vector* genBlock();
};

#endif
