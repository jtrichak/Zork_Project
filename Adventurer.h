#ifndef ADVENTURER_H
#define ADVENTURER_H
#include "Base.h"

class Adventurer {
public:
	Room* Loc;

	Adventurer();
	virtual ~Adventurer();

	void move(Adventurer*, Room*);
	void inventory(Item**);
	void take(Item**, Room*);
	//void drop(Item**, Room*);
	//void open(Room*, Adventurer*); //Needs to check Adventurer for objects?
	//void read(Inventory);
	void openExit(Adventurer*, int*);    //Int can be a main flag, indicates game still active
	//void putItem(Inventory*, Room*, Char*); //Changes ownership from Item to Container name in Room
	//void turnOn(Item*); 
	//void attack()
};

#endif
