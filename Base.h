#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string.h>
#include "Room.h"
#include "Item.h"
#include "Adventurer.h"
#include "Container.h"
#include "Creature.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "rapidxml.hpp"

#include <assert.h> // REMOVE BEFORE DEMO
using namespace std;
using namespace rapidxml;


Item firstItemInit(xml_node<>*);
Room firstRoomInit(xml_node<>*);
Container firstContInit(xml_node<>*, int*);
Creature firstCreatInit(xml_node<>*);
Room* findRoom(Room*, char*, int);
Item* findItem(Item*, char*, int);
Container* findCont(Container*, char*, int);
int validateWord(std::string, std::string, std::string, std::string, int);
void takeItem(Room*, Item***, Room*, Item*, Item**, int*, std::string, int, int, int*, Container**, int*, Item***, int);
void dropItem(Room*, Item***, Room*, Item*, Item**, int*, std::string, int, int, int*);
void openContainer(Room*, int, Container**, Item**, Item***, int, int, int, int*, int*, std::string, int*, std::string**);
void putItem(Item***, Item**, Container**, int, int, int, std::string, std::string, int*, int*, int*, std::string**);
int findRoomIndex(Room*, char*, int);
int findItemIndex(Item*, char*, int);
int findContIndex(Container*, char*, int);
void readItem(Item**, int, std::string);
void sortMissingItem(int*, Item**);
void wireItem(Item*, Item**, char*, int);
void wireCont(Container*, Container**, char*, int);
void wireRoom(Room*, Room*, char*, char*, int);
void wireItemInCont(Item*, Item**, char*, int);
int checkDupes(Item**, Item*, int);


#endif
