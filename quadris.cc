#include <iostream>
#include "quadris.h"
using namespace std;

Quadris::Quadris(Xwindow *xw1, Xwindow *xw2): 
   pxw1(xw1), pxw2(xw2), g(Grid(xw1, xw2)), currentSeed(DEFAULT_SEED),
   nextBlock(NULL), ba(BlockAnimation(&g)), currentLevel(1),
   gameOver(false), currentScore(0), hiScore(0), round(1), restarted(false),
   droppedOrFirstRun(true), eofDetected(false) {}
   
Quadris::~Quadris() {
   if (ba.currentBlock) delete ba.currentBlock;
   if (nextBlock) delete nextBlock;
   sequence.clear();
   colors.clear();
}

void Quadris::runQuadris() {
   if (pxw1) drawInterface();
   p.seed(currentSeed);     // new
   istringstream dropStream;
   int droppedTimes = 0;//
   while(true) {
      if (eofDetected) break;    // break out the loop when eof is detected
      if (pxw1) colorSelector();    // select colors for different blocks randomly.
      if (gameOver) clearGrid();    // clears the board when game is over.
	   if (currentLevel == 0) genCurrentBlock(0);  // generates current block
      else if (currentLevel == 1) genCurrentBlock(p()%12);
      else if (currentLevel == 2) genCurrentBlock(p()%7);
      else if (currentLevel == 3) genCurrentBlock(p()%9);
      g.setBlockLiving(ba.currentBlock); // makes the generated block alive.
      string theCmd;
      while(true) {
         // generates next block when block is dropped, or when game is 
         // in first round, game is restarted or game is over.
         if (droppedOrFirstRun || restarted || gameOver) { 
            if (currentLevel == 0) genNextBlock(0); 
            else if (currentLevel == 1) genNextBlock(p()%12);
            else if (currentLevel == 2) genNextBlock(p()%7);
            else if (currentLevel == 3) genNextBlock(p()%9);
            g.setNextBlockLiving(nextBlock); // sets the next block alive.
            printInterface(); 
            droppedOrFirstRun = false; // turn off the flags
            restarted = false;
            gameOver = false;
         } // if
         if (droppedTimes) { // if there is a >1 number before "drop" command
            theCmd = cmd.getCommand(6); // then the input command is "drop"
            droppedTimes--;  // decrement that number by one.
         } else if (!(cin >> theCmd)) { // reads command from stdin.
            eofDetected = true;
            break; // if encounters eof, break out the loop.
         } // if
         cmd.setCurrentCmd(theCmd); // sends the command to Command class.
         cmd.setValidCmd(); // processes the input command to see whether it is valid.
         char validCommand = cmd.getValidCmd();
         int times = cmd.getTimes();  // separates the number before command.
         
         if (validCommand == 'F') {  // if the input command is valid (found in the TrieNode and there is
                                     // only one possible autocompletion.
            string realCommand = cmd.getRealCmd(); // gets the complete command.
            if (realCommand == cmd.getCommand(0)) { // == "clockwise"
               ba.rotateClock(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(1)) { // == "counterclockwise"
               ba.rotateCounterClock(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(2)) { // == "left"
               ba.moveLeft(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(3)) { // == "right"
               ba.moveRight(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(5)) { // == "down"
               ba.moveDown(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(4)) { // == "up" 
               ba.moveUp(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(6)) { // == "drop"
               if (times) { // if the number before "drop" is not 0.
                  ba.dropBlock(); 
                  g.setBlockFixed(ba.currentBlock); // makes the dropped block fixed status, meaning
                                                    // the block is out of the control of BlockAnimation class.
                  ba.pushBlock();   // pushes the dropped block into vector
                  ba.deleteFilledLines(); // delete lines when they fill.
                  setCurrentScore(); // calculates the current score.
                  setHiScore();  // calculates the high score.
                  g.setNextBlockDeath(nextBlock);  // set last displayed next block death, ready for 
                                                   //the new next block to come to life.
                  nextBlock->genBlock(); // creates the coordinates of next block cells.
                  ba.currentBlock = nextBlock; // now next block is passed to current block.
                  ba.checkInBounds("new"); // check if the new born block has room to live.
                  if (ba.getCanMove()) g.setBlockLiving(ba.currentBlock); // if yes, then set it alive.
                  else {   
                     gameOver = true;  // else, game is over
                     cout << "Game over" << endl; 
                     break;            // and breaks out the loop, starting a new round.
                  } // if     
                  droppedOrFirstRun = true;  // set dropped flag
                  if (times-1) droppedTimes = times-1; // if the number before the command >1, 
                                                       //then blocks need dropping times-1 times.
               } else printInterface();
            } else if (realCommand == cmd.getCommand(7)) { // == "levelup"
               levelUp(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(8)) { // == "leveldown"
               levelDown(times);
               printInterface();
            } else if (realCommand == cmd.getCommand(9)) { // == "restart"
               restarted = true;
               clearGrid();
               break;
            } else if (realCommand == cmd.getCommand(10)) { // == "rename"
               string inputCmd, newCmd;
               cin >> inputCmd >> newCmd;
               cmd.renameCmd(inputCmd, newCmd);
            } else if (realCommand == cmd.getCommand(11)) { // == "default"
               cmd.setDefaultCmd();
            } else if (realCommand == cmd.getCommand(12)) { // == "help"
               cmd.help();
            } // if
         } else if (validCommand == 'N') { // if the input command is invalid 
                                           // (not found in the TrieNode)
            cout << "Command not found" << endl;
         } else if (validCommand == 'A') { // if the input command is invalid
                                           // (found in the TrieNode but there is more than 1 possible words)
            cout << "Command is ambiguous" << endl;
         } // if
      } // while
      sequence.clear();
      if (pxw1) colors.clear();
   } // while
} // runQuadris
   


void Quadris::setCurrentLevel(int lev) {
   currentLevel = lev;
}

void Quadris::levelUp(int time) {
   if (time) {
      for (int i = 0; i < time; ++i) {
         if (currentLevel < 3) {  // if level < 3
            currentLevel++;
            ba.currentBlock->incrementLevel();  // increment the level preference of a block, used for scoring.
            nextBlock->incrementLevel();
         } // if
      } // for
      if (pxw1) { // updates the level part of the graphic interface.
         ostringstream oss1;
         oss1 << currentLevel;
         string clevel = "Level: "+oss1.str();
         int pLevel = currentLevel - 1;
         ostringstream oss2;
         oss2 << pLevel;
         string plevel = "Level: "+oss2.str();
         pxw1->fillRectangle(110,16,plevel.length()*7,12, Xwindow::Cyan);
         pxw1->drawString(110,27,clevel);
      } // if
   } // if
} // levelUp

void Quadris::levelDown(int time) {
   if (time) {
      for (int i = 0; i < time; ++i) {
         if (currentLevel > 0) { // if level  > 0
            currentLevel--;
            ba.currentBlock->decrementLevel(); // decrement the level preference of a block, used for scoring
            nextBlock->decrementLevel();
         } // if
      } // for
      if (pxw1) { // updates the level part of the graphic interface.
         ostringstream oss1;
         oss1 << currentLevel;
         string clevel = "Level: "+oss1.str();
         int pLevel = currentLevel + 1;
         ostringstream oss2;
         oss2 << pLevel;
         string plevel = "Level: "+oss2.str();
         pxw1->fillRectangle(110,16,plevel.length()*7,12, Xwindow::Cyan);
         pxw1->drawString(110,27,clevel);
      } // if
   } // if
} // levelDown

void Quadris::setCurrentScore() { // calculates the current score according to lines removed, 
                                  //blocks removed and level.
   int linesRemoved = ba.getLinesRemoved();
   int scoringFromBlocksRemoved = 0;
   vector<int> temp = ba.getLevelsRemoved(); // get the vector of levels of blocks removed.
   int pScore = currentScore; // current score before updating
   for (unsigned int i = 0; i < temp.size(); ++i) {
      scoringFromBlocksRemoved += (temp[i] + 1)*(temp[i] + 1);   // updates part of the score.
   } // for
   if (linesRemoved)
      // update the current score.
      currentScore += (currentLevel + linesRemoved)*(currentLevel + linesRemoved) + scoringFromBlocksRemoved;
   ba.clearLevelsRemoved(); // reset ba.levelsRemoved vector to empty.
   temp.clear();
   ba.resetLinesRemoved();
   if (pxw1) { // updates the score part of the graphic interface.
      ostringstream oss1;
      oss1 << currentScore;
      string score = "Score: " + oss1.str();
      ostringstream oss2;
      oss2 << pScore;
      string pscore = "Score: "+oss2.str();
      pxw1->fillRectangle(10,16,pscore.length()*7,12, Xwindow::Cyan);
      pxw1->drawString(10, 27, score);
   } // if
} // setCurrentScore

void Quadris::setHiScore() {
   int pHiscore = hiScore; // high score before updating
   if (hiScore <= currentScore) { 
      hiScore = currentScore; // updates the high score if current score exceeds high score.
                              // keep this data when game is restarted.
      if (pxw1) { // updates the score part of the graphic interface.
         ostringstream oss1;
         oss1 << hiScore;
         string hiscore = "Hi Score: "+oss1.str();
         ostringstream oss2;
         oss2 << pHiscore;
         string phiscore = "Hi Score: "+oss2.str();
         pxw1->fillRectangle(10,37,phiscore.length()*7,12, Xwindow::Cyan);
         pxw1->drawString(10, 48, hiscore);
      } // if
   } // if
} // setHiScore 

void Quadris::incrementRound() { // increment round number.
   int pround = round; // round before incrementing.
   round++;
   if (pxw1) { // updates the round part of the graphic interface. 
      ostringstream oss1;
      oss1 << round;
      string Round = "Round #: "+oss1.str();
      ostringstream oss2;
      oss2 << pround;
      string pRound = "Round #: "+oss2.str();
      pxw1->fillRectangle(110,37,pRound.length()*7,12, Xwindow::Cyan);
      pxw1->drawString(110, 48, Round);
   } // if
} // incrementRound

void Quadris::genCurrentBlock(uint32_t rand) {
   genNextBlock(rand); // generate next block according to levels.
   ba.currentBlock = nextBlock;
   nextBlock = NULL;
}

void Quadris::genNextBlock(uint32_t rand){ // generate next block according to levels.
	char type;
	switch(currentLevel){
		case 0:
		   readSequence("sequence.txt");
		   nb.setSequence(sequence);
			nb.level0();
			type = nb.getBlockType();
			break;
		case 1:
			nb.level1(rand);
			type = nb.getBlockType();
			break;
		case 2:
			nb.level2(rand);
			type = nb.getBlockType();
			break;
		case 3:
			nb.level3(rand);
			type = nb.getBlockType();
			break;
	} // switch
	if (type == 'I') nextBlock = new IBlock(currentLevel);
	else if (type == 'O') nextBlock = new OBlock(currentLevel);
	else if (type == 'L') nextBlock = new LBlock(currentLevel);
	else if (type == 'S') nextBlock = new SBlock(currentLevel);
	else if (type == 'Z') nextBlock = new ZBlock(currentLevel);
	else if (type == 'T') nextBlock = new TBlock(currentLevel);
	else if (type == 'J') nextBlock = new JBlock(currentLevel);
	if (currentLevel == 0) nb.incrementCounter();
} // genNextBlock

void Quadris::readSequence(string s){ // read block sequence from a file, and put into a vector
	char temp;
	ifstream myfile(s.c_str());
	if (!myfile.fail()) {
		while(myfile >> temp) {
			sequence.push_back(temp);
		} // while
	} // if
} // readSequence

vector<char> Quadris:: getSequence(){
	return sequence;
}

void Quadris::printInterface() {
   cout << "Level:      " << currentLevel << endl;
   cout << "Round #:    " << round << endl;
   cout << "Score:      " << currentScore << endl;
   cout << "Hi Score:   " << hiScore << endl;
   cout << g;
}

void Quadris::clearGrid() { // clear the board, and re-initialize the fields.
   if (ba.currentBlock) {
      g.setBlockDeath(ba.currentBlock);
      if (restarted) {  // did this because when gameover but not restarted, 
                        // ba.currentBlock is equal to nextBlcok, so just delete nextBlock.
         delete ba.currentBlock;
      } // if
   } // if
   if (nextBlock) {
      g.setNextBlockDeath(nextBlock);
      delete nextBlock;
   } // if
   sequence.clear();
   ba.clearLevelsRemoved();
   ba.clearVb();
   ba.clearBlocksInBound();
   nb.resetCounter();
   currentScore = 0;
   if (pxw1) colors.clear();
   setCurrentScore();
   incrementRound();
} // clearGrid

void Quadris::setSeed(uint32_t s) { // set current seed to s
   currentSeed = s;
}

// returns -1 if value is not in list, or the index of the value in list if found.
int SearchValue(vector<int> list, int value) { 
   unsigned int index = 0;
   int position = -1;
   bool found = false;
   while (index < list.size() && !found) {
      if (list[index] == value) {
         found = true;
         position = index;
      } // if
      index++;
   } // while
   return position;
} // SearchValue

void Quadris::colorSelector() { // selects 9 unique random colors for blocks.
   PRNG p;
   int temp = 0; 
   for(int i = 0; i < 9; i++) {
      do {
         temp = p(time(0)) % 9; // get random number
      } while (SearchValue(colors, temp) != -1); // repeat till it's unique
      colors.push_back(temp); // push the unique random number into color vector.
   } // for
   for (int i = 0; i < MAX_ROW+3; ++i) {
      for (int j = 0; j < MAX_COL; ++j) {
         g.getCell(i,j).setColorVector(colors); // set the color vector of cell at i-th row and j-th column
                                                // to be this->colors.
      } // for
   } // for
} // colorSelector

void Quadris::drawInterface() { // draws the graphic interface.
    pxw1->fillRectangle(0, 0, MAX_COL*20, 67, Xwindow::Cyan);  // fill score board color.
    pxw1->fillRectangle(0, 67, MAX_COL*20, 3); // draw separator
    pxw1->drawString(10, 27, "Score: 0");
    pxw1->drawString(10, 48, "Hi Score: 0");
    pxw1->drawString(110, 27, "Level: 1");
    pxw1->drawString(110, 48, "Round #: 1");
    pxw2->drawString(5,10,"Next Block:");
}
