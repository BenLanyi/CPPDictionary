#include "Verb.h"

Verb::Verb() : Word()
{
	type = "(v.) ";
	rawType = "v";
}

bool Verb::isVerb()
{
	return true;
}