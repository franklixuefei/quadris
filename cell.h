#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "block.h"
#include <vector>
#include "window.h"  //for Xwindow.

class Cell {
   bool isAlive;
   char blockType;
   bool fixed;
   std::vector<int> c;   // for storing unique random numbers for colors use. 
   Block *ablock; // know which block this cell belongs to.
   int xCoord, yCoord, width, height;
   Xwindow *pxw;
  public:
   Cell();
  //  Cell(const Cell &other);
    ~Cell();
   void setBlockType(char blockType);
   void setLiving(); // need to set color
   void setDeath(); // need to set color
   bool getIsAlive();
   bool isFixed();
   void setFixedStatus();
   void setUnfixed(); 
   char getBlockType(); 
   void setMasterBlock(Block *aBlock); // set ablock field, letting this cell know which block it belongs to.
   Block* getMasterBlock();
   void setCoords(int xc, int yc, Xwindow *xw, int w, int h);
    void setYCoords(int y);
    int getYCoords();
    void draw();  //
   void undraw();   //
   //void pushColor(int colorCode); //
   void setColorVector(std::vector<int> cl);
   friend std::ostream& operator<<(std::ostream &out, const Cell &c);
};

#endif
