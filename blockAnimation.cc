#include <iostream>
#include "blockAnimation.h"
using namespace std;

BlockAnimation::BlockAnimation(Grid *g):
   g(g), can_Rot(true), can_Move(true), rotClockTried(false),
   rotCounterClockTried(false), lineFilled(false),
   fixedRowUpperBound(MAX_ROW-1), linesRemoved(0), blocksRemoved(0),
   currentBlock(NULL) {}
   
BlockAnimation::~BlockAnimation() {
   vector<Block*>::const_iterator cii;
   for (cii = vb.begin(); cii != vb.end(); ++cii) {
      if (*cii) delete *cii;
   }
   vb.clear();
}

void BlockAnimation::rotateClock(int time) {
   if (time) {
      if (currentBlock) {
         checkInBounds("clock");
         if (can_Rot) {
            g->setBlockDeath(currentBlock);
            for (int i = 0; i < time; ++i) {
               checkInBounds("clock");
               if (can_Rot) {
                  currentBlock->RotClock();
                  currentBlock->genBlock();
               } else break;
            }
            g->setBlockLiving(currentBlock);
         }
      }
   }
}

void BlockAnimation::rotateCounterClock(int time) {
   if (time) {
      if (currentBlock) {
         checkInBounds("counterclock");
         if (can_Rot) {
            g->setBlockDeath(currentBlock);
            for (int i = 0; i < time; ++i) {
               checkInBounds("counterclock");
               if (can_Rot) {
                  currentBlock->RotCounterClock();
                  currentBlock->genBlock();
               } else break;
            }
            g->setBlockLiving(currentBlock);
         }
      }
   }
}

void BlockAnimation::moveLeft(int time) {
   if (time) {
      if (currentBlock) {
         checkInBounds("left");
         if (can_Move) {
            g->setBlockDeath(currentBlock);
            for (int i = 0; i < time; ++i) {
               checkInBounds("left");
               if (can_Move) {
                  currentBlock->setBlockPos(-1, 0);
                  currentBlock->genBlock();
               } else break;
            }
            g->setBlockLiving(currentBlock);
         }
      }
   }
}

void BlockAnimation::moveRight(int time) {
   if (time) {
      if (currentBlock) {
         checkInBounds("right");
         if (can_Move) {
            g->setBlockDeath(currentBlock);
            for (int i = 0; i < time; ++i) {
               checkInBounds("right");
               if (can_Move) {
                  currentBlock->setBlockPos(1, 0);
                  currentBlock->genBlock();
               } else break;
            }
            g->setBlockLiving(currentBlock);
         }
      }
   }
}

void BlockAnimation::moveUp(int time) {
   if (time) {
      if (currentBlock) {
         checkInBounds("up");
         if (can_Move) {
            g->setBlockDeath(currentBlock);
            for (int i = 0; i < time; ++i) {
               checkInBounds("up");
               if (can_Move) {
                  currentBlock->setBlockPos(0, -1);
                  currentBlock->genBlock();
               } else break;
            }
            g->setBlockLiving(currentBlock);
         }
      }
   }
}


void BlockAnimation::dropBlock() {
   if (currentBlock) {
      checkInBounds("down");
      if (can_Move) {
         g->setBlockDeath(currentBlock);
         for (int i = 0; i < MAX_ROW; ++i) {
            checkInBounds("down");
            if (can_Move) {
               currentBlock->setBlockPos(0, 1);
               currentBlock->genBlock();
            } else break;
         }
         g->setBlockLiving(currentBlock);
      }
   }
}
   
   
void BlockAnimation::moveDown(int time) {
   if (time) {
      if (currentBlock) {
         checkInBounds("down");
         if (can_Move) {
            g->setBlockDeath(currentBlock);
            for (int i = 0; i < time; ++i) {
               checkInBounds("down");
               if (can_Move) {
                  currentBlock->setBlockPos(0, 1);
                  currentBlock->genBlock();
               } else break;
            }
            g->setBlockLiving(currentBlock);
         }
      }
   }
}
   
