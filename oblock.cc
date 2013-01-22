#include <iostream>
#include "oblock.h"
using namespace std;

OBlock::OBlock(int level, char blockType):
  Block(blockType)
{
  this->blockType = blockType;
  rotPos = NORTH;
  blockPos_X = 0;
  blockPos_Y = 2;
  this->level = level;
  numAliveCells = 0;
}

Vector* OBlock::genBlock() {
  int x = blockPos_X;
  int y = blockPos_Y;
  switch(rotPos) {
    case NORTH:
    case EAST:
    case SOUTH:
    case WEST:
      block[0].x = 0 + x;
		block[0].y = 0 + y;

		block[1].x = 1 + x;
		block[1].y = 0 + y;

		block[2].x = 0 + x;
		block[2].y = 1 + y;

		block[3].x = 1 + x;
		block[3].y = 1 + y;
      break;
  }
  return block; 
}
