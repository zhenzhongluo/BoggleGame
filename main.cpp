/*
Boggle

Write a program that takes as input a board of size M x N and a dictionary (a simple list of words)
and produces a list of all words that can be formed from sequences of adjacent characters in the board.  
All words must contain at least 3 letters, and each letter can be used at most one time.  Please list any assumptions.
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Boggle.h"

using namespace std;

/*
Test Cases:
0. long list of words in the dictionary
1. normal length of words
2. Case-sensitive words + repeated characters in a word
3. dictionary is empty
4. boggle is empty
5. palindrome words
*/

int main()
{
	// board size = 8 x 5
	cout << "Example 0 - The result is: " << endl;
	vector<string> dictionary0 = { "extrodinary" , "big", "fish", "games", "rock" };
	vector<vector<char>> boggle0 = { { 'a','n','r','g','d' },
									 { 'i','f','a','b','c' },
									 { 'd','m','i','r','h' },
									 { 'o','e','s','s','y' },
									 { 'g','r','o','c','d' },
									 { 'i','h','t','k','i' },
									 { 'b','x','v','s','g' },
									 { 'e','r','o','b','i' }
								   };

	shared_ptr<Boggle> obj0(new Boggle(boggle0, dictionary0));

	// result = "extrodinary", "big", "fish", "games", "rock" 
	obj0->FindWords();
	cout << endl;

	cout << "Example 1 - The result is: " << endl;
	vector<string> dictionary1 = { "fishs", "a", "fish"};
	vector<vector<char>> boggle1 = { { 'o','s','h' },
									 { 'i','a','s' },
									 { 'f','e','e' }
								   };

	shared_ptr<Boggle> obj1 (new Boggle(boggle1, dictionary1));

	// result = "feed", "fish", "a" 
	obj1->FindWords();

	cout << endl;

	cout << "Example 2 - The result is: " << endl;
	vector<string> dictionary2 = { "AAA", "aaaa", "aaaaaa", "aaaaa" };
	vector<vector<char>> boggle2 = { { 'a','a','A' },
									 { 'a','A','A' },
									 { 'a','a','a' }
								   };

	shared_ptr<Boggle> obj2(new Boggle(boggle2, dictionary2));

	// result = "aaaa", "aaaaa", "aaaaaa"
	obj2->FindWords();
	cout << endl;

	cout << "Example 3 - The result is: " << endl;
	vector<string> dictionary3 = {};
	vector<vector<char>> boggle3 = { { 'b','i','g' } };

	shared_ptr<Boggle> obj3(new Boggle(boggle3, dictionary3));

	// result = "No result found."
	obj3->FindWords();
	cout << endl;

	cout << "Example 4 - The result is: " << endl;
	vector<string> dictionary4 = {"fish"};
	vector<vector<char>> boggle4 = {};

	shared_ptr<Boggle> obj4(new Boggle(boggle4, dictionary4));

	// result = "No result found."
	obj4->FindWords();
	cout << endl;

	cout << "Example 5 - The result is: " << endl;
	vector<string> dictionary5 = { "god", "dog"};
	vector<vector<char>> boggle5 = { { 'd','o','g' },
									{ 'o','a','o' },
									{ 'g','o','d' } };

	shared_ptr<Boggle> obj5(new Boggle(boggle5, dictionary5));

	// result = "dog", "god"
	obj5->FindWords();
	cout << endl;

	system("PAUSE");
}