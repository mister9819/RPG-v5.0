#include "Map.h"
#include <fstream>
#include <iostream>
#include <conio.h>

using namespace std;

Map::Map()
{
	isRepeat[1] = 1; //setting map1 value to 1
	isLoad = false; //set loading game to false changes to true if we want to load
}

void Map::loadMap(string fileName, Player &player)
{

	//Clears the map data
	_mapData.erase(_mapData.begin(), _mapData.end());
	//Clear the monster data
	monster.erase(monster.begin(), monster.end());

	//Loads the map
	string line;

	ifstream file;
	file.open(fileName);
	if (file.fail()) {

		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	while (getline(file, line)) {
		_mapData.push_back(line);
	}

	file.close();

	//Processes the map
	char tile;
	for (unsigned int i = 0; i < _mapData.size(); i++) {
		for (unsigned int j = 0; j < _mapData[i].size(); j++) {	//i loops through each row and j loops through every letter in that row
			tile = _mapData[i][j]; //Finds the position of tile

			switch (tile) {
			case '@':
				player.setPosition(j, i);
				break;
			case 'G': //Creating goblins
				monster.push_back(Monster("Goblin", 'G', 150, 30, 20, 10, 100, 100));
				monster.back().setPosition(j, i);
				break;
			case 'D': //Creating dragons
				monster.push_back(Monster("Dragon", 'D', 1500, 30, 20, 10, 100, 100));
				monster.back().setPosition(j, i);
				break;
			}
		}
	}
}

void Map::printMap()
{
	system("CLS");
	for (unsigned int i = 0; _mapData.size() > i; i++) {
		printf("%s\n", _mapData[i].c_str());
	}
	printf("\n");
}

void Map::movePlayer(char move, Player &player, Map &map, Itemshop &ishop)
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);
	char confirm;

	switch (move) {
	case 'w':	//up
		processPMove(player, playerX, playerY - 1, map, ishop);
		break;
	case 's':	//down
		processPMove(player, playerX, playerY + 1, map, ishop);
		break;
	case 'a':	//left
		processPMove(player, playerX - 1, playerY, map, ishop);
		break;
	case 'd':	//right
		processPMove(player, playerX + 1, playerY, map, ishop);
		break;
	case 'q':
		cout << "\nAre you sure you want to quit the game?(Y/N): ";
		confirm = getch();
		if (confirm == 'y' || confirm == 'Y')
			map.isDone = 0;
		break;
	case 'p':
		system("cls");
		player.printUStats();
		player.printInventory();
		system("Pause");
		printMap();
		break;
	case 'o':
		map.mapSave(map, player);
		break;
	}
}

char Map::getTile(int x, int y)
{
	return _mapData[y][x];
}

void Map::setTile(int x, int y, char tile)
{
	_mapData[y][x] = tile;
}

void Map::processPMove(Player &player, int targetX, int targetY, Map &map, Itemshop &ishop)
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '#':
		break;
	case ' ':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, ' ');
		setTile(targetX, targetY, '@');
		break;
	case 'G':
	case 'D':
		initBattle(player, targetX, targetY, map);
		break;
    case 'S':
        ishop.callShop(player, shops);
        player.finalStats(player);
        break;
	case '1':
			system("CLS");
			map.isDone = 11;
		break;
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		if (map.isRepeat[moveTile - 48] > 0) { //using - 48 and - 38 to convert chat to int
			system("CLS");
			map.isDone = moveTile - 38;
		} else {
			system("CLS");
			map.isRepeat[moveTile - 48] += 1;
			map.isDone = moveTile - 48;
		}
		break;
	}
}

