#pragma once
#include "Word.h"

class Verb : virtual public Word
{
public:
	Verb();
	bool isVerb();
};