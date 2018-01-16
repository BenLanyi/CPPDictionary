#include "Noun.h"

Noun::Noun() : Word()
{
	type = "(n.) ";
	rawType = "n";
}

bool Noun::isNoun()
{
	return true;
}