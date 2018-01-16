#pragma once
#include "Word.h"
using namespace std;

class Noun : virtual public Word
{
public:
	Noun();
	bool isNoun();
};