#include <iostream>
#include "nextBlock.h"
using namespace std;

NextBlock::NextBlock(): blockType(0), counter(0) {}

NextBlock::~NextBlock() { // destructor
   sequence.clear();
}

// set blockType when level = 0
void NextBlock::level0(){ 
   blockType = sequence[counter];
} // level0

// set blockType when level = 1
void NextBlock::level1(uint32_t rand){ // s,z 1/12, others 1/6
	char t;
	//rand = 0,1,2,3,4,5,6,7,8,9,10,11,12,13 corresponding to 
	//I(0,1),J(2,3),L(4,5),O(6,7),S(8),Z(9),T(10,11) s,z 1/12, others 1/6
	switch(rand) {
		case 0:  
		case 1:  t = 'I';
	      		break;
		case 2:  
		case 3:  t = 'J';
	      		break;
		case 4:  
		case 5:  t = 'L';
	      		break;
		case 6:  
		case 7:  t = 'O';
	      		break;
		case 8:  t = 'S';
	   	   	break;
		case 9:  t = 'Z';
	   		   break;
		case 10: 
		case 11: t = 'T';
	   		   break;
	} // switch
	blockType = t; //set the blockType to t
} // level1

// set blockType when level = 2
void NextBlock::level2(uint32_t rand){//all equal
	char t;
	//rand =0,1,2,3,4,5,6 corresponding to I:0, J:1, L:2, O:3, S:4, Z:5, T:6
	switch(rand) {
	   case 0:  t = 'I';
	         	break;
	   case 1:  t = 'J';
	   			break;
		case 2:  t = 'L';
	   			break;
		case 3:  t = 'O';
	   			break;
		case 4:  t = 'S';
	   			break;
	   case 5:  t = 'Z';
		   		break;
		case 6:  t = 'T';
		   		break;
	} // switch
	blockType = t; //set the blockType to t
} // level2

// set blockType when level = 3
void NextBlock::level3(uint32_t rand){//s,z 2/9 each,others 1/9
	char t;
	//rand = 0,1,2,3,4,5,6,7,8 corresponding to I:0, J:1, L:2, O:3, S:(4,5), Z:(6,7), T:8
	switch(rand){
		case 0:  t = 'I';
	      		break;
		case 1:  t = 'J';
					break;
		case 2:  t = 'L';
					break;
		case 3:  t = 'O';
	   			break;
		case 4:  
		case 5:  t = 'S';
	   			break;
		case 6:  
		case 7:  t = 'Z';
					break;
		case 8:  t = 'T';
	   			break;
	} // switch
	blockType = t; //set the blockType to t
} // level3

char NextBlock::getBlockType() { //get the blockType
   return blockType;
}

void NextBlock::incrementCounter() { // increment counter by 1.
   counter++;
   if (counter > sequence.size()-1) resetCounter(); // if counter >= size of sequence, reset it.
}

void NextBlock::resetCounter() { // set counter to 0.
   counter = 0;
}

void NextBlock::setSequence(vector<char> s) { //set the sequence to s
   sequence = s;
}
