#pragma once

#include <vector>

using namespace std;

const int g_alphabetSize = 26;

class TrieNode
{
public:
	TrieNode() : m_child(g_alphabetSize, nullptr) {};

	vector<TrieNode*> m_child;
	bool m_isLeaf = false;
};