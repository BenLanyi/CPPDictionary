#include "word.h"


//standard word class
Word::Word()
{
	type = "(?) ";
	rawType = "word";
}

Word::~Word()
{
}

void Word::setWord(string word, string definition)
{
	Word::word = word;
	Word::definition = definition;
}
//returns raw type. used when saving dictionary back in original format
string Word::getType()
{
	return rawType;
}

string Word::getWord()
{
	return word;
}

string Word::getDefinition(string options)
{
	if (options == "clean")
	{
		return definition;
	}
	else
	{
		string returnDefinition;
		returnDefinition = definition;
		returnDefinition.insert(0, type);
		return returnDefinition;
	}
}

bool Word::isNoun()
{
	return false;
}

bool Word::isVerb()
{
	return false;
}
