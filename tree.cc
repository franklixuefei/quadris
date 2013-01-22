#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "tree.h"

using namespace std;

TrieNode::TrieNode() {
	isWord = false;
	for (int i = 0; i < NUM_CHARS; ++i) letters[i] = NULL;
}

TrieNode::~TrieNode() {}

TrieNode* TrieNode::getLetters(int i) {
   return letters[i];
}

void TrieNode::insert(TrieNode &node, const string &word) {
	istringstream iss(word);
	char addChar;
	TrieNode **letter = node.letters, *aNode = &node;
	while (iss >> addChar) {
		int charLoc = addChar - 'a'; // charLoc from 0 to 25.
		if (letter[charLoc]) {
			aNode = letter[charLoc];
			letter = letter[charLoc]->letters;
		} else {
			letter[charLoc] = new TrieNode;
			aNode = letter[charLoc];
			letter = letter[charLoc]->letters;
		}
	}
	aNode->isWord = true;
}

void TrieNode::remove(TrieNode &node, const string &word) {
	istringstream iss(word);
	char addChar;
	TrieNode **letter = node.letters, *aNode = &node;
	while (iss >> addChar) {
		int charLoc = addChar - 'a'; // charLoc from 0 to 25.
		if (letter[charLoc]) {
			aNode = letter[charLoc];
			letter = letter[charLoc]->letters;
		} else
			return;
	}
	aNode->isWord = false;
}

string find_help(const TrieNode &node, const string &word,
		string prefix, string token, string output, const TrieNode *aNode) {
	istringstream iss(word);
	char addChar;
	TrieNode * const *letter = node.letters;
	while (iss >> addChar) {
		int charLoc = addChar - 'a'; // charLoc from 0 to 25.
		if (letter[charLoc]) {
			aNode = letter[charLoc];
			letter = letter[charLoc]->letters;
			prefix += addChar;
		} else
			return (output = "");
		token = prefix;
	} // while, creating prefix.
	if (aNode->isWord)
		output += (token + " ");
	for (int i = 0; i < 25; ++i) {
		string emptyStr = "";
		TrieNode *nextNode = aNode->letters[i];
		if (nextNode)
			output = find_help(node, emptyStr, prefix,
					token + (char) (i + 'a'), output, nextNode);
	}
	return output;
}

string TrieNode::find(const TrieNode &node, const string &word) {
	return find_help(node, word, "", "", "", &node);
}

void DeleteTree(TrieNode *node) {
	for (int i = 0; i < NUM_CHARS; ++i) {
		if (node) {
			TrieNode *letter = node->letters[i];
			if (letter) DeleteTree(letter);
		}
	}
	if (node) delete node;
}


