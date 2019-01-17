#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <Windows.h>
#include "Player.h"
#include "Monster.h"
#include "Shop.h"
#include "Itemshop.h"

using namespace std;

class Map
{
public:
	Map();
	int isDone; //The main thing which makes the maps change or tells us when the player dies
	int isRepeat[10] = {0}; //Checks if accessing the same map again or not, if yes, pass onto empty map
                            //Also setting all values to 0
	bool isLoad;

	void loadMap(string fileName, Player &player); //Main data cruncher

	void printMap(); // Prints the map

	void movePlayer(char move, Player &player, Map &map, Itemshop &ishop);	//sees if player move is possible

	char getTile(int x, int y); //Getters

	void setTile(int x, int y, char tile); //Setters

	void processPMove(Player &player, int targetX, int targetY, Map &map, Itemshop &ishop); //Process player move
	void processMoMove(Player &player, int targetX, int targetY, Map &map, int monsterNumber); //Process monster move

	void initBattle(Player &player, int targetX, int targetY, Map &map); //Just the simple battle
	void initBattle(Player &player, int targetX, int targetY, Map &map, int i); //Monster starts the battle

	void mapSave(Map &map, Player &player); //Saves all the data to a txt with player name

	void updateMonsters(Player &player, Map &map); //update monster position

	vector <string> _mapData; //Map data

	vector <Monster> monster; //Monster data

	list <Shop> shops; //passing a list of shops
};

#endif // MAP_H
