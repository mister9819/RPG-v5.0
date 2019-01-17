#include "Itemshop.h"
#include <conio.h>

Itemshop::Itemshop()
{
}


void Itemshop::initShops(list<Shop> &shops)
{
	//making shop names
	shops.push_back(Shop("Beginner Shop"));
	//Giving items to the shops
	shops.back().addItem(Item("Normal Sword", 30, 'A', 5));
	shops.back().addItem(Item("Normal Armour", 40, 'D', 5));
	shops.back().addItem(Item("Normal Helmet", 50, 'H', 5));
	shops.back().addItem(Item("Normal Boots", 50, 'B', 5));
	//shops.back().addItem(Item("Basic Heal", 20, 'I', 5));

	shops.push_back(Shop("Blacksmith Shop"));
	shops.back().addItem(Item("Iron Sword", 80, 'A', 5));
	shops.back().addItem(Item("Iron Armour", 90, 'D', 5));
	shops.back().addItem(Item("Iron Helmet", 100, 'H', 5));
	shops.back().addItem(Item("Iron Boots", 100, 'B', 5));
	//shops.back().addItem(Item("Minor Heal", 40, 'K', 5));

	shops.push_back(Shop("Forger Shop"));
	shops.back().addItem(Item("Gold Sword", 150, 'A', 5));
	shops.back().addItem(Item("Gold Armour", 180, 'D', 5));
	shops.back().addItem(Item("Gold Helmet", 200, 'H', 5));
	shops.back().addItem(Item("Gold Boots", 200, 'B', 5));
	//shops.back().addItem(Item("Massive Heal", 80, 'X', 5));

	shops.push_back(Shop("Refiner Shop"));
	shops.back().addItem(Item("Crystal Sword", 250, 'A', 5));
	shops.back().addItem(Item("Crystal Armour", 350, 'D', 5));
	shops.back().addItem(Item("Crystal Helmet", 400, 'H', 5));
	shops.back().addItem(Item("Crystal Boots", 400, 'B', 5));
	//shops.back().addItem(Item("Epic Heal", 160, 'Y', 5));

	shops.push_back(Shop("Divine Shop"));
	shops.back().addItem(Item("Divine Sword", 500, 'A', 5));
	shops.back().addItem(Item("Divine Armour", 550, 'D', 5));
	shops.back().addItem(Item("Divine Helmet", 600, 'H', 5));
	shops.back().addItem(Item("Divine Boots", 600, 'B', 5));
	//shops.back().addItem(Item("Mystic Heal", 320, 'Z', 5));
}

void Itemshop::enterShop(Player &player, Shop &shop)
{
	bool isDone = false;
	char input;
	string itemName;

	while (isDone == false) {
		//Clear screen
		system("cls");
		//Print shop
		shop.printShop();
		//Print gold
		cout << "\nCurrent gold: " << player.getMoney();
		//Print Player inventory
		player.printInventory();
		//The item we are returning to the player
		Item newItem("NOITEM", 0, 'N', 0);
		char rStatType;

		//Ask if buy or sell
		cout << "\nWould you like to buy or sell or quit? (B/S/Q): ";
		input = getch();

		//Checking if buying or selling
		if (input == 'Q' || input == 'q') //quit
			return;

		else if (input == 'B' || input == 'b') { //buy
			cout << "\nEnter the item you wish to buy: ";
			cin.sync(); //Clear the input buffer
			getline(cin, itemName);
			cout << "Item name: " << itemName << endl;
			rStatType = shop.itemRepeat(itemName);

			if (player.itemRepeat(rStatType) == true) {
				if (shop.canAffordItem(itemName, player.getMoney())) {

					//See if shop has the item
					if (shop.purchaseItem(itemName, newItem) == true) {
						player.subtractMoney(newItem.getValue());
						player.addItem(newItem); //adds new item
					}
					else {
						cout << "That is an invalid item! (Mind the case of the letters!)\n"; //Invalid item
						cin.get();
					}
				}
				else {
					cout << "\nYou don't have enough money!\n"; //Invalid item
					cout << "-OR-\nThat is an invalid item! (Mind the case of the letters!)\n";
					cin.get();
				}
			}
			else {
				cout << "You can own only one type of this item! \nHint: Sell the other same type of item to buy another one!" << endl;
				cin.get();
			}
		}
		else if (input == 'S' || input == 's') { //sell
			cout << "\nEnter the item you wish to sell: ";
			cin.sync(); //Clear the input buffer
			getline(cin, itemName);

			//see if player has item
			if (player.removeItem(itemName, newItem) == true) {
				//shop.addItem(newItem);
				player.addMoney((newItem.getValue()) / 2);
			}
			else {
				cout << "That is an invalid item! (Mind the case of the letters!)\n"; //Invalid item
				cin.get();
			}
		}
	}
}

void Itemshop::callShop(Player &player, list<Shop> &shops)
{
	//passing a list of shops
	list<Shop>::iterator lit;
	//Single player
	int shopNumber;

	//Tells us when to exit the shop
	bool isDoneShop = false;

	while (isDoneShop == false) {
		system("cls");
		cout << "\nShops: \n";
		//Printing out shop names
		int i = 1;
		for (lit = shops.begin(); lit != shops.end(); lit++) {
			cout << i << ". " << (*lit).getName() << endl;
			i++;
		}
		cout << "6. Quit\n" << "Which shop number would you like to enter?(Input: Number)" << endl;
        cin.sync(); //Clear the input buffer

		while (1) {
			shopNumber = getInt();
			if (shopNumber < 7)
				break;
			cout << "Invalid input.  Try again: ";
		}

		if (shopNumber == 6)
			break;

		int j = 1;
		//Entering the shop
		for (lit = shops.begin(); lit != shops.end(); lit++) {
			if (j == shopNumber) {
				enterShop(player, (*lit));
			}
			j++;
		}
	}
	return;
}

int Itemshop::getInt() {
	char x;
	int z;
	bool isInt = true;
	while(isInt)
    {
        x = getch();
        switch(x)
        {
        case '1':
            z = 1;
            isInt = false;
            break;
        case '2':
            z = 2;
            isInt = false;
            break;
        case '3':
            z = 3;
            isInt = false;
            break;
        case '4':
            z = 4;
            isInt = false;
            break;
        case '5':
            z = 5;
            isInt = false;
            break;
        case '6':
            z = 6;
            isInt = false;
            break;
        }
        cout << "Try again! " << endl;
    }
	return z;
}
