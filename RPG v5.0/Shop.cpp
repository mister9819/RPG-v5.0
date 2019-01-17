#include <iostream>
#include <list>
#include "Shop.h"



Shop::Shop(string name)
{
    _name = name;
}

void Shop::printShop()
{
    cout << "\n***Welcome to The " << _name << "***\n\n";
    //Item iterator (An iterator is any object that, pointing to some element in a range of elements)
    list<Item>::iterator lit;

    //i is set to one so that the numbering starts from one
    int i=1;
    //Traversing through the array to get names of items and the amount of items
    for (lit = _items.begin(); lit!= _items.end(); lit++){
        cout << i << ". " << (*lit).getName() << "\n" << " Price: " << (*lit).getValue() << " gold Type: " << (*lit).getStatType() << endl;
        i++;
    }

}
//To verify if purchase is valid or not
 bool Shop::canAffordItem(string name, int money)
 {
     list<Item>::iterator lit;

     for (lit = _items.begin(); lit!= _items.end(); lit++){
        //to find if the items exists or not, if it does not, we return false
        if ((*lit).getName() == name) {
            if((*lit).getValue() <= money){ //returns true if player has enough money
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
 }

//returns true if the item exists and false if it does not, so we pass in the reference parameter
bool Shop::purchaseItem(string name, Item &newItem)
{
    //iterator declared yet again...!!
    list<Item>::iterator lit;

    //Traversing through the items
    for (lit = _items.begin(); lit!= _items.end(); lit++){
        //to find if the items exists or not, if it does not, we return false
        if ((*lit).getName() == name) {
            //we are gonna send the item
            newItem = (*lit);
            //so we make a new item and return it with one count
            newItem.setCount(1);
            //we are taking away one item away from the shop
            (*lit).removeItem();

            //we need to check if the item exists or not.. if it does not we remove it from the list
            if((*lit).getCount() == 0) {
                _items.erase(lit);
            }
            return true;
        }
    }
    return false;
}

void Shop::addItem(Item newItem)
{
    list<Item>::iterator lit;

    for (lit = _items.begin(); lit!= _items.end(); lit++){
            //if they have the same name we'll add it to our current item in our item list
        if ((*lit).getName() == newItem.getName()) {
            (*lit).addItem();
            //to quit the loop
            return;
        }
    }
    //if item doesnt exist we need to add one, so we add an item.
    _items.push_back(newItem);
}

char Shop::itemRepeat (string name)
{
    //cout << "Inside item repeat" << endl;
                    //cin.get();
    list<Item>::iterator lit;
    char rstatType; //Returned from shop stat value type

    for (lit = _items.begin(); lit!= _items.end(); lit++){
        //to find if the items exists or not, if it does not, we return false
        if ((*lit).getName() == name) {
                rstatType = (*lit).getStatType();
        }
    }
     //cout << "Ummm.. " << rstatType;
     return rstatType;
}

