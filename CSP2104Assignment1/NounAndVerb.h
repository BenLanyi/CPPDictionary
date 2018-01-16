#pragma once
#include "Noun.h"
#include "Verb.h"

class NounAndVerb : public Noun, public Verb
{
public:
	NounAndVerb();
};