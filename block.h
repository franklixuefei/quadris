#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


struct Vector {//we use the structure Vector to store the value of a coordinate.
   int x;
   int y;
};

class Block {//the Block is a base class of seven inheritance class, "IBlock","JBlock","LBlock","OBlock","SBlock","TBlock","ZBlock"
  protected:
   int rotPos;//rotPos stands for the direction of a block. 0,1,2,3 represents 4 directions that are differentiated by 90 degree.
   char blockType; //blockType is one of "I", "J", "L", "O", "S", "T", "Z"
   int blockPos_X, blockPos_Y;//represents the postions of a block. If blockPos_X is increased by one, then each four cells of the block's x-coordinates are increased by one
   Vector block[4];//store the coordinates of each cell in the block
   int level; // stores the level value when a block is generated.
   int numAliveCells;//the number of the alive cells
  public:
   Block(char blockType);
   virtual ~Block();
   virtual Vector *genBlock() = 0;//abstract function
   void RotClock();//rotate the block clockwise
   void RotCounterClock();//rotate the block counter clockwise
   int getRotPos();//return the value of rotPos
   void setRotPos(int rp);//change the value of rotPos
   char getBlockType();//return the blockType
   void setBlockPos(int x_change, int y_change); // right and down are positive
   void setBlockPosTo(int x, int y);//change the block's position to (x,y)
   Vector* getBlockCoords(); // the Vector* of this block is copied, so need deleting.
   Vector* getBlockCoordsNoCopying(); // return block directly.
   int getBlockPos_X();//return blockPos_X
   int getBlockPos_Y();//return blockPos_Y
   int getLevel(); // used for calculating scores.
   void incrementLevel();//increase the level value by 1
   void decrementLevel();//decrease the level value by 1
   void incrementAliveCell(); // increase numAliveCells by 1
   void decrementAliveCell(); // decrease numAliveCells by 1
   int getNumAliveCells(); //return the value of numAliveCells
};

#endif

