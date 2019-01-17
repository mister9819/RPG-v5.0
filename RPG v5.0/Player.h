#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "Item.h"

using namespace std;
class Player
{
public:
	Player();

	void initPlayer(Player &player); //Initializes Player
	void addItem(Item newItem); //Adding new item
	void finalStats(Player &player); //Adds effect of items
	void printUStats(); //Prints updated stats

						//Take in player data for loading
	void setName(string name) { _name = name; }
	void setLevel(int level) { _level = level; }
	void setHealth(int health) { _health = health; }
	void setAttack(int attack) { _attack = attack; }
	void setDefense(int defense) { _defense = defense; }
	void setEvasion(int evasion) { _evasion = evasion; }
	void setMaxhealth(int maxhealth) { _maxhealth = maxhealth; }
	void setMoney(int money) { _money = money; }

	//Use player data
	string getName() { return _name; }
	int getUhealth() { return _uhealth; }
	int getUdefense() { return _udefense; }
	int getUattack() { return _uattack; }
	int getUevasion() { return _uevasion; }
	int getMaxhealth() { return _maxhealth; }
	int getLevel() { return _level; }
	int getExp() { return _experience; }

	//Use player data to save original values
	int getHealth() { return _health; }
	int getDefense() { return _defense; }
	int getAttack() { return _attack; }
	int getEvasion() { return _evasion; }

	//Sets max health
	void setMaxhealth() { _maxhealth = _uhealth; }

	// Set new health (after level up)
	void setUhealth() { _uhealth = _maxhealth; }

	//Decrease player health
	void setUhealth(int uhealth) { _uhealth = uhealth; }

	//Check for level up
	void checkLevel(Player &player);

	//Add experience
	void setExp(int experience) { _experience += experience; }

	//Get health back to normal, if ever health goes over max health
	void compHealth();

	//Setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int &x, int &y);

	//Get experience needed for next level
	int nextLevel();

	//Player inventory
	void loadInventory(); //Load
	void saveInventory(); //Save
	void printInventory(); //Print
	void getItemType(char type, int stat); //Writing attack, defense and so on..

										   //returnns the value of the specific stat using the char as in that decides the type
	int getSpecificStat(char stat);

	//Modifying player inventory
	bool canAffordItem(string name, int money);
    bool itemRepeat (char name);
    bool removeItem(string name, Item &newItem);
    int getMoney() {return _money; }
    void subtractMoney(int amount) {_money -= amount; }
    void addMoney(int amount) {_money += amount; }

private:
	//Position
	int _x;
	int _y;

	//Player experience and data
	int _level;
	int _experience;

	//Max health of player
	int _maxhealth;

	//Updated Player Data, will be used for fights!
	int _uhealth;
	int _udefense;
	int _uattack;
	int _uevasion;

	//Player Data
	int _health;
	int _defense;
	int _attack;
	int _evasion;
	string _name;
	list <Item> _items;
	int _money;
};

#endif // PLAYER_H
