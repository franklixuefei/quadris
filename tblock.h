#ifndef __TBLOCK_H__
#define __TBLOCK_H__
#include <iostream>
#include "block.h"

class TBlock : public Block {
  public:
   TBlock(int level, char blockType = 'T');
   Vector* genBlock();
};

#endif
