#include "Base.h"

Room::Room() {
	int i = 0;
	for(i = 0; i < 4; i++) {
		Border[i] = NULL;
	}
	Type = (char*) "Regular";
	Status = (char*) "";
	Description = (char*) "";
	Name = (char*) "";
}
Room::~Room() { }

Room* findRoom(Room* rooms, char* name, int maxRoom) {
	int i = 0;
	for(i = 0; i < maxRoom; i++) {
		if(strcmp(rooms[i].Name, name) == 0) {
			return(&(rooms[i]));
		}
	}
	return NULL;
}


Room firstRoomInit(xml_node<>* child) {
	    xml_node<>* child2 = child->first_node();
	    Room curRoom = Room();
	    while(child2 != 0) {
	        if(strcmp(child2 -> name(), (char*) "name") == 0) {
	        	curRoom.Name = child2->value();
	        }
	        else if(strcmp(child2 -> name(), (char*) "description") == 0) {
	        	curRoom.Description = child2->value();
	        }
	        else if(strcmp(child2 -> name(), (char*) "type") == 0) {
	        	curRoom.Type = child2->value();
	        }
	        else if(strcmp(child2 -> name(), (char*) "status") == 0) {
	        	curRoom.Status = child2->value();
	        }
	        child2 = child2 -> next_sibling();
 		}
	return curRoom;
}

void wireRoom(Room* roomArray, Room* curRoom, char* name, char* direction, int maxRoom) {
	Room* targetRoom = findRoom(roomArray, name, maxRoom);
	if(strcmp(direction, "north") == 0) {
		curRoom -> Border[0] = targetRoom;
	}
	else if(strcmp(direction, "south") == 0) {
		curRoom -> Border[2] = targetRoom;
	}
	else if(strcmp(direction, "west") == 0) {
		curRoom -> Border[3] = targetRoom;
	}
	else if(strcmp(direction, "east") == 0) {
		curRoom -> Border[1] = targetRoom;
	}
	return;
}
