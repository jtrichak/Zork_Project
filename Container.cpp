#include "Base.h"

Container::Container() {
	Name = (char*) "";
	Description = (char*) "";
	Status = (char*) "";
}

Container::~Container() { 
}

Container firstContInit(xml_node<>* child, int* acceptElement) {
	xml_node<>* child2 = child->first_node();
    Container newCont = Container();
    while(child2 != 0) {
        if(strcmp(child2 -> name(), (char*) "name") == 0) {
        	newCont.Name = child2->value();
        }
        else if(strcmp(child2 -> name(), (char*) "description") == 0) {
        	newCont.Description = child2->value();
        }
        else if(strcmp(child2 -> name(), (char*) "status") == 0) {
        	newCont.Status = child2->value();
        }
        else if(strcmp(child2 -> name(), (char*) "accept") == 0) {
            (*acceptElement)++;
        }
        child2 = child2 -> next_sibling();
	}

	return newCont;
}

int findContIndex(Container* contArray, char* contName, int maxCont) {
    int i;
    int index = 0;                 // If Index is unexpectedly 0, check here
    for(i = 0; i < maxCont; i++) {
        if(strcmp(contName, contArray[i].Name) == 0) {
            index = i;
            i += maxCont;
        }
    }
    return index;
}

Container* findCont(Container* contArray, char* contName, int maxCont) {
    int i;
    int index = 0;                 // If Index is unexpectedly 0, check here
    for(i = 0; i < maxCont; i++) {
        if(strcmp(contName, contArray[i].Name) == 0) {
            index = i;
            i += maxCont;
        }
    }
    return (&(contArray[index]));
}

void wireItemInCont(Item* itemArray, Item** curContInven, char* name, int maxItemCount) {
    Item* targetItem = findItem(itemArray, name, maxItemCount);
    *curContInven = targetItem;
    return;
}

void wireCont(Container* contArray, Container** curCont, char* name, int maxContainer) {
        Container* targetCont = findCont(contArray, name, maxContainer);
        *curCont = targetCont;
    return;
}