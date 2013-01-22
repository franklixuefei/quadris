#include <iostream>
#include "command.h"
using namespace std;

Command::Command(): tree(new TrieNode), validCmd(1), currentCmd(""),
					numRemovedCmd(""), times(0) 
{  // 13 commands in total, name of commands and corresponding explanations.
   command[0] = pair<string,string>("clockwise", "Rotate current block clockwise");
   command[1] = pair<string,string>("counterclockwise", "Rotate current block counter-clockwise");
   command[2] = pair<string,string>("left", "Move current block left");
   command[3] = pair<string,string>("right", "Move current block right");
   command[4] = pair<string,string>("up", "Move current block up");
   command[5] = pair<string,string>("down", "Move current block down");
   command[6] = pair<string,string>("drop", "Drop current block");
   command[7] = pair<string,string>("levelup", "One level up (<= 3)");
   command[8] = pair<string,string>("leveldown", "One level down (>= 0)");
   command[9] = pair<string,string>("restart", "Restart the game");
   command[10] = pair<string,string>("rename", "Rename an existing command");
   command[11] = pair<string,string>("default", "Restore default commands");
   command[12] = pair<string,string>("help", "List out existing commands");
   for (int i = 0; i < NUM_CMD; ++i) {
      tree->insert(*tree, command[i].first); // inserts all command names to tree in TreeNode class.
      cmd_backup.push_back(command[i].first); // backup the default commands.
   } // for
}

Command::~Command() { // destructor
   for (int i = 0; i < NUM_CHARS; ++i) DeleteTree(tree->getLetters(i));
   delete tree;
   command.clear();
   cmd_backup.clear();
}

bool isNumber(char n) { // to see whether a char is a number or not
	if(n >= '0'&& n <= '9') return true;
	else return false;
}

int stringConvert(string s){ //takes a number string and converts it to the corresponding number.
	istringstream iss(s);
	int num;
	iss >> num;
	return num;
}

void Command::renameCmd(string inputCmd, string newCmd){ //renames the i-th command with user's preferred one.
   int i = 0;
   setCurrentCmd(inputCmd); // set currentCmd to inputCmd.
   setValidCmd(); // converts the input command to complete form if possible, and sets validCmd
   if (validCmd == 'F') { // if found
	   while (i < NUM_CMD) {
	      if (command[i].first == realCmd) break;
	      i++;
	   } // while
	   setCurrentCmd(newCmd); // the following is to determine whether newCmd is conflict free to be set.
	   setValidCmd();
	   if (validCmd == 'N') {
	      command[i].first = newCmd;
	      tree->remove(*tree, realCmd);
	      tree->insert(*tree, newCmd);
	   } else cout << "New command already exists" << endl;
	} else if (validCmd == 'N') { // if not found
	   cout << "Command to be renamed not found" << endl;
	} else if (validCmd == 'A') { // if found but more than 1 possible autocompletions.
	   cout << "Command to be renamed is ambiguous" << endl;
	} // if
} // renameCmd

void Command::setDefaultCmd() {
   for (unsigned int i = 0; i < cmd_backup.size(); ++i) {
      if (command[i].first != cmd_backup[i]) { 
         tree->remove(*tree, command[i].first);
         tree->insert(*tree, cmd_backup[i]);
         command[i].first = cmd_backup[i];
      } // if
   } // for
} //setDefaultCmd


void Command::help() {
   cout << "----------------------------------" << endl;
   for (int i = 0; i < NUM_CMD; ++i) {
      if (i == 10) {
         cout << command[i].first << " old_cmd new_cmd" << "    ---    " << command[i].second << endl;
      } else {
         cout << command[i].first << "    ---    " << command[i].second << endl;
      } // if
   } // for
} // help


//this function can interpret a simplified command and store it into the realCmd variable if it is valid
void Command::setValidCmd() {
	cmdRemoveNum(); // sets numRemovedCmd, removes the number before the command, 
	                // and stores that number into times.
	string s = tree->find(*tree,numRemovedCmd); // find all possible autocompletions for numRemovedCmd
	string tmp;
	istringstream iss(s);
	vector<string> v;
	while(iss >> tmp) v.push_back(tmp);
	if(v.size() == 1) {
		realCmd = v[0];
		validCmd = 'F'; // found
	}
	else if (v.size() == 0)  {
		validCmd = 'N'; // not found
	} else {
		validCmd = 'A'; // ambiguous
	}
	v.clear();
}

char Command::getValidCmd() { // gets validCmd
	return validCmd;
}

string Command::getRealCmd() { //get realCmd
   return realCmd;
}

void Command::cmdRemoveNum() { //remove the number from the string and record the number into times.
	int cmdSize = currentCmd.length();
	int i = 0;
	string numString = "";
	for (; i<cmdSize; i++){
		if(isNumber(currentCmd[i])){
			numString += currentCmd[i]; // parse the number string.
		} // if
		else break;
	} // for
	if (!i) numString = "1";
	times = stringConvert(numString);
	numRemovedCmd = currentCmd.substr(i);
} // cmdRemoveNum

string Command::getCommand(int i) { //get the i-th command
   return command[i].first;
}

void Command::setCurrentCmd(string cmd) { //set the input cmd as the current cmd.
	currentCmd = cmd;
}

int Command::getTimes() { //get the repeated times of a command
   return times;
}
