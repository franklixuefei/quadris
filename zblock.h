#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include <iostream>
#include "block.h"

class ZBlock : public Block {
  public:
   ZBlock(int level, char blockType = 'Z');
   Vector* genBlock();
};

#endif
