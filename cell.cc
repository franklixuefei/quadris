#include <iostream>
#include "cell.h"
using namespace std;

Cell::Cell(): isAlive(false), blockType(0), fixed(false),
              ablock(NULL) {}

Cell::~Cell() {
   c.clear();
}

void Cell::setBlockType(char blockType) {
   this->blockType = blockType;
}

void Cell::setLiving() {
   isAlive = true;
   if (ablock) ablock->incrementAliveCell(); //
   if (pxw) draw();
}

void Cell::setDeath() {
   isAlive = false;
   if (ablock) ablock->decrementAliveCell(); //
   if (pxw) undraw();
}

bool Cell::getIsAlive() {
   return isAlive;
}

bool Cell::isFixed() {
   return fixed;
}

void Cell::setFixedStatus() {
   fixed = true;
}

void Cell::setUnfixed() {
   fixed = false;
}

char Cell::getBlockType() {
   return blockType;
}

void Cell::setMasterBlock(Block *aBlock) {
   ablock = aBlock;
}

Block* Cell::getMasterBlock() {
   return ablock;
}

void Cell::setCoords(int xc, int yc, Xwindow *xw, int w, int h) {
   xCoord = xc;
   yCoord = yc;
   width = w;
   height = h;
   pxw = xw;
}

void Cell::setYCoords(int y) {
    yCoord = y; 
}

int Cell::getYCoords() {
    return yCoord;
}

void Cell::draw() {
   switch(blockType) {
      case 'I':
         pxw->fillRectangle(xCoord, yCoord, width, height, c[c[c[0]]]+1); // even more more RANDOM!!!!!
           //cout << c[c[c[0]]]+1 << endl;
           break;
      case 'O':
         pxw->fillRectangle(xCoord, yCoord, width, height, c[c[c[1]]]+1);
          //cout << c[c[c[1]]]+1 << endl; 
         break;
      case 'L':
         pxw->fillRectangle(xCoord, yCoord, width, height, c[c[c[2]]]+1);
           //cout << c[c[c[2]]]+1 << endl;
           break;
      case 'J':
         pxw->fillRectangle(xCoord, yCoord, width, height, c[c[c[3]]]+1);
           //cout << c[c[c[3]]]+1 << endl;
         break;
      case 'S':
         pxw->fillRectangle(xCoord, yCoord, width, height, c[c[c[4]]]+1);
           //cout << c[c[c[4]]]+1 << endl;
         break;
      case 'Z':
         pxw->fillRectangle(xCoord, yCoord, width, height, c[c[c[5]]]+1);
           //cout << c[c[c[5]]]+1 << endl;
         break;
      case 'T':
         pxw->fillRectangle(xCoord, yCoord, width, height, c[c[c[6]]]+1);
           //cout << c[c[c[5]]]+1 << endl;
           break;
      default:
         pxw->fillRectangle(xCoord, yCoord, width, height, 0);
   }
   
} // draw

// Purpose: undraws the cell (turing it into white color).
// Return type: void
void Cell::undraw() {
   pxw->fillRectangle(xCoord, yCoord, width, height, Xwindow::White);
} // undraw

void Cell::setColorVector(std::vector<int> cl) {
   c = cl;
}

ostream& operator<<(ostream &out, const Cell &c) {
   if (c.isAlive) out << c.blockType;
   else out << " ";
   return out;
}
