#include <iostream>

#include "Inventory.h"

//====================
//Default Constructor
//====================

//Leaving empty so the mItems vector can begin empty.
Inventory::Inventory() {
}

//====================
//Add Item
//====================
void Inventory::AddItem(const Item& item) {
	mItems.push_back(item); 
}

//====================
//Remove Item
//====================
bool Inventory::RemoveItem(int index) {
	//Checks for an invalid index. 
	if (index < 0 || index >= static_cast<int>(mItems.size())) {
		return false; 
	}
	//Removes the item at the selected index. 
	mItems.erase(mItems.begin() + index); 

	return true; 
}

//====================
//Display Inventory
//====================
void Inventory::DisplayInventory() const {
	std::cout << "\n=-=-= Inventory =-=-=\n"; 

	//Checks if the inventory is empty. 
	if (mItems.empty()) {
		std::cout << "Inventory is Empty.\n"; 
		return; 
	}

	//Loops through and displays each item. 
	for (int i = 0; i < static_cast<int>(mItems.size()); i++) {
		std::cout << i + 1 << ". " << mItems[i].GetName() << std::endl;
	}
}

//====================
//Get Item Count
//====================
int Inventory::GetItemCount() const {
	return static_cast<int>(mItems.size());
}

//========================
//v.03 Get Item
//========================
const Item* Inventory::GetItem(int Index) const {
	//Validate the requested index. 
	if (Index < 0 || Index >= static_cast<int>(mItems.size())) {
		return nullptr; 
	}
	return &mItems[Index];
}

//=========================
//v.04 GetItemByName
//=========================
int Inventory::FindItemByName(const std::string& name) const {
	for (int i = 0; i < static_cast<int>(mItems.size()); i++) {
		if (mItems[i].GetName() == name) {
			return i; 
		}
	}
	return -1; 
}