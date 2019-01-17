#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include <list>
#include <string>
#include "Item.h"

using namespace std;

class Shop
{
    public:
        Shop(string name);

        void printShop();
        bool canAffordItem(string name, int money);
        bool purchaseItem(string name, Item &newItem);
        void addItem(Item newItem);
        char itemRepeat (string name);

        //Getters
        string getName() {return _name; }

    private:
        string _name;
        //A type of an array to traverse through the items
        list<Item> _items;
};

#endif // SHOP_H
