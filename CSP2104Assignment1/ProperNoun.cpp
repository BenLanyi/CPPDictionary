#include "ProperNoun.h"

ProperNoun::ProperNoun() : Noun()
{
	type = "(pn.) ";
	rawType = "pn";
}

//getWord changes first character to a capital for proper noun type words. Note: Searching for a definition now requires proper nouns to be typed with a capital for a match to be found
string ProperNoun::getWord()
{
	string returnString;
	returnString = word;
	returnString[0] = toupper(returnString[0]);
	return returnString;
}