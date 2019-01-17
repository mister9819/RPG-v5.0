#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

class Item
{
public:

    //To add and remove items.
    void addItem();
    void removeItem();

    //Getters
	Item(string name, int value, char statType, int staty); //Gives an item it's property
	string getName() { return _name; } //Returns name of the item
	int getValue() {return _value; }
    int getCount() {return _count; }
	char getStatType() { return _statType; } //Returns type of item
	int getStaty() { return _staty; } //Returns value of stat

	//Setters
    void setCount(int count) { _count = count; }

private:
	//Characteristics of an item
	string _name;
	char _statType;
	int _staty;
	int _count;
	int _value;
};

#endif // ITEM_H
