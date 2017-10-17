#ifndef ITEM_H_
#define ITEM_H_

#include "Base.h"

class Item {
public:
	char* Name;
	char* Status;
	char* Description;
	char* Writing;
	//Trigger* Trigger;
	//TurnOn* turnOn;
	Item();
	virtual ~Item();
};


#endif
