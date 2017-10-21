#ifndef ADVENTURER_H
#define ADVENTURER_H
#include "Base.h"

class Adventurer {
public:
	Room* Loc;

	Adventurer();
	virtual ~Adventurer();

	void move(Adventurer*, Room*);
	void inventory(Item**, int);
	void openExit(Adventurer*, int*);    //Int can be a main flag, indicates game still active
};

#endif
