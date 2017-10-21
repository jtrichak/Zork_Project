#include "Base.h"

Creature::Creature() {
	Name = (char*) "";
	Description = (char*) "";
	Status = (char*) "";
}

Creature::~Creature() { 
}

Creature firstCreatInit(xml_node<>* child) {
	xml_node<>* child2 = child->first_node();
    Creature newCreat = Creature();
    while(child2 != 0) {
        if(strcmp(child2 -> name(), (char*) "name") == 0) {
        	newCreat.Name = child2->value();
        }
        else if(strcmp(child2 -> name(), (char*) "description") == 0) {
        	newCreat.Description = child2->value();
        }
        else if(strcmp(child2 -> name(), (char*) "status") == 0) {
        	newCreat.Status = child2->value();
        }
        child2 = child2 -> next_sibling();
	}

	return newCreat;
}