#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>

using namespace std;

class Monster
{
public:
	//Initialzing the monster
	Monster(string name, char tile, int health, int attack, int defense, int evasion, int exp, int gold);

	//Use monster data
	char getTile() { return _mtile; }
	int getMhealth() { return _mhealth; }
	int getMdefense() { return _mdefense; }
	int getMattack() { return _mattack; }
	int getMevasion() { return _mevasion; }
	int getGexp() { return _gexp; }
	int getGgold() { return _ggold; }

	//Decrease health
	void setMhealth(int mhealth) { _mhealth = mhealth; }

	//Manipulate position
	void setPosition(int x, int y);
	void getPosition(int &x, int &y);

	//Gets AI move command
	char getMove(int playerX, int playerY);
private:
	//Monster Data
	char _mtile;
	int _mhealth;
	int _mdefense;
	int _mattack;
	int _mevasion;
	int _gexp;
	int _ggold;
	string _name;
	//Position
	int _mx;
	int _my;
};

#endif //   MONSTER_H
