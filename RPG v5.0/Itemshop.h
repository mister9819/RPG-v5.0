#ifndef ITEMSHOP_H
#define ITEMSHOP_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <limits>
#include <list>
#include "Shop.h"
#include "Player.h"
#include "Item.h"

class Itemshop
{
public:
	Itemshop();
	void initShops(list<Shop> &shops);
	void enterShop(Player &player, Shop &shops);
	int getInt();
	void callShop(Player &player, list<Shop> &shops);
};

#endif // ITEMSHOP_H
