#ifndef CONTAINER_H
#define CONTAINER_H
#include "Base.h"

class Container {
public:
	char* Name;
	char* Description;
	char* Status;

	Container();
	virtual ~Container();
};

#endif
