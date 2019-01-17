#include "Player.h"

Player::Player()
{
    _experience = 0;
    _money = 2000;
}


//Sets the Position of the Player
void Player::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

//Gets the position of the player using refernce variables
void Player::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}

void Player::initPlayer(Player &player)
{
	cout << "Enter your name Adventurer: ";
	cin >> _name;
	//Player data
	_level = 1;
	_health = 150;
	_defense = 25;
	_attack = 145;
	_evasion = 3;

	//Player Items
	player.addItem(Item("Broken Sword", 50, 'A', 10));
	player.addItem(Item("Broken Armour", 50, 'D', 10));
	player.addItem(Item("Broken Helmet", 50, 'H', 10));
	player.addItem(Item("Broken Boots", 50, 'E', 2));
}

void Player::addItem(Item newItem)
{
	list<Item>::iterator lit;

	for (lit = _items.begin(); lit != _items.end(); lit++) {
		//if they have the same name we'll add it to our current item in our item list
		if ((*lit).getName() == newItem.getName()) {
			(*lit).addItem();
			//to quit the loop
			return;
		}
	}
	_items.push_back(newItem); //push back the new item in the inventory
}

void Player::finalStats(Player &player)
{
	list<Item>::iterator lit;
	char rstatType; //Returned from shop stat value type

					//Goes through all the items in player inventory and then adds the value of stat to the hero if the stat type matches
	for (lit = _items.begin(); lit != _items.end(); lit++) {
		rstatType = (*lit).getStatType();
		switch (rstatType)
		{
		case 'A':
			_uattack = _attack + (*lit).getStaty(); //updated attack (original attack + attack by equipment)
			break;
		case 'D':
			_udefense = _defense + (*lit).getStaty(); //updated defense (original defense + defense by equipment)
			break;
		case 'H':
			_uhealth = _health + (*lit).getStaty(); //updated health (original health + health by equipment)
			break;
		case 'E':
			_uevasion = _evasion + (*lit).getStaty(); //updated evasion (original evasion + evasion by equipment)
			break;
		default:
			break;
		}
	}
}


void Player::printUStats() //Prints out current data of hero;
{
	cout << "Adventurer: " << _name;
	cout << "\nLEVEL: " << _level << "/20" << endl;
	cout << "\nGold: " << _money << "g" << endl;
	cout << "Experience: " << _experience << "/" << nextLevel() << endl;
	cout << "Health: " << _uhealth << "/" << _maxhealth << " (" << _health << "+" << getSpecificStat('H') << ")" << endl;
	cout << "Defense: " << _udefense << " (" << _defense << "+" << getSpecificStat('D') << ")" << endl;
	cout << "Attack: " << _uattack << " (" << _attack << "+" << getSpecificStat('A') << ")" << endl;
	cout << "Evasion: " << _uevasion << "%" << " (" << _evasion << "%+" << getSpecificStat('E') << "%)" << endl;
}

void Player::checkLevel(Player &player)
{
	switch (_level)
	{
	case 1:
		if (_experience >= nextLevel()) {
			_experience -= nextLevel(); //Decrease xp by the requried xp
			_level++;
			cout << "\n**Level up!**" << endl;
			cin.get();
			_health += 10;
			_attack += 2;
			_defense += 2;
			_evasion += 1;
			finalStats(player);
			setMaxhealth();
		}
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		if (_experience > nextLevel()) {
			_experience -= nextLevel();
			_level++;
			cout << "\n**Level up!**" << endl;
			cin.get();
			_health += 15;
			_attack += 2;
			_defense += 2;
			_evasion += 1;
			finalStats(player);
			setMaxhealth();
		}
		break;
	default:
		break;
	}
}

void Player::compHealth()
{
	if (_uhealth > _maxhealth) {
		_uhealth = _maxhealth;
	}
}


int Player::nextLevel()
{
	switch (_level)
	{
	case 1:
		return 100;
		break;
	case 2:
		return 250;
		break;
	case 3:
		return 450;
		break;
	default:
		break;
	}
}