void Map::initBattle(Player &player, int targetX, int targetY, Map &map) //Battle time!
{
	mt19937 RG(time(0)); //Random generator
	system("cls");

	int monsterX;
	int monsterY;

	for (unsigned int i = 0; i < monster.size(); i++) {
		monster[i].getPosition(monsterX, monsterY);
		if (targetX == monsterX && targetY == monsterY) {
			while (true) {
				printMap();
				Sleep(500);
				uniform_int_distribution<int> attChance(0, 100); //For dodging
				uniform_int_distribution<int> attMul(90, 100); //Attack power

				//player attacks
				if (attChance(RG) > monster[i].getMevasion()) { //See if monster dodges or not
					if ((monster[i].getMdefense() / 2) < player.getUattack()) //See if monster's defense is less than player attack
					{
						int mhealth = monster[i].getMhealth();
						mhealth = mhealth + (monster[i].getMdefense() / 2) - (((attMul(RG))*player.getUattack()) / 100); //Reduces monster health
						cout << "\nYou did " << monster[i].getMhealth() - mhealth << " damage!" << endl;
						monster[i].setMhealth(mhealth);
						if (monster[i].getMhealth() < 0) {
							cout << "Monster Health after damage: 0" << endl;
						}
						else { cout << "Monster Health after damage: " << monster[i].getMhealth() << endl; }
						Sleep(500);
					}
					else { cout << "\nYour attack is too weak!" << endl; Sleep(500); }
				}
				else { cout << "\nMonster Dodges!" << endl; Sleep(500); }
				if (monster[i].getMhealth() <= 0) {	break; }

				//monster attacks
				if (attChance(RG) > player.getUevasion()) { //See if player dodges or not
					if ((player.getUdefense() / 2) < monster[i].getMattack()) { //See if player's defense is less than monster attack
						int uhealth = player.getUhealth();
						uhealth = uhealth + (player.getUdefense() / 2) - (((attMul(RG))*monster[i].getMattack()) / 100); //Reduces player health
						cout << "\nMonster did " << player.getUhealth() - uhealth << " damage!" << endl;
						player.setUhealth(uhealth);
						player.compHealth();
						cout << "Your Health after damage: " << player.getUhealth() << endl;
						Sleep(500);
					}
					else { cout << "\nYour defense is too strong!" << endl; Sleep(500); }
				}
				else { cout << "\nYou Dodge!" << endl; Sleep(500); }
				if (player.getUhealth() <= 0) { break; }
				system("cls");
			}

			if (monster[i].getMhealth() <= 0) {
				cout << "\nMonster Died!" << endl;
				cout << "Experience= +" << monster[i].getGexp() << endl;
				cout << "Gold= +" << monster[i].getGgold() << endl;
				Sleep(1000);
				player.setExp(monster[i].getGexp()); //gives exp to player
				player.addMoney(monster[i].getGgold()); //gives money to player
				player.checkLevel(player); //checks if player levelled up
				monster[i] = monster.back();  // removes
				monster.pop_back();			 // the
				i--;						// enemy
				setTile(targetX, targetY, ' '); //sets monster tile to null
			}
			if (player.getUhealth() <= 0) {
				cout << "You died!" << endl;
				Sleep(500);
				map.isDone = 0; } //if player dies, breaks the game out of the main loop
		}
	}
}

void Map::mapSave(Map &map, Player &player)
{
	string filename = player.getName() + ".txt";
	cout << filename << endl;
	ofstream file;
	file.open(filename);
	if (file.fail()) {
		cout << "Saving Failed!" << endl;
		system("PAUSE");
	}
	file << player.getName() << " " << player.getLevel() << " " << player.getExp() << " " << player.getHealth() << " " << player.getMaxhealth() << " " << player.getAttack() << " " << player.getDefense() << " " << player.getEvasion() << " " << player.getMoney() << " " << map.isDone << " ";
	for (int i = 0; i < 10; i++) {
		file << map.isRepeat[i] << " ";
	}

	filename = "Map" + player.getName() + ".txt";
	cout << filename << endl;
	ofstream mappy;
	mappy.open(filename);
	if (mappy.fail()) {
		cout << "Saving Failed!" << endl;
		system("PAUSE");
	} else {
		for (unsigned int i = 0; _mapData.size() > i; i++) {
			mappy << _mapData[i] << endl;
		}
	}
	player.saveInventory();
	cout << "Saving Successful!" << endl;
	system("PAUSE");
}

void Map::processMoMove(Player &player, int targetX, int targetY, Map &map, int monsterNumber)
{
	int playerX;
	int playerY;
	player.getPosition(playerX, playerY); //get and set player coords

	int monsterX;
	int monsterY;
	monster[monsterNumber].getPosition(monsterX, monsterY); //get and set monster coords

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '#':
		break;
	case ' ':
		monster[monsterNumber].setPosition(targetX, targetY);
		setTile(monsterX, monsterY, ' ');
		setTile(targetX, targetY, monster[monsterNumber].getTile());
		break;
	case '@':
		initBattle(player, targetX, targetY, map, monsterNumber);
	default:
		break;
	}
}

