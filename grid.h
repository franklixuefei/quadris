#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include "block.h"
#include "cell.h"
#include "window.h"

const int MAX_ROW = 18;
const int MAX_COL = 10;

class Grid {
   Cell **theGrid;
   Xwindow *pxw1, *pxw2;
  public:
   Grid(Xwindow *xw1, Xwindow *xw2);
   ~Grid();
   void setBlockLiving(Block *ablock);
   void setNextBlockLiving(Block *ablock);
   void setBlockDeath(Block *ablock);
   void setNextBlockDeath(Block *ablock);
   void setLineDeath(int y); //
   void moveLineDown(int y); // move line y down by one.(to y + 1)
   void setBlockFixed(Block *ablock);
   bool isFixed(int x, int y); //
   bool isLiving(int x, int y); //
   bool isFixedLiving(int x, int y); //determine whether the cell at x, y is alive AND fixed.
   Cell& getCell(int i, int j);
   friend std::ostream& operator<<(std::ostream &out, const Grid &g);
};

#endif
   
