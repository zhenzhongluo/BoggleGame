#include <algorithm>
#include <iostream>
#include "Boggle.h"

using namespace std;

// Constructor
Boggle::Boggle(vector<vector<char>>& boggle, vector<string>& dictionary) : m_boggle(boggle), m_dictionary(dictionary)
{
	m_root = new TrieNode();

	CreateTrie(m_root);
}

void Boggle::FindWords()
{
	if (m_boggle.size() == 0 || m_dictionary.size() == 0)
	{
		cout << "No result found." << endl;
		return;
	}

	const int rows = m_boggle.size();
	const int cols = m_boggle[0].size();

	vector<vector<bool>> visited(rows, vector<bool>(cols, false));

	TrieNode* root = m_root;

	string str = "";

	vector<string> result;

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			char character = m_boggle[row][col];

			int index = toupper(character) - 65;

			// start searching from the characters of the boggle contained in the root's children list
			if (root->m_child[index])
			{
				str += m_boggle[row][col];

				// recursively search for the current string in the current parent
				SearchWord(result, str, root->m_child[index], visited, row, col, rows, cols);

				// when the recursion is backtracked and done, reset the str
				str = "";
			}
		}
	}
	
	PrintResult(result);
}

void Boggle::CreateTrie(TrieNode* root)
{
	int size = m_dictionary.size();

	for (int i = 0; i < size; i++)
	{
		Insert(root, m_dictionary[i]);
	}
}


void Boggle::Insert(TrieNode* root, string& key)
{
	TrieNode* child = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = toupper(key[i])-65;

		if (!child->m_child[index])
		{
			child->m_child[index] = new TrieNode();
		}

		child = child->m_child[index];
	}

	// mark the last character of the key as the leaf
	child->m_isLeaf = true;
}

void Boggle::SearchWord(vector<string>& result, string& str, TrieNode* root, vector<vector<bool>>& visited, int row, int col, int rows, int cols)
{
	// if it's the leaf node, it is not found in the resut list, and it's in the dictionary list
	if (root->m_isLeaf && 
		find(result.begin(), result.end(), str) == result.end() && 
		find(m_dictionary.begin(), m_dictionary.end(), str) != m_dictionary.end())
	{
		result.push_back(str);
	}

	if (WithinRange(row, col, rows, cols, visited))
	{
		// mark the current character in the boggle as visited
		visited[row][col] = true;

		for (int i = 0; i < g_alphabetSize; i++)
		{
			char character = (char)i + 'a';

			// traverse all children of the current root recursively
			if (root->m_child[i])
			{
				str += character;

				// search the current character's neighbors
				if (WithinRange(row, col+1, rows, cols, visited) && m_boggle[row][col+1] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row, col + 1, rows, cols);
				}

				if (WithinRange(row-1, col+1, rows, cols, visited) && m_boggle[row-1][col+1] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row - 1, col + 1, rows, cols);
				}

				if (WithinRange(row + 1, col + 1, rows, cols, visited) && m_boggle[row + 1][col + 1] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row + 1, col + 1, rows, cols);
				}

				if (WithinRange(row, col - 1, rows, cols, visited) && m_boggle[row][col - 1] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row, col - 1, rows, cols);
				}

				if (WithinRange(row+1, col-1, rows, cols, visited) && m_boggle[row+1][col-1] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row + 1, col - 1, rows, cols);
				}

				if (WithinRange(row-1, col-1, rows, cols, visited) && m_boggle[row-1][col-1] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row-1, col - 1, rows, cols);
				}

				if (WithinRange(row+1, col, rows, cols, visited) && m_boggle[row+1][col] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row+1, col, rows, cols);
				}

				if (WithinRange(row-1, col, rows, cols, visited) && m_boggle[row-1][col] == character)
				{
					SearchWord(result, str, root->m_child[i], visited, row-1, col, rows, cols);
				}

				// remove the last added character at this point because 
				// the curren root node might not be the correct one for the word
				str = str.substr(0, str.size() - 1);
			}
		}

		// reset the current character in the boggle as unvisited for the next word search
		visited[row][col] = false;
	}
}

bool Boggle::WithinRange(int row, int col, int rows, int cols, vector<vector<bool>>& visited)
{
	return (row >= 0 && row < rows) && (col >= 0 & col < cols) && (!visited[row][col]);
}

void Boggle::PrintResult(vector<string>& result)
{
	for (string str : result)
	{
		cout << str << endl;
	}
}