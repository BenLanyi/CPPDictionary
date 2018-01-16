#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FunWithTriGrams 
{
public:
	FunWithTriGrams();
	~FunWithTriGrams();
	void processTextFile(string fileName);
private:
	int getIndex(char inputCharacter);
	//3 dimensional array to store probability of letters occuring
	int characterCount[27][27][27] = { 0 };
	void generateWord(string userInput);
	int findHighestIndex(int index1, int index2);
};