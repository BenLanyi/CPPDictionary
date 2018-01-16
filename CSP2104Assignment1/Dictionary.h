#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>

#include <thread>

#include "word.h"
#include "Adjective.h"
#include "Adverb.h"
#include "MiscWord.h"
#include "Noun.h"
#include "NounAndVerb.h"
#include "Preposition.h"
#include "ProperNoun.h"
#include "Verb.h"

using namespace std;

class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	int getTotalNumberOfWords();
	void loadDictionary(string fileName);
	string defineWord(string searchWord);
	void threeZlist();
	void qWithoutU();
	void isNounAndVerb();
	void isPalindrome();
	void isAnagram(string searchWord);
	void guessingGame();
	void editDictionary();
	string getSaveStatus();
private:
	vector<Word*> dictionary;
	string stringToLower(string inputString);
	string dictionaryFileName;
	void addWord();
	void deleteWord();
	int findWord(string searchWord);
	void editWord();
	void saveChanges();
	//saveComplete will become false when a saveChanges thread is running
	bool saveComplete = true;
	
};

#endif