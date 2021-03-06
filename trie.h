#ifndef __TRIE__
#define __TRIE__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "tools.h"

using namespace std;

class TrieNode {
public:
	unordered_map <string, int> data;
	// first: file name; second: frequency

	TrieNode* child[38];

	bool exist = false;

	void trieTraverse(TrieNode* head);
};

class Trie {
private:
	TrieNode* root = nullptr;
	void __clear(TrieNode* node);

public:
	vector <pair <string, int>> search(string keyword);
	// search and rank all files to a vector based on the keyword
	// first: file name; second: point according to the keyword

	void build(string key, unordered_map<string, int> data);

	void save(string filename);

	void load(string filename);

	void clear();

	bool isEmpty();
	// clear nodes

	void trieTraverse();

};

#endif