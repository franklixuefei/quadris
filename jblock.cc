#include <iostream>
#include "jblock.h"
using namespace std;

JBlock::JBlock(int level, char blockType): 
  Block(blockType)
{
  this->blockType = blockType;
  rotPos = NORTH;
  blockPos_X = 0;
  blockPos_Y = 2;
  this->level = level;
  numAliveCells = 0;
}

Vector* JBlock::genBlock() {
  int x = blockPos_X;
  int y = blockPos_Y;
  switch(rotPos) {
    case NORTH:
      block[0].x = 0 + x;
		block[0].y = 0 + y;

		block[1].x = 0 + x;
		block[1].y = 1 + y;

		block[2].x = 1 + x;
		block[2].y = 1 + y;

		block[3].x = 2 + x;
		block[3].y = 1 + y;
      break;
    case EAST:
      block[0].x = 0 + x;
		block[0].y = -1 + y;

		block[1].x = 1 + x;
		block[1].y = -1 + y;

		block[2].x = 0 + x;
		block[2].y = 0 + y;

		block[3].x = 0 + x;
		block[3].y = 1 + y;
      break;
    case SOUTH:
      block[0].x = 0 + x;
		block[0].y = 0 + y;

		block[1].x = 1 + x;
		block[1].y = 0 + y;

		block[2].x = 2 + x;
		block[2].y = 0 + y;

		block[3].x = 2 + x;
		block[3].y = 1 + y;
      break;
    case WEST:
      block[0].x = 1 + x;
		block[0].y = -1 + y;

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