void BlockAnimation::checkInBounds(string try_dir) {
   // mutate can_Move, can_Rot
   // 3 aspects:
   //    1. check if in board -- done
   //    2. check if overlapped -- done
   //    3. check if newly born block has room to survive -- done
   if (currentBlock) {
      Vector* theBlock = currentBlock->getBlockCoords();
      if (try_dir == "new") {
         // do nothing
      } else if (try_dir == "left") {
         for (int i = 0; i < 4; ++i) theBlock[i].x -= 1;
      } else if (try_dir == "right") {
         for (int i = 0; i < 4; ++i) theBlock[i].x += 1;
      } else if (try_dir == "up") {
         for (int i = 0; i < 4; ++i) theBlock[i].y -= 1;
      } else if (try_dir == "down") {
         for (int i = 0; i < 4; ++i) theBlock[i].y += 1;
      } else if (try_dir == "clock") {
         currentBlock->RotClock();
         rotClockTried = true;
         currentBlock->genBlock();
         delete [] theBlock;
         theBlock = currentBlock->getBlockCoords();
      } else if (try_dir == "counterclock") {
         currentBlock->RotCounterClock();
         rotCounterClockTried = true;
         currentBlock->genBlock();
         delete [] theBlock;
         theBlock = currentBlock->getBlockCoords();
      }
      for (int i = 0; i < 4; ++i) {
         if (theBlock[i].x > MAX_COL-1 || theBlock[i].x < 0
            || theBlock[i].y > MAX_ROW-1 || theBlock[i].y < 0
            || g->isFixedLiving(theBlock[i].x, theBlock[i].y)) { 
            can_Move = false;
            can_Rot= false;
            break;
         } else { 
            can_Move = true;
            can_Rot = true;
         }
      }
      if (rotClockTried) {
         currentBlock->RotCounterClock();
         rotClockTried = false;
         currentBlock->genBlock();          
        
      } else if (rotCounterClockTried) {
         currentBlock->RotClock();
         rotCounterClockTried = false;
         currentBlock->genBlock();
      }
      delete [] theBlock;
   }
}

void BlockAnimation::pushBlock() {
   vb.push_back(currentBlock);
   Vector* realBlock = currentBlock->getBlockCoordsNoCopying();
   if (realBlock[0].y < fixedRowUpperBound) //means realBlock[0] is above original fixedRowUpperBound.
      fixedRowUpperBound = realBlock[0].y; // get the top-most y-coord of fixed blocks
}

void BlockAnimation::checkLineFilled(int y) {
   for (int i = 0; i < MAX_COL; ++i) {
      if (!g->isLiving(i, y)) {
         lineFilled = false;
         return;
      }
   }
   lineFilled = true;
}

void BlockAnimation::deleteFilledLines() {
   for (int i = MAX_ROW-1; i >= fixedRowUpperBound; --i) {
      checkLineFilled(i+linesRemoved);
      if (lineFilled) {
         // set this line death.
         // update linesRemoved.
         // move the above fixed blocks down by 1;
         g->setLineDeath(i+linesRemoved);
         linesRemoved++;
          for (int j = i+linesRemoved-2/*one row above line i*/; j >= fixedRowUpperBound; --j) g->moveLineDown(j);
      }
   }
   // check if there is one or more blocks which have been completely removed from grid.(using Block's method getNumAliveCells())
   // if so, update blocksRemoved.
   vector<Block*>::const_iterator cii;
   for (cii = vb.begin(); cii != vb.end(); ++cii) {
      if(*cii) {
         if ((*cii)->getNumAliveCells() == 0) {
            blocksRemoved++; // for determining whether blocks removed.
            levelsRemoved.push_back((*cii)->getLevel());
         }
      }
   } 
   if (blocksRemoved) {
      for (unsigned int i = 0; i < vb.size(); ++i) {
         if (vb[i]) {
            if (vb[i]->getNumAliveCells() == 0) {
               delete vb[i];
               vb[i] = NULL;
            }
         }
      }
   }
   blocksRemoved = 0;
}

int BlockAnimation::getLinesRemoved() {
   return linesRemoved;
}

int BlockAnimation::getBlocksRemoved() {
   return blocksRemoved;
}

std::vector<int> BlockAnimation::getLevelsRemoved() {
   return levelsRemoved;
}

void BlockAnimation::clearLevelsRemoved() {
   levelsRemoved.clear();
}

void BlockAnimation::resetLinesRemoved() {
   linesRemoved = 0;
}

bool BlockAnimation::getCanMove() {
   return can_Move;
}

void BlockAnimation::clearVb() {
   vector<Block*>::iterator cii;
   for (cii = vb.begin(); cii != vb.end(); ++cii) {
      if (*cii) {
         delete *cii;
         *cii = NULL;
      }
   }
   vb.clear();
}          
        

void BlockAnimation::clearBlocksInBound() {
    for (int i = fixedRowUpperBound; i < MAX_ROW ; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            if(g->getCell(i, j).getIsAlive())g->getCell(i, j).setDeath();
            g->getCell(i, j).setMasterBlock(NULL);//
            g->getCell(i, j).setBlockType(0);
            g->getCell(i, j).setUnfixed(); //
        }
    }
}
