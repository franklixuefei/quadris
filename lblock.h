#ifndef __LBLOCK_H__
#define __LBLOCK_H__
#include <iostream>
#include "block.h"

class LBlock : public Block {
  public:
   LBlock(int level, char blockType = 'L');
   Vector* genBlock();
};

#endif
