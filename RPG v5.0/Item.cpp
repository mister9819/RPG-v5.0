#include "Item.h"


Item::Item(string name, int value, char statType, int staty)
{
	//Constructor to initliaze an item
	_name = name;
	_statType = statType;
	_staty = staty;
	_value = value;
	_count = 1;
}

void Item::addItem()
{
	_count++;	//Adds count to the item
}

//decrease the count of the item by one only if there are more than one item
void Item::removeItem()
{
    if ( _count > 0){
        _count--;
    }
}