void Player::loadInventory()
{
	list <Item> ::iterator lit;
	string nPart1;
	string nPart2;
	char statType;
	int staty;
	int value;

	//Gets player inventory
	string filename = "Items" + _name + ".txt";
	cout << filename << endl;
	ifstream file;
	file.open(filename);
	if (file.fail()) {
		cout << "Saving Failed!" << endl;
		cin.get();
	}
	else {
		while (file >> nPart1 >> nPart2 >> value >> statType >> staty) {
			_items.push_back(Item(nPart1 + " " + nPart2, value, statType, staty));
		}
	}
}

void Player::saveInventory()
{
	list <Item> ::iterator lit;

	//Stores player inventory
	string filename = "Items" + _name + ".txt";
	cout << filename << endl;
	ofstream myfile(filename);
	if (myfile.is_open())
	{
		for (lit = _items.begin(); lit != _items.end(); lit++) {
			myfile << (*lit).getName() << ' ' << (*lit).getValue() << (*lit).getStatType() << ' ' << (*lit).getStaty() << endl;
		}
	}
	else {
		cout << "Saving Failed!";
		cin.get();
	}
}

//Printing the current inventory
void Player::printInventory()
{
	cout << "\n***" << _name << "'s inventory***\n";
	//cout << "Gold: " << _money << endl;
	list<Item>::iterator lit;

	//i is set to one so that the numbering starts from one
	int i = 1;
	//Traversing through the array to get names of items and the amount of items
	for (lit = _items.begin(); lit != _items.end(); lit++) {
		cout << i << ". " << (*lit).getName(); getItemType((*lit).getStatType(), (*lit).getStaty()); //Print out details about the item
																									 //<< "\n     x " << (*lit).getCount() << " Sell for: " << ((*lit).getValue()) / 2 << " gold" << endl;
		i++;
	}
}

void Player::getItemType(char type, int stat)
{
	switch (type)
	{
	case 'A':
		cout << "\n   Attack: +" << stat << endl;
		break;
	case 'D':
		cout << "\n   Defense: +" << stat << endl;
		break;
	case 'H':
		cout << "\n   Health: +" << stat << endl;
		break;
	case 'E':
		cout << "\n   Evasion: +" << stat << "%" << endl;
		break;
	}
}

int Player::getSpecificStat(char stat)
{
	list<Item>::iterator lit;
	char rstat; //to check if the stat type of sent type and item type matches

	for (lit = _items.begin(); lit != _items.end(); lit++) {
		rstat = (*lit).getStatType();
		if (rstat == stat) {
			return (*lit).getStaty();
		}
	}
}

//to check if player doesnt get two swords and so on
bool Player::itemRepeat (char name)
{
    list<Item>::iterator lit;

     for (lit = _items.begin(); lit!= _items.end(); lit++){
        //to find if the items exists or not, if it does not, we return false
        if ((name == (*lit).getStatType()) && ( name == 'A' || name == 'B' || name == 'D' || name == 'H'))
            return false;
    }
    return true;
}

//To verify if purchase is valid or not
 bool Player::canAffordItem(string name, int money)
 {
     list<Item>::iterator lit;

     for (lit = _items.begin(); lit!= _items.end(); lit++){
        //to find if the items exists or not, if it does not, we return false
        if ((*lit).getName() == name) {
            if((*lit).getValue() <= money){
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
 }

 bool Player::removeItem(string name, Item &newItem)
{
    list<Item>::iterator lit;

    for (lit = _items.begin(); lit!= _items.end(); lit++){
        //if they have the same name we'll remove it from our current item in our item list
        if ((*lit).getName() == name) {
            newItem = (*lit);
            (*lit).removeItem();
            if((*lit).getCount() == 0) {
                 _items.erase(lit);
            }
            //quit the shop after we're done
            return true;
        }
    }
    return false;
}

