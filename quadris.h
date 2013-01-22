#ifndef __QUADRIS_H__
#define __QUADRIS_H__
#include <iostream>
#include <fstream>
#include <sstream>
#include "block.h"
#include "blockAnimation.h"
#include "grid.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "nextBlock.h"
#include "command.h"


const uint32_t DEFAULT_SEED = 362436069;

class Quadris {
   Xwindow *pxw1, *pxw2; // two Xwindow pointers
   Grid g; // the board
   PRNG p;
   uint32_t currentSeed; // used for setting seed by user.
   Block *nextBlock; // a pointer to the next block
	Command cmd; // command
   BlockAnimation ba;  // controls the movement of current block.
   NextBlock nb;       // determines which block is coming next according to different levels.
   int currentLevel; // 4 levels: 0, 1, 2, and 3.
   bool gameOver; // determines whether game is over.
   int currentScore; // stores the current score gained.
   int hiScore;      // stores the highest score ever gained during runtime.
   int round;  // stores how many round the user has played.
   std::vector<char> sequence;  // stores the sequence of blocktypes read from a file.
   std::vector<int> colors;  // stores a sequence of unique color codes.
   bool restarted; // determines whether the game has been restarted.
   bool droppedOrFirstRun; // determines whether the block has been dropped or the game is in first round.
   bool eofDetected; // determines whether the stdin encounters an EOF char.
  
public:
   Quadris(Xwindow *xw1 = NULL, Xwindow *xw2 = NULL); // constructor
   ~Quadris();  // destructor
   void runQuadris(); // main method, controls the game during runtime.
   void genCurrentBlock(uint32_t rand); //according to 4 levels,0 1 2 3.
   void genNextBlock(uint32_t rand); //according to 4 levels,0 1 2 3.
   void setCurrentLevel(int lev); // used for typing which level directly.
   void levelUp(int time = 1);    // makes one level up
   void levelDown(int time = 1);  // makes one level down
   void setCurrentScore();    // used to determine the current score.
   void setHiScore();         // used to determine the high score.
   void incrementRound();     // adds 1 to the number of rounds.
   void readSequence(std::string s);   // reads a sequence file
   std::vector<char> getSequence();    // gets the sequence vector.
   void printInterface();  // prints out the text-version interface
   void clearGrid(); // clears the board and resets the initial values.
   void setSeed(uint32_t s);   // for commandline interface use.
   void colorSelector();// randomly selecting colors for draw(..);, a FEATURE
   void drawInterface(); // draw out the graphic-version interface
};
   
  


#endif
   
