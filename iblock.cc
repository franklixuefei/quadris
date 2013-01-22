#include <iostream>
#include "iblock.h"
using namespace std;

IBlock::IBlock(int level, char blockType)://initialize the IBlock
  Block(blockType)
{
  this->blockType = blockType;
  rotPos = NORTH;
  blockPos_X = 0;
  blockPos_Y = 3;
  this->level = level;
  numAliveCells = 0;
}

Vector* IBlock::genBlock() {//generate an IBlock according to its position on board and its rotation position. The same idea is used in other 6 types of blocks.
  int x = blockPos_X;
  int y = blockPos_Y;
  switch(rotPos) {
    case NORTH://we define four rotation position: NORTH, EAST, SOUTH,WEST with the corresponding coordinates relationship.The same idea is used in other 6 types of blocks.
      block[0].x = 0 + x;
		block[0].y = 0 + y;

		block[1].x = 1 + x;
		block[1].y = 0 + y;

		block[2].x = 2 + x;
		block[2].y = 0 + y;

		block[3].x = 3 + x;
		block[3].y = 0 + y;
      break;
    case EAST:
      block[0].x = 0 + x;
		block[0].y = -3 + y;

		block[1].x = 0 + x;
		block[1].y = -2 + y;

		block[2].x = 0 + x;
		block[2].y = -1 + y;

		block[3].x = 0 + x;
		block[3].y = 0 + y;
      break;
    case SOUTH:
      block[0].x = 0 + x;
		block[0].y = 0 + y;

		block[1].x = 1 + x;
		block[1].y = 0 + y;

		block[2].x = 2 + x;
		block[2].y = 0 + y;

		block[3].x = 3 + x;
		block[3].y = 0 + y;
      break;
    case WEST:
      block[0].x = 0 + x;
		block[0].y = -3 + y;

		block[1].x = 0 + x;
		block[1].y = -2 + y;

		block[2].x = 0 + x;
		block[2].y = -1 + y;

		block[3].x = 0 + x;
		block[3].y = 0 + y;
      break;
  }
  return block; 
}
