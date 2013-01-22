#include <iostream>
#include "block.h"
using namespace std;

Block::Block(char blockType) {//initialize each cell of the block with (0,0) coordinates.
   for (int i = 0; i < 4; ++i) {
      block[i].x = 0;
      block[i].y = 0;
   }
}
   
Block::~Block() {}

int Block::getRotPos() {//return the rotation position of a block
   return rotPos;
}

char Block::getBlockType() {//return the type of a block
   return blockType;
}

void Block::setRotPos(int rp) {//set the rotation position
   rotPos = rp;
}

void Block::RotClock() {//if we rotate the block clockwise, we just use the coordinates of the rotation of another direction with 90 degrees difference.
   if (rotPos == WEST) rotPos = NORTH;
   else rotPos++;
}

void Block::RotCounterClock() {//same idea as in the RotClock, just doing it in the opposite direction.
   if (rotPos == NORTH) rotPos = WEST;
   else rotPos--;
}

void Block::setBlockPos(int x_change, int y_change) {//adding x_change, and y_change to the x and y coordinates of a block.
   blockPos_X += x_change;
   blockPos_Y += y_change;
}

void Block::setBlockPosTo(int x, int y) {//set the block position to x and y.
   blockPos_X = x;
   blockPos_Y = y;
}

Vector* Block::getBlockCoords() {//return the copy version coordinates of a block
   Vector* theBlock = new Vector[4];
   for (int i = 0; i < 4; ++i) {
      theBlock[i].x = block[i].x;
      theBlock[i].y = block[i].y;
   }
   return theBlock;
}

Vector* Block::getBlockCoordsNoCopying() {//return the Vector block
   return block;
}

int Block::getBlockPos_X() {//return the blockPos_X
   return blockPos_X;
}

int Block::getBlockPos_Y() {//return the blockPos_Y
   return blockPos_Y;
}

int Block::getLevel() {//return the level of the Block
   return level;
}

void Block::incrementLevel() {//increase the level by one
   level++;
}
   
void Block::decrementLevel() {//decrease the level by one
   level--;
}

void Block::incrementAliveCell() {//increase the alive cells' number by one
   numAliveCells++;
}

void Block::decrementAliveCell() {//decrease the alive cells' number by one
   numAliveCells--;
}

int Block::getNumAliveCells() {//return the number of alive cells
   return numAliveCells;
}







