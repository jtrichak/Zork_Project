#ifndef ROOM_H
#define ROOM_H
#include "Base.h"

class Room {
public:
	char* Name;
	char* Status;
	char* Type;
	char* Description;
	Room* Border[4]; //Border[0] = north, Border[1] = east, Border[2] = south, Border[3] = west
	//Container** roomContainer;
	//Item** roomItem;
	//Creature** roomCreature;
	//Trigger** roomTrigger;
	Room();
	virtual ~Room();

};

#endif
