#include <iostream>
#include "grid.h"
using namespace std;

Grid::Grid(Xwindow *xw1, Xwindow *xw2):pxw1(xw1), pxw2(xw2) {
   theGrid = new Cell*[MAX_ROW+3];
   for (int i = 0; i < MAX_ROW+3; ++i) {
      theGrid[i] = new Cell[MAX_COL];
   }
   for (int i = 0; i < MAX_ROW; ++i) {
      for (int j = 0; j < MAX_COL; ++j) {
         theGrid[i][j].setCoords(j*20, 70 + i*20, pxw1, 20, 20);  // width and height are both 20 pix; reserve 50 pix for score and level and time use.
      }
   }
   for (int i = MAX_ROW; i < MAX_ROW+3; ++i) {
      for (int j = 0; j < MAX_COL; ++j) {
         theGrid[i][j].setCoords(60 + j*20, 17+(i-MAX_ROW)*20, pxw2, 20, 20);
      }
   }
}

Grid::~Grid() {
   for (int i = 0; i < MAX_ROW+3; ++i) {
      delete [] theGrid[i];
   }
   delete [] theGrid;
}

void Grid::setBlockLiving(Block *ablock) {
   Vector *theBlock = ablock->genBlock();
   for (int i = 0; i < 4; ++i) {
      theGrid[theBlock[i].y][theBlock[i].x].setBlockType(ablock->getBlockType());
      theGrid[theBlock[i].y][theBlock[i].x].setMasterBlock(ablock);//
      theGrid[theBlock[i].y][theBlock[i].x].setLiving();
   }
}

void Grid::setNextBlockLiving(Block *ablock) {
   int y_Coord = ablock->getBlockPos_Y();
   ablock->setBlockPosTo(0, MAX_ROW);
   Vector *theBlock = ablock->genBlock();
   for (int i = 0; i < 4; ++i) {
      theGrid[theBlock[i].y][theBlock[i].x].setBlockType(ablock->getBlockType());
      theGrid[theBlock[i].y][theBlock[i].x].setMasterBlock(ablock);//
      theGrid[theBlock[i].y][theBlock[i].x].setLiving();
   }
   ablock->setBlockPosTo(0, y_Coord);
}

void Grid::setBlockDeath(Block *ablock) {
   Vector *theBlock = ablock->genBlock();
   for (int i = 0; i < 4; ++i) {
      theGrid[theBlock[i].y][theBlock[i].x].setDeath();
      theGrid[theBlock[i].y][theBlock[i].x].setMasterBlock(NULL);//
      theGrid[theBlock[i].y][theBlock[i].x].setBlockType(0);
      theGrid[theBlock[i].y][theBlock[i].x].setUnfixed(); //
   }
}

void Grid::setNextBlockDeath(Block *ablock) {
   int y_Coord = ablock->getBlockPos_Y();
   ablock->setBlockPosTo(0, MAX_ROW);
   Vector *theBlock = ablock->genBlock();
   for (int i = 0; i < 4; ++i) {
      theGrid[theBlock[i].y][theBlock[i].x].setDeath();
      theGrid[theBlock[i].y][theBlock[i].x].setMasterBlock(NULL);//
      theGrid[theBlock[i].y][theBlock[i].x].setBlockType(0);
   }
   ablock->setBlockPosTo(0, y_Coord);
}

void Grid::setLineDeath(int y) {
   for (int i = 0; i < MAX_COL; ++i) {
      theGrid[y][i].setDeath();
      theGrid[y][i].setBlockType(0);
      theGrid[y][i].setUnfixed();
      theGrid[y][i].setMasterBlock(NULL); //
   }
}


void Grid::moveLineDown(int y) {
   for (int i = 0; i < MAX_COL; ++i) {
      int OrigYCoords = theGrid[y+1][i].getYCoords();
      theGrid[y+1][i] = theGrid[y][i]; // DO NOT forget to use copyctor!!!
      theGrid[y+1][i].setYCoords(OrigYCoords);
      if (theGrid[y][i].getIsAlive()) theGrid[y+1][i].setLiving();
      theGrid[y][i].setDeath();
      theGrid[y][i].setMasterBlock(NULL);
      theGrid[y][i].setBlockType(0);
      theGrid[y][i].setUnfixed();
   }
}

void Grid::setBlockFixed(Block *ablock) {
   Vector *theBlock = ablock->genBlock();
   for (int i = 0; i < 4; ++i) {
      theGrid[theBlock[i].y][theBlock[i].x].setFixedStatus();
   }
}

bool Grid::isFixed(int x, int y) {
   return theGrid[y][x].isFixed();
}

bool Grid::isLiving(int x, int y) {
   return theGrid[y][x].getIsAlive();
}

bool Grid::isFixedLiving(int x, int y) {
   return (theGrid[y][x].getIsAlive() && theGrid[y][x].isFixed());
}

Cell& Grid::getCell(int i, int j) {
   Cell &cell = theGrid[i][j];
   return cell;
}

ostream& operator<<(ostream &out, const Grid &g) {
   for (int n = 0; n < MAX_COL; ++n) out << "-";
   out << endl;
   for (int i = 0; i < MAX_ROW; ++i) {
      for (int j = 0; j < MAX_COL; ++j) {
         out << g.theGrid[i][j];
      } // for
      out << endl;
   } // for
   for (int n = 0; n < MAX_COL; ++n) out << "-";
   out << endl << "Next:" << endl;
   for (int i = MAX_ROW; i < MAX_ROW+3; ++i) {
      for (int j = 0; j < MAX_COL; ++j) {
         out << g.theGrid[i][j];
      } // for
      out << endl;
   } // for
   return out;
} // operator<<
   
   
