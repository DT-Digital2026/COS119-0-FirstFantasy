#pragma once

#include <vector> 

#include "Item.h"

//Creation of inventory class. 
class Inventory {
public:
	//Default constructor.
	Inventory(); 

	//Add an item to inventory.
	void AddItem(const Item& Item); 

	//Remove an item from inventory. 
	bool RemoveItem(int Index); 

	//Display everything currently in the inventory. 
	void DisplayInventory() const; 

	//Gets the number of items currently stored. 
	int GetItemCount() const; 

private:
	//Create a vector of Item objects. 
	std::vector<Item> mItems; 
};