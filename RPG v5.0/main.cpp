#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>
#include <limits>
#include "Map.h"
#include "Player.h"
#include "Monster.h"
#include "Shop.h"
#include "Itemshop.h"

using namespace std;

void playerMove(Map &map, Player &player, Itemshop &ishop);
string to_string(int convert); //converting int to string 1-20

int main()
{
	//Iniliazes random things
	Map map; //Map 11 onwards are copy of 1 onwards but without monsters
	Player player;
	map.isDone = 1;
	int copyisDone = 1; //to know current map
	Itemshop ishop;

	ishop.initShops(map.shops); //Intitialing

	string line;
	cout << "**Welcome to a RPG game!***" << endl; //We obviously need cool things in an RPG!
	ifstream file;
	file.open("Start.txt");
	if (file.fail()) {
		system("PAUSE");
		exit(1);
	}
	while (getline(file, line)) {
		cout << line << endl;
	}

	//Load or new game?
	int load;
	cin >> load;
	if (load == 1) {
		map.isLoad = true; //sets loading to true so not to clear map
		string name;
		int level;
		int exp;
		int health;
		int maxhealth;
		int attack;
		int defense;
		int evasion;
		int money;
		cout << "Enter your username, adventurer!: ";
		cin >> name;
		//Gets player stats
		string filename = name + ".txt";
		cout << filename << endl;
		ifstream file;
		file.open(filename);
		if (file.fail()) {
			cout << "Saving Failed!" << endl;
			system("PAUSE");
		}
		else {
			file >> name >> level >> exp >> health >> maxhealth >> attack >> defense >> evasion >> money >> copyisDone >> map.isDone;
			player.setName(name);
			player.setLevel(level);
			player.setExp(exp);
			player.setHealth(health);
			player.setMaxhealth(maxhealth);
			player.setAttack(attack);
			player.setDefense(defense);
			player.setEvasion(evasion);
			player.setMoney(money);
			for (int i = 0; i < 10; i++) {
				file >> map.isRepeat[i];
			}
			player.loadInventory();
			cout << "Saving Successful!" << endl;
			system("PAUSE");
			//if (copyisDone > 10) { copyisDone -= 10; }
			map.isDone = copyisDone; //intitating the current map
		}
		player.finalStats(player); //Initializes the player when loading
		player.printUStats();
	}
	else {
		player.initPlayer(player); //Initializes the player for new game
		player.finalStats(player);
		player.setMaxhealth();
		system("CLS");
		player.printUStats();
		player.printInventory();
		system("pause");
	}

	while (map.isDone != 0) {

		string mapNum;

		if (map.isLoad == false) {
			mapNum = "Map" + to_string(copyisDone) + ".txt";
		}
		else { //if map is being loaded take it from the map file
			mapNum = "Map" + player.getName() + ".txt";
			map.isLoad = false;
		}
		map.loadMap(mapNum, player);
		map.printMap();

		while (map.isDone == copyisDone) {
			map.printMap();
			playerMove(map, player, ishop);
			map.updateMonsters(player, map);
		}
		//For saving previous instance of a map into a new txt and will only access that txt from now
		string filename;
		if (copyisDone <= 10) { //Saves the last copy of the map before player quit the map for the first time
			filename = "Map" + to_string(copyisDone + 10) + ".txt";
		}
		else if (map.isDone > 10) { //Saves the last copy of the map before player quit the map for the rest of the time
			filename = "Map" + to_string(copyisDone) + ".txt";
		}
		system("pause");
		ofstream file;
		file.open(filename);
		if (file.fail()) {
			cout << "Saving Failed!" << endl;
			system("PAUSE");
		}
		for (unsigned int i = 0; map._mapData.size() > i; i++) {
			file << map._mapData[i] << endl;
		}
		//Sets value of copyisDone so can be used when saving previous maps
		copyisDone = map.isDone;
	}
	cout << "\n**GAME OVER**" << endl;
	system("pause");
	return 0;
}

void playerMove(Map &map, Player &player, Itemshop &ishop)
{
	char move;
	printf("Enter a move command (w/s/a/d) \n(q to quit) \n(p for player) \n(o for save) \n");
	move = getch();

	map.movePlayer(move, player, map, ishop);
}

string to_string(int convert)
{
    string constring;
    switch (convert)
    {
    case 1:
        constring = "1";
        return constring;
    case 2:
        constring = "2";
        return constring;
    case 3:
        constring = "3";
        return constring;
    case 4:
        constring = "4";
        return constring;
    case 5:
        constring = "5";
        return constring;
    case 6:
        constring = "6";
        return constring;
    case 7:
        constring = "7";
        return constring;
    case 8:
        constring = "8";
        return constring;
    case 9:
        constring = "9";
        return constring;
    case 11:
        constring = "11";
        return constring;
    case 12:
        constring = "12";
        return constring;
    case 13:
        constring = "13";
        return constring;
    case 14:
        constring = "14";
        return constring;
    case 15:
        constring = "15";
        return constring;
    case 16:
        constring = "16";
        return constring;
    case 17:
        constring = "17";
        return constring;
    case 18:
        constring = "18";
        return constring;
    case 19:
        constring = "19";
        return constring;
    default:
        constring = "0";
        return constring;
    }
}
