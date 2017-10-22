#include "Base.h"

int main(int argc, char* argv[]) {


	int gameActive = 1;
	char* fileInput = new char[50];
	while(gameActive == 1) {
		scanf("%s", fileInput);
		ifstream myfile(fileInput);
		if(myfile.is_open()) {

			rapidxml::xml_document<> doc;
			vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>( ));
			buffer.push_back('\0');
			doc.parse<0>(&buffer[0]);
			xml_node<>* node = doc.first_node();
			xml_node<>* child;
			xml_node<>* child2;
			xml_node<>* child3;


			int maxRoomCount = 0;		//Maximum amount of game rooms
			int maxItemCount = 0;		//Maximum amount of game items
			int maxCreatCount = 0;		//Maximum amount of game creatures
			int maxContCount = 0;		//Maximum amount of game containers
			int i = 0;
			int j = 0;

			while(node != 0) {
				child = node -> first_node();
				while(child != 0) {
					if(strcmp(child->name(), "room") == 0) {
						maxRoomCount++;
					}
					else if(strcmp(child->name(), "item") == 0) {
						maxItemCount++;
					}
					else if(strcmp(child->name(), "creature") == 0) {
						maxCreatCount++;
					}
					else if(strcmp(child->name(), "container") == 0) {
						maxContCount++;
					}
					child = child -> next_sibling();
				}
				node = node -> next_sibling();
			}


			xml_node<>** roomNodeArray = new xml_node<>*[maxRoomCount];
			xml_node<>** itemNodeArray = new xml_node<>*[maxItemCount];
			xml_node<>** creatNodeArray = new xml_node<>*[maxCreatCount];
			xml_node<>** contNodeArray = new xml_node<>*[maxContCount];



			Room* roomArray = new Room[maxRoomCount]; 							// Array of all possible rooms
			Item* itemArray = new Item[maxItemCount];							// Array of all possible items
			Creature* creatArray = new Creature[maxCreatCount];					// Array of all possible creatures
			Container* contArray = new Container[maxContCount];					// Array of all possible containers
			Item** inventory = new Item*[maxItemCount];							// Array of items on the adventurer

			Item*** roomInventories = new Item**[maxRoomCount];					// Array of size room, holds arrays of size maxItem pointers for each room
			Container*** roomContainers = new Container**[maxRoomCount];
			Creature*** roomCreatures = new Creature**[maxRoomCount];
			int* roomContCount = new int[maxRoomCount];
			int* roomTrigCount = new int[maxRoomCount];
			int* roomInventoryCount = new int[maxRoomCount];
			int* acceptItem = new int[maxContCount];

			for(i = 0; i < maxRoomCount; i++) {
				roomInventories[i] = new Item*[maxItemCount];
				for(j = 0; j < maxItemCount; j++) {
					roomInventories[i][j] = NULL;
					inventory[i] = NULL;								// Initializes all pointers in the item array in each room to NULL
				}
				roomCreatures[i] = new Creature*[maxCreatCount];
				for(j = 0; j < maxCreatCount; j++) {
					roomCreatures[i][j] = NULL;
				}
				roomContainers[i] = new Container*[maxContCount];
				for(j = 0; j < maxContCount; j++) {
					roomContainers[i][j] = NULL;
					acceptItem[j] = 0;
				}
				roomTrigCount[i] = 0;
				roomContCount[i] = 0;
				roomInventoryCount[i] = 0;
			}
/*
			Creature*** roomCreatures = new Creature**[maxRoomCount];
			for(i = 0; i < maxRoomCount; i++) {
				roomCreatures[i] = new Creature*[maxCreatCount];
				for(j = 0; j < maxCreatCount; j++) {
					roomCreatures[i][j] = NULL;
				}
			}
			Container*** roomContainers = new Container**[maxRoomCount];
			for(i = 0; i < maxRoomCount; i++) {
				roomContainers[i] = new Container*[maxContCount];
				for(j = 0; j < maxContCount; j++) {
					roomContainers[i][j] = NULL;
				}
			}

			int* roomContCount = new int[maxRoomCount];
			int* roomTrigCount = new int[maxRoomCount];
			int* roomInventoryCount = new int[maxRoomCount];
			for(i = 0; i < maxRoomCount; i++) {
				roomTrigCount[i] = 0;
				roomContCount[i] = 0;
				roomInventoryCount[i] = 0;
			}
*/
			Item*** contInventories = new Item**[maxContCount];					// Array of array of item pointers, size maxRoomCount by maxItemCount
			int* contTrigCount = new int[maxContCount];
			int* contItemCount = new int[maxContCount];
			for(i = 0; i < maxContCount; i++) {
				contInventories[i] = new Item*[maxItemCount];
				contItemCount[i] = 0;
				contTrigCount[i] = 0;
				for(j = 0; j < maxItemCount; j++) {
					contInventories[i][j] = NULL;								// Initializes all pointers in the item pointer array to NULL
				}
			}
/*
			int* contTrigCount = new int[maxContCount];
			int* contItemCount = new int[maxContCount];
			for(i = 0; i < maxContCount; i++) {
				contItemCount[i] = 0;
				contTrigCount[i] = 0;
			}
*/
			int inventoryCount = 0;												// Number of items in adventurer's inventory
			node = doc.first_node();
			int curRoom = 0;
			int curItem = 0;
			int curCreat = 0;
			int curCont = 0;

			while(node != 0) {
				child = node->first_node();
				while(child != 0) {
					if(strcmp(child->name(), (char*) "room") == 0) {
						roomNodeArray[curRoom] = child;
						roomArray[curRoom] = firstRoomInit(child);
						curRoom++;
					}
					else if(strcmp(child->name(), (char*) "item") == 0) {
						itemNodeArray[curItem] = child;
						itemArray[curItem] = firstItemInit(child);
						curItem++;
					}
					else if(strcmp(child->name(), (char*) "creature") == 0) {
						creatNodeArray[curCreat] = child;
						creatArray[curCreat] = firstCreatInit(child);
						curCreat++;
					}
					else if(strcmp(child->name(), (char*) "container") == 0) {
						contNodeArray[curCont] = child;
						contArray[curCont] = firstContInit(child, &(acceptItem[curCont]));
						curCont++;
					}
					child = child -> next_sibling();
				}
				node = node -> next_sibling();
			}

			std::string** acceptItemArray = new std::string*[maxContCount];
			for(i = 0; i < maxContCount; i++) {
				acceptItemArray[i] = new std::string[acceptItem[i]];
				for(j = 0; j < acceptItem[i]; j++) {
					acceptItemArray[i][j] = "";
				}
			}

			node = doc.first_node();
			i = 0;
			curRoom = 0;
			curItem = 0;
			curCreat = 0;
			curCont = 0;
			Room roomToWire = roomArray[curRoom];
			char* direction;
			char* name;

			while(node != 0) {
				child = node -> first_node();
				while(child != 0) {
					if(strcmp(child->name(), (char*) "room") == 0) {
						child2 = child -> first_node();
						while(child2 != 0) {
							if(strcmp(child2 -> name(), (char*) "border") == 0) {
								child3 = child2 -> first_node();
								while(child3 != 0) {
									if(strcmp(child3 -> name(), (char*) "name") == 0) {
										name = child3 -> value();
									}
									else if(strcmp(child3 -> name(), (char*) "direction") == 0) {
										direction = child3 -> value();
									}
									child3 = child3 -> next_sibling();
								}
								wireRoom(roomArray, &(roomArray[curRoom]), name, direction, maxRoomCount); // Points the borders of the current room to the proper room in roomArray
							}
							else if(strcmp(child2 -> name(), (char*) "item") == 0) {
								wireItem(itemArray, &(roomInventories[curRoom][roomInventoryCount[curRoom]]), child2 -> value(),  maxItemCount); // Points the proper room in the roomArray to the proper item in itemArray
								roomInventoryCount[curRoom]++;
							}
							else if(strcmp(child2 -> name(), (char*) "container") == 0) {
								wireCont(contArray, &(roomContainers[curRoom][roomContCount[curRoom]]), child2 -> value(), maxItemCount);
								roomContCount[curRoom]++;
							}
							child2 = child2 -> next_sibling();
						}
						curRoom++;
					}
					else if (strcmp(child->name(), (char*) "item") == 0) {
						// TODO - address any pointers in an item
					}
					else if (strcmp(child->name(), (char*) "creature") == 0) {
						// TODO - address any pointers in a creature
					}
					else if (strcmp(child->name(), (char*) "container") == 0) {
						child2 = child -> first_node();
						while(child2 != 0) {
							if(strcmp(child2 -> name(), (char*) "item") == 0) {
								wireItemInCont(itemArray, &(contInventories[curCont][contItemCount[curCont]]), child2 -> value(), maxItemCount);
								contItemCount[curCont]++;
							}
							else if(strcmp(child2 -> name(), (char*) "accept") == 0) {
								acceptItemArray[curCont][i] = string(child2 -> value());
								i++;
							}
							child2 = child2 -> next_sibling();
						}
						i = 0;
						curCont++;
					}
					child = child -> next_sibling();
				}
				node = node -> next_sibling();
			}
			Adventurer player = Adventurer();
			//player.Loc = gameMap.Start;
			player.Loc = findRoom(roomArray, (char*) "Entrance", maxRoomCount); 	// Finds room named Entrance in roomArray, points adventurer to that room
			i = 0;
			int strWord = 0;

			std::string comp_input;
			std::vector <std::string> input_vec;
			std::vector <std::string>::iterator curWord;
			std::string start;
			std::string Word1;
			std::string Word2;
			std::string Word3;
			std::string Word4;

			int wordCount;
			int valid = 0;  //0 if invalid, 1 if take, 2 if open, 3 if read, 4 if drop, 5 if put, 6 if turn on, 7 if attack
			int roomIndex = 0;
			std::cout << player.Loc -> Description << std::endl;
			while (gameActive == 1) {
				roomIndex = findRoomIndex(roomArray, player.Loc -> Name, maxRoomCount);
				std::getline(std::cin, comp_input);

				std::istringstream iss(comp_input);
				wordCount = 0;
				for(start; iss >> start; wordCount++) {
					input_vec.push_back(start);
				}

				if(comp_input == "n") {
					player.move(&player, player.Loc -> Border[0]);
				}
				else if(comp_input == "s") {
					player.move(&player, player.Loc -> Border[2]);
				}
				else if(comp_input == "w") {
					player.move(&player, player.Loc -> Border[3]);
				}
				else if(comp_input == "e") {
					player.move(&player, player.Loc -> Border[1]);
				}
				else if(comp_input == "open exit") {
					player.openExit(&player, &gameActive);
				}
				else if(comp_input == "i") {
					player.inventory(inventory, inventoryCount);
				}
				else {

					if(i == 1) {
						if(wordCount > 4 || wordCount == 0) {		
							std::cout << "Error" << std::endl;	
						} 
						else {
							curWord = input_vec.begin();
							for( ; curWord != input_vec.end(); curWord++) {
								if(strWord == 0) {
									Word1 = *curWord;
								}
								else if(strWord == 1) {
									Word2 = *curWord;
								}
								else if(strWord == 2) {
									Word3 = *curWord;
								}
								else if(strWord == 3) {
									Word4 = *curWord;
								}
								strWord++;
							}
							strWord = 0;

							valid = validateWord(Word1, Word2, Word3, Word4, wordCount);
							if(valid == 0) {
								std::cout << "Error" << std::endl;
							}
							else if(valid == 1) {
								std::cout << "Valid is 1, takeItem Called" << std::endl;
								takeItem(roomArray, roomInventories, player.Loc, itemArray, inventory, &inventoryCount, Word2, maxRoomCount, maxItemCount, &(roomInventoryCount[roomIndex]), roomContainers[roomIndex], contItemCount, contInventories, maxContCount);
							}
							else if(valid == 2) {
								std::cout << "Valid is 2, openContainer Called" << std::endl;
								openContainer(findRoom(roomArray, player.Loc -> Name, maxRoomCount), roomIndex, roomContainers[roomIndex], roomInventories[roomIndex], contInventories, maxRoomCount, maxItemCount, maxContCount, contItemCount, &(roomInventoryCount[roomIndex]) , Word2, acceptItem, acceptItemArray);
							}
							else if(valid == 3) {
								std::cout << "Valid is 3, readItem Called" << std::endl;
								readItem(inventory, inventoryCount, Word2);
							}
							else if(valid == 4) {
								std::cout << "Valid is 4, dropItem Called" << std::endl;
								dropItem(roomArray, roomInventories, player.Loc, itemArray, inventory, &inventoryCount, Word2, maxRoomCount, maxItemCount, &(roomInventoryCount[roomIndex]));
							}
							else if(valid == 5) {
								std::cout << "Valid is 5, putItem Called" << std::endl;
								putItem(contInventories, inventory, roomContainers[roomIndex], roomIndex, maxItemCount, maxContCount, Word2, Word4, contItemCount, &(inventoryCount), acceptItem, acceptItemArray);
							}
							else if(valid == 6) {
								std::cout << "Valid is 6, turnOnItem Called" << std::endl;
								//turnOnItem
							}
							else if(valid == 7) {
								std::cout << "Valid is 7, attack Called" << std::endl;
								//attack
							}
							else {
								std::cout << "Something really went wrong with validateWord" << std::endl;
							}	
						}
						
					}
					else {
						i = 1;
					}
				}
				input_vec.clear();
			}

			if(roomArray != NULL) {
				delete [] roomArray;
			}
			if(itemArray != NULL) {
				delete [] itemArray;
			}
			if(roomInventoryCount != NULL) {
				delete [] roomInventoryCount;
			}
			if(inventory != NULL) {
				delete [] inventory;
			}
			if(roomInventories != NULL) {
				for(i = 0; i < maxRoomCount; i++) {
					if(roomInventories[i] != NULL) {
						delete [] roomInventories[i];
					}
				}
				delete [] roomInventories;
			}

			if(contInventories != NULL) {
				for(i = 0; i < maxContCount; i++) {
					if(contInventories[i] != NULL) {
						delete [] contInventories[i];
					}
				}
				delete [] contInventories;
			}

			if(roomContainers != NULL) {
				for(i = 0; i < maxRoomCount; i++) {
					if(roomContainers[i] != NULL) {
						delete [] roomContainers[i];
					}
				}
				delete [] roomContainers;
			}
			if(roomCreatures != NULL) {
				for(i = 0; i < maxRoomCount; i++) {
					if(roomCreatures[i] != NULL) {
						delete [] roomCreatures[i];
					}
				}
				delete [] roomCreatures;
			}
			if(contTrigCount != NULL) {
				delete [] contTrigCount;
			}

			if(contItemCount != NULL) {
				delete [] contItemCount;
			}

			if(contArray != NULL) {
				delete [] contArray;
			}
			if(roomContCount != NULL) {
				delete [] roomContCount;
			}
			if(roomTrigCount != NULL) {
				delete [] roomTrigCount;
			}
			if(roomNodeArray != NULL) {
				delete [] roomNodeArray;
			}
			if(itemNodeArray != NULL) {
				delete [] itemNodeArray;
			}
			if(creatNodeArray != NULL) {
				delete [] creatNodeArray;
			}
			if(contNodeArray != NULL) {
				delete [] contNodeArray;
			}
			if(creatArray != NULL) {
			  delete [] creatArray;
			}	
		}
	}
	delete [] fileInput;
	return 0;
}
