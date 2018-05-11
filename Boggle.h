#pragma once

#include <string>
#include <vector>
#include "TrieNode.h"

using namespace std;

class Boggle
{
public:

	// constructor
	Boggle(vector<vector<char>>& boggle, vector<string>& dictionary);

	void FindWords();

private:
	void CreateTrie(TrieNode* root);

	void Insert(TrieNode* root, string& key);

	void SearchWord(vector<string>& result,string& str, TrieNode* root, vector<vector<bool>>& visited, int row, int col, int rows, int cols);

	bool WithinRange(int row, int col, int rows, int cols, vector<vector<bool>>& visited);

	void PrintResult(vector<string>& result);

	TrieNode* m_root;
	vector<string> m_dictionary;
	vector<vector<char>> m_boggle;
};