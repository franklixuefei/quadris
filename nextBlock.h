#ifndef __NEXTBLOCK_H__
#define __NEXTBLOCK_H__
#include <sstream>
#include <vector>
#include "PRNG.h"

class NextBlock{
	char blockType; // the type of the nextblock
	std::vector<char> sequence; // use vector to store a sequence of blocktypes.
	unsigned int counter; // keeps track of where we are in the sequence vector.
public:
	NextBlock();
	~NextBlock();
	void level0();// set blockType
	void level1(uint32_t rand); // set blockType
	void level2(uint32_t rand); // set blockType
	void level3(uint32_t rand); // set blockType
	char getBlockType(); // returns the blockType
	void incrementCounter(); // increase counter by 1;
	void resetCounter(); // reset counter to 0
	void setSequence(std::vector<char> s); // set the sequence vector with the given vector
};



#endif
