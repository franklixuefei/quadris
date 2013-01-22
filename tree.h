#ifndef __TREE_H__
#define __TREE_H__
#include <string>

const int NUM_CHARS = 26;

class TrieNode {
	bool isWord;
	TrieNode *letters[NUM_CHARS];
   friend void DeleteTree(TrieNode *node);
   friend std::string find_help(const TrieNode &node, const std::string &word,
		std::string prefix, std::string token, std::string output, const TrieNode *aNode);
public:
	TrieNode();
	~TrieNode();
	TrieNode *getLetters(int i);
	void insert(TrieNode &node, const std::string &word);
	void remove(TrieNode &node, const std::string &word);
	std::string find(const TrieNode &node, const std::string &word);
	
};

#endif

