#include "Monster.h"
#include <time.h>
#include <random>
#include <limits>

using namespace std;

Monster::Monster(string name, char tile, int health, int attack, int defense, int evasion, int exp, int gold)
{
	_mtile = tile;
	_name = name;
	_gexp = exp;
	_mhealth = health;
	_mdefense = defense;
	_mattack = attack;
	_mevasion = evasion;
	_ggold = gold;
}

//Sets the Position of the Monster
void Monster::setPosition(int x, int y)
{
	_mx = x;
	_my = y;
}

//Gets the position of the Monster using refernce variables
void Monster::getPosition(int &x, int &y)
{
	x = _mx;
	y = _my;
}

char Monster::getMove(int playerX, int playerY)
{
	mt19937 RG(time(0)); //Random generator
	uniform_int_distribution<int> rMove(0, 3); //For random move

	int distance; //Distance from player
	int dx = _mx - playerX; //differnece in x
	int dy = _my - playerY; //differnece in y
	int adx = abs(dx); //abs always give postive output
	int ady = abs(dy);

	distance = adx + ady;  //Following algo not working

	if (distance <= 5) {
		//Move along the x-axis
		if (adx > ady) {
			if (dx > 0) { //if player is to the left
				return 'a'; //move to the left
			}
			else {
				return 'd'; //move to the right
			}
		}
		else { //Move along y-axis
			if (dy > 0) { //if player is up
				return 'w'; //move to the up
			}
			else {
				return 's'; //move to the down
			}
		}
	}

	int randomMove = rMove(RG); // random move
	switch (randomMove)
	{
	case 0:
		return 'a';
		break;
	case 1:
		return 'w';
		break;
	case 2:
		return 's';
		break;
	case 3:
		return 'd';
		break;
	default:
		return '.';
		break;
	}
}
