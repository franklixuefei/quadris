#ifndef __BLOCKANIMATION_H__
#define __BLOCKANIMATION_H__
#include <iostream>
#include <vector>
#include <string>
#include "block.h"
#include "grid.h"

class BlockAnimation {
   Grid *g;
   bool can_Rot;
   bool can_Move;
   bool rotClockTried;
   bool rotCounterClockTried;
   bool lineFilled; // determine if a line filled
   std::vector<Block*> vb; // for storing dropped blocks
   int fixedRowUpperBound;
   int linesRemoved; // lines removed after a single drop.
   int blocksRemoved; // for determining whether blocks removed in one drop
   std::vector<int> levelsRemoved; // stores levels of blocks removed.
  public:
   Block *currentBlock;
   BlockAnimation(Grid *g);
   ~BlockAnimation();
   void moveLeft(int time = 1);
   void moveRight(int time = 1);
   void moveDown(int time = 1);
   void moveUp(int time = 1);
   void rotateClock(int time = 1);
   void rotateCounterClock(int time = 1);
   void dropBlock();
   void checkInBounds(std::string try_dir);
   void pushBlock(); // push currentBlock into vector, and update fixedRowUpperBound.
   void checkLineFilled(int y); // check line y is filled or not
   void deleteFilledLines(); // also move down above fixed blocks.
   int getLinesRemoved();
   int getBlocksRemoved();
   std::vector<int> getLevelsRemoved(); //
   void clearLevelsRemoved(); // reset levelsRemoved to empty vector.
   void resetLinesRemoved(); // reset linesRemoved to 0;
   bool getCanMove();
   void clearVb();
    void clearBlocksInBound();
};

#endif
