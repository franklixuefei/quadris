#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <iostream>
#include <sstream>
#include <vector>
#include "tree.h"
#include <map>

const int NUM_CMD = 13;

class Command{
	TrieNode *tree;
	char validCmd; // 'F': valid; 'N': not found; 'A': ambiguous.
	std::string currentCmd;//the initial command the user type in.
	std::string numRemovedCmd;//the command with numbers been removed.
	std::string realCmd;//the complete form of the short command.
	int times;//the repeated times of a command
	std::map<int,std::pair<std::string,std::string> > command;
	   // 0 1 2 3 4 5 6 7 8 9 10 11 12 corresponding to
	   // clockwise, counterclockwise, left, right, up, down, drop, levelup, leveldown, restart, rename, default.
	std::vector<std::string> cmd_backup;// used for restoring default commands.
	
  public:
	Command(); // waiting for a simplified (or complete) command.
	~Command();
	void renameCmd(std::string inputCmd, std::string newCmd); //enable user to rename the command. 
	                                                          //Replace the oldCmd with the newCmd.
	void setDefaultCmd(); // sets all commands to default.
	void help(); // lists out existing command usages and explanations.
	void setValidCmd(); // converts the input command if it is valid, and set validCmd.
	char getValidCmd(); // return validCmd
	std::string getRealCmd(); //returns the final converted complete version of command
	void cmdRemoveNum(); // removes the numbers before a command 
	std::string getCommand(int i); // return command[i]
	void setCurrentCmd(std::string cmd); // set the current input command to currentCmd
	int getTimes(); // returns the repeated times of a command
};

#endif
