#include "Base.h"

Adventurer::Adventurer() {
	Loc = NULL;
}
Adventurer::~Adventurer() { }

void Adventurer::inventory(Item** Inventory) {
	int i = 0;
	if(Inventory[i] == NULL) {
		std::cout << "Inventory: Empty" << std::endl;
	} else {
		std::cout << "Inventory: ";
		for(i = 0; Inventory[i] != NULL; i++) {
			std::cout << Inventory[i] -> Name;
			if(Inventory[i + 1] != NULL) {
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

