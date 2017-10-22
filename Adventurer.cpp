#include "Base.h"

Adventurer::Adventurer() {
	Loc = NULL;
}
Adventurer::~Adventurer() { }

void Adventurer::inventory(Item** Inventory, int maxInventory) {
	int i = 0;
	if(Inventory[i] == NULL) {
		std::cout << "Inventory: Empty" << std::endl;
	} else {
		std::cout << "Inventory: ";
		for(i = 0; i < maxInventory; i++) {
			std::cout << Inventory[i] -> Name;
			if(i < (maxInventory - 1)) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
	return;
}
void Adventurer::move(Adventurer* adventurer, Room* newLoc) {
	if(newLoc == NULL) {
		std::cout << "Can't go that way" << std::endl;
	} else {
		adventurer -> Loc = newLoc;
		std::cout << adventurer -> Loc -> Description << std::endl;
	} 
	return;
}

void Adventurer::openExit(Adventurer* adventurer, int* exitVal) {
	if(strcmp(adventurer -> Loc->Type, "exit") == 0) {
		std::cout << "Congrats, you won!" << std::endl;
		*exitVal = 0;
	} else {
		std::cout << "This room is not the exit" << std::endl;
	}
	return;
}

int validateWord (std::string word1, std::string word2, std::string word3, std::string word4, int wordCount) {
	int validWord;   //0 if invalid, 1 if take, 2 if open, 3 if read, 4 if drop, 5 if put, 6 if turn on, 7 if attack
	if(wordCount <= 1) {
		validWord = 0;
	}
	else {
		if(word1 == "take") {
			if(wordCount != 2) {
				validWord = 0;
			}
			else {
				validWord = 1;
			}
		}
		else if(word1 == "open") {
			if(wordCount != 2) {
				validWord = 0;
			}
			else {
				validWord = 2;
			}
		}
		else if(word1 == "read") {
			if(wordCount != 2) {
				validWord = 0;
			}
			else {
				validWord = 3;
			}
		}
		else if(word1 == "drop") {
			if(wordCount != 2) {
				validWord = 0;
			}
			else {
				validWord = 4;
			}
		}
		else if(word1 == "put") {
			if(wordCount != 4) {
				validWord = 0;
			}
			else {
				if(word3 == "in") {
					validWord = 5;
				}
				else {
					validWord = 0;
				}
			}
		}
		else if(word1 == "turn") {
			if(word2 == "on") {
				if(wordCount == 3) {
					validWord = 6;
				}
				else {
					validWord = 0;
				}
			}
			else {
				validWord = 0;
			}
		}
		else if(word1 == "attack") {
			if(word3 == "with") {
				if(wordCount == 4) {
					validWord = 7;
				}
				else {
					validWord = 0;
				}
			}
			else {
				validWord = 0;
			}
		}
		else {
			validWord = 0;
		}
	}

	assert(validWord == 0 || validWord == 1 || validWord == 2 || validWord == 3 || validWord == 4 || validWord == 5 || validWord == 6 || validWord == 7);
	return validWord;
}

void takeItem(Room* roomArray, Item*** roomInventories, Room* curLoc, Item* itemArray, Item** inventory, int* invenCount, std::string word, int maxRoom, int maxItem, int* roomInvenCount, Container** roomContainers, int* containerInvenCounts, Item*** contInventories, int maxCont) {
	// MODIFY FOR CONTAINERS IN ROOM TOO
	int curRoom;
	int curRoomIndex;
	char* wordChar = new char[word.length() + 1];
	strcpy(wordChar, word.c_str());
	wordChar[word.length()] = '\0';

	for(curRoom = 0; curRoom < maxRoom; curRoom++) {
		if(strcmp(roomArray[curRoom].Name, curLoc -> Name) == 0) {
			curRoomIndex = curRoom;
			curRoom += maxRoom;
		}
	}

	int curRoomInven;
	int change = 0;
	int i;
	int j;

	for(curRoomInven = 0; curRoomInven < maxItem; curRoomInven++) {
		if(roomInventories[curRoomIndex][curRoomInven] != NULL) {
			if(strcmp(roomInventories[curRoomIndex][curRoomInven] -> Name, wordChar) == 0) {
				for(i = 0; i < maxCont; i++) {
					for(j = 0; j < maxItem; j++) {
						if(contInventories[i][j] != NULL) {
							if(strcmp(contInventories[i][j] -> Name, wordChar) == 0) {
								contInventories[i][j] = NULL;
								sortMissingItem(&(containerInvenCounts[i]), contInventories[i]);
								containerInvenCounts[i]--;
							}
						}
					}
				}
				inventory[*invenCount] = roomInventories[curRoomIndex][curRoomInven];
				roomInventories[curRoomIndex][curRoomInven] = NULL;
				std::cout << "Item " << inventory[*invenCount] -> Name << " added to inventory" << std::endl;
				change = 1;
				sortMissingItem(roomInvenCount, roomInventories[curRoomIndex]);
				(*invenCount)++;
				(*roomInvenCount)--;
				curRoomInven += maxItem;
			}
		}
	}
	assert((*invenCount) <= maxItem);
	assert((*roomInvenCount) >= 0);

	if(change == 0) {
		std::cout << "Item was not found" << std::endl;
	}



	delete [] wordChar;
	return;
}

void dropItem(Room* roomArray, Item*** roomInventories, Room* curLoc, Item* itemArray, Item** inventory, int* invenCount, std::string word, int maxRoom, int maxItem, int* roomInvenCount) {
	int curRoom;
	int curRoomIndex;
	char* wordChar = new char[word.length() + 1];
	strcpy(wordChar, word.c_str());
	wordChar[word.length()] = '\0';

	for(curRoom = 0; curRoom < maxRoom; curRoom++) {
		if(strcmp(roomArray[curRoom].Name, curLoc -> Name) == 0) {
			curRoomIndex = curRoom;
			curRoom += maxRoom;
		}
	}

	int curInven;
	int change = 0;

	if(inventory != NULL) {
		for(curInven = 0; curInven < *invenCount; curInven++) {
			if(strcmp(inventory[curInven] -> Name, wordChar) == 0) {
				roomInventories[curRoomIndex][*roomInvenCount] = inventory[curInven];
				inventory[curInven] = NULL;
				std::cout << "Item " << roomInventories[curRoomIndex][*roomInvenCount] -> Name << " was dropped" << std::endl;
				curInven += *invenCount;
				sortMissingItem(invenCount, inventory);  // Need, because invenCount changes but there ain't no justice no mo
				(*roomInvenCount)++;
				(*invenCount)--;
				change = 1;
			}
		}
	}
	assert((*roomInvenCount) <= maxItem);
	assert((*invenCount) >= 0);

	if(change == 0) {
		std::cout << "Item not in inventory" << std::endl;
	}

	delete [] wordChar;
	return;
}

void sortMissingItem(int* invenCount, Item** inventory) {
	int missingItem;
	int i;
	Item* temp;
	for(i = 0; i < *invenCount; i++) {
		if(inventory[i] == NULL) {
			missingItem = i;
			i += *invenCount;
		}
	}
	temp = inventory[*invenCount - 1];
	inventory[*invenCount - 1] = NULL;
	inventory[missingItem] = temp;
	return;
}

void readItem(Item** itemArray, int invenCount, std::string word) {
	char* wordChar = new char[word.length() + 1];
	strcpy(wordChar, word.c_str());
	wordChar[word.length()] = '\0';

	int i;
	int change = 0;
	for(i = 0; i < invenCount; i++) {
		if(strcmp(itemArray[i] -> Name, wordChar) == 0) {
			std::cout << itemArray[i] -> Writing << std::endl;
			i += invenCount;
			change = 1;
		}
	}

	if(change == 0) {
		std::cout << "Item not in inventory" << std::endl;
	}

	delete [] wordChar;
	return;
}

void openContainer(Room* curRoom, int curRoomIndex, Container** roomContainers, Item** roomInventory, Item*** contInventories, int maxRoom, int maxItem, int maxCont, int* contItemCounts, int* roomInvenCount, std::string word, int* acceptItem, std::string** acceptItemNames) {
	char* wordChar = new char[word.length() + 1];
	strcpy(wordChar, word.c_str());
	wordChar[word.length()] = '\0';

	int i;
	int curContIndex = 0;
	int change1 = 0;
	for(i = 0; i < maxCont; i++) {
		if(roomContainers[i] != NULL) {
			if(strcmp(roomContainers[i] -> Name, wordChar) == 0) {
				change1 = 1;
				curContIndex = i;
				i += maxCont;
			}
		}
	}

	if(change1 == 0) {
		std::cout << "Container is not present in current room" << std::endl;
	}
	else {
		//int change2 = 0;
		if(contItemCounts[curContIndex] == 0) {
			std::cout << roomContainers[curContIndex] -> Name << " is empty" << std::endl;
		}
		else {
			std::cout << roomContainers[curContIndex] -> Name << " contains ";
			for(i = 0; i < contItemCounts[curContIndex]; i++) {
				if(contInventories[curContIndex][i] != NULL) {
					std::cout << contInventories[curContIndex][i] -> Name;
					if(contItemCounts[curContIndex] > 1) {
						if(i != (contItemCounts[curContIndex] - 1)) {
							std::cout << ", ";
						}
					}
				}
			}
			std::cout << std::endl;
			int j = *roomInvenCount;
			for(i = 0; i < contItemCounts[curContIndex]; i++) {
				if(checkDupes(roomInventory, contInventories[curContIndex][i], maxItem) == 0) {
					roomInventory[j] = contInventories[curContIndex][i];
					j++;
				}
			}
			
			j = 0;
			for(i = 0; i < maxItem; i++) {
				if(roomInventory[i] != NULL) {
					j++;
				}
			}
			(*roomInvenCount) = j;
		}
	}
	delete [] wordChar;
	return;

}

int checkDupes(Item** roomInventory, Item* newItem, int maxItem) {

	int choice = 0;
	int i;

	for(i = 0; i < maxItem; i++) {
		if(roomInventory[i] != NULL) {
			if(strcmp(roomInventory[i] -> Name, newItem -> Name) == 0) {
				i += maxItem;
				choice = 1;
			}
		}
	}

	return choice;
}

void putItem(Item*** contInventories, Item** inventory, Container** roomContainers, int roomIndex, int maxItem, int maxCont, std::string word, std::string word2, int* contInvenCounts, int* invenCount, int* acceptItem, std::string** acceptItemNames) {
	char* itemChar = new char[word.length() + 1];
	strcpy(itemChar, word.c_str());
	itemChar[word.length()] = '\0';

	char* contChar = new char[word2.length() + 1];
	strcpy(contChar, word2.c_str());
	contChar[word2.length()] = '\0';

	int invIndex;
	int i;
	int change1 = 0;
	for(i = 0; i < maxItem; i++) {
		if(inventory[i] != NULL) {
			if(strcmp(inventory[i] -> Name, itemChar) == 0) {
				invIndex = i;
				i += maxItem;
				change1 = 1;
			}
		}
	}

	if(change1 == 0) {
		std::cout << "Item " << word << " was not found in inventory" << std::endl;
	}
	else {
		int contIndex;
		int itemGood = 0;
		int change2 = 0;
		for(i = 0; i < maxCont; i++) {
			if(roomContainers[i] != NULL) {
				if(strcmp(roomContainers[i] -> Name, contChar) == 0) {
					change2 = 1;
					contIndex = i;
					i += maxCont;
				}
			}
		}

		if(change2 == 0) {
			std::cout << "Container " << word2 << " was not found in the current room" << std::endl;
		}
		else {

			if(acceptItem[contIndex] >= 1) {
				for(i = 0; i < acceptItem[contIndex]; i++) {
					if(acceptItemNames[contIndex][i] == word) {
						itemGood = 1;
						i += acceptItem[contIndex];
					}
				}
			}
			
			if(acceptItem[contIndex] == 0 || itemGood == 1) {
				int lastContItem;
				for(i = 0; i < maxItem; i++) {
					if(contInventories[contIndex][i] == NULL) {
						lastContItem = i;
						i += maxItem;
					}
				}
			
	
				Item* temp = inventory[invIndex];
				inventory[invIndex] = NULL;
				contInventories[contIndex][lastContItem] = temp;

				std::cout << "Item " << contInventories[contIndex][lastContItem] -> Name << " was added to " << roomContainers[contIndex] -> Name << std::endl;
				sortMissingItem(invenCount, inventory);
				(*invenCount)--;
				contInvenCounts[contIndex]++;
			}
			else {
				std::cout << "Item " << word << " could not be put in container" << std::endl;
			}
		}
	}

	delete [] itemChar;
	delete [] contChar;
	return;
}
