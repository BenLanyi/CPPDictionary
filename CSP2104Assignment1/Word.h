#ifndef WORD_H
#define WORD_H

#include <string>
using namespace std;

class Word
{
public:
	Word();
	~Word();
	virtual string getWord();
	string getDefinition(string options = "");
	virtual bool isNoun();
	virtual bool isVerb();
	void setWord(string word, string definition);
	string getType();
protected:
	string word;
	string definition;
	string type;
	string rawType;
};
















#endif