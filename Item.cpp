#include "Base.h"

Item::Item() {
	Name = (char*) "";
	Status = (char*) "";
	Description = (char*) "";
	Writing = (char*) "";
}

Item::~Item() { }

Item firstItemInit(xml_node<>* child) {
	    xml_node<>* child2 = child->first_node();
	    Item curItem = Item();
	    while(child2 != 0) {
	        if(strcmp(child2 -> name(), (char*) "name") == 0) {
	        	curItem.Name = child2->value();
	        }
	        else if(strcmp(child2 -> name(), (char*) "description") == 0) {
	        	curItem.Description = child2->value();
	        }
	        else if(strcmp(child2 -> name(), (char*) "writing") == 0) {
	        	curItem.Writing = child2->value();
	        }
	        else if(strcmp(child2 -> name(), (char*) "status") == 0) {
	        	curItem.Status = child2->value();
	        }
	        child2 = child2 -> next_sibling();
 		}
	return curItem;
}

void wireItem(Item* itemArray, Item** pointer, char* name, int maxItem) {
	/* Item* targetItem = findItem(itemArray, name, maxItem);

	int i;
	int lastItem;
	for(i = 0; i < maxItem; i++) {
		if(curRoom -> roomItem[i] == NULL) {
			lastItem = i;
			i += maxItem;
		}
	}
	*/
	*pointer = findItem(itemArray, name, maxItem);	
	return;
}

Item* findItem(Item* itemArray, char* name, int maxItem) {
	int i;
	for(i = 0; i < maxItem; i++) {
		if(strcmp(itemArray[i].Name, name) == 0) {
			return (&(itemArray[i]));
		}
	}
	return NULL;
}
