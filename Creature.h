#ifndef CREATURE_H
#define CREATURE_H
#include "Base.h"

class Creature {
public:
	char* Name;
	char* Description;
	char* Status;

	Creature();
	virtual ~Creature();
};

#endif
