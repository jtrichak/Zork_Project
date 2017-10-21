all:
	g++ -g -Wall Adventurer.cpp Container.cpp Item.cpp Room.cpp Creature.cpp main.cpp -o Zork
	./Zork