void Map::updateMonsters(Player &player, Map &map)
{
	char aiMove;
	int playerX;
	int playerY;
	int monsterX;
	int monsterY;

	player.getPosition(playerX, playerY);

	for (unsigned int i = 0; i < monster.size(); i++) {
		monster[i].getPosition(monsterX, monsterY);

		aiMove = monster[i].getMove(playerX, playerY);

		switch (aiMove) {
		case 'w':	//up
			processMoMove(player, monsterX, monsterY - 1, map, i);
			break;
		case 's':	//down
			processMoMove(player, monsterX, monsterY + 1, map, i);
			break;
		case 'a':	//left
			processMoMove(player, monsterX - 1, monsterY, map, i);
			break;
		case 'd':	//right
			processMoMove(player, monsterX + 1, monsterY, map, i);
			break;
		}
	}
}

void Map::initBattle(Player &player, int targetX, int targetY, Map &map, int i)
{
	mt19937 RG(time(0)); //Random generator
	system("cls");

	int monsterX;
	int monsterY;
	monster[i].getPosition(monsterX, monsterY); //get positon to remove the monster logo

	//Battle
	while (true) {
		printMap();
		Sleep(500);
		uniform_int_distribution<int> attChance(0, 100); //For dodging
		uniform_int_distribution<int> attMul(90, 100); //Attack power

		//monster attacks
		if (attChance(RG) > player.getUevasion()) { //See if player dodges or not
			if ((player.getUdefense() / 2) < monster[i].getMattack()) { //See if player's defense is less than monster attack
				int uhealth = player.getUhealth();
				uhealth = uhealth + (player.getUdefense() / 2) - (((attMul(RG))*monster[i].getMattack()) / 100); //Reduces player health
				cout << "\nMonster did " << player.getUhealth() - uhealth << " damage!" << endl;
				player.setUhealth(uhealth);
				player.compHealth();
				cout << "Your Health after damage: " << player.getUhealth() << endl;
				Sleep(500);
			}
			else { cout << "\nYour defense is too strong!" << endl; Sleep(500); }
		}
		else { cout << "\nYou Dodge!" << endl; Sleep(500); }
		if (player.getUhealth() <= 0) { break; }

		//player attacks
		if (attChance(RG) > monster[i].getMevasion()) { //See if monster dodges or not
			if ((monster[i].getMdefense() / 2) < player.getUattack()) //See if monster's defense is less than player attack
			{
				int mhealth = monster[i].getMhealth();
				mhealth = mhealth + (monster[i].getMdefense() / 2) - (((attMul(RG))*player.getUattack()) / 100); //Reduces monster health
				cout << "\nYou did " << monster[i].getMhealth() - mhealth << " damage!" << endl;
				monster[i].setMhealth(mhealth);
				if (monster[i].getMhealth() < 0) {
					cout << "Monster Health after damage: 0" << endl;
				}
				else { cout << "Monster Health after damage: " << monster[i].getMhealth() << endl; }
				Sleep(500);
			}
			else { cout << "\nYour attack is too weak!" << endl; Sleep(500); }
		}
		else { cout << "\nMonster Dodges!" << endl; Sleep(500); }
		if (monster[i].getMhealth() <= 0) { break; }
		system("cls");
	}

	if (monster[i].getMhealth() <= 0) {
		cout << "\nMonster Died!" << endl;
		cout << "Experience= +" << monster[i].getGexp() << endl;
		cout << "Gold= +" << monster[i].getGgold() << endl;
		Sleep(1000);
		player.setExp(monster[i].getGexp()); //gives exp to player
		player.addMoney(monster[i].getGgold()); //gives money to player
		player.checkLevel(player); //checks if player levelled up
		monster[i] = monster.back();  // removes
		monster.pop_back();			 // the
		i--;						// enemy
		setTile(monsterX, monsterY, ' '); //sets monster tile to null
	}
	if (player.getUhealth() <= 0) {
		cout << "You died!" << endl;
		Sleep(500);
		map.isDone = 0; } //if player dies, breaks the game out of the main loop
}
