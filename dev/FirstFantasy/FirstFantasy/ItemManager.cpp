#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "ItemManager.h"

void ItemManager::UseItemOutsideofCombat(Inventory& inventory, Character& OraKanu, Character& Mbatha) {
	
	if (inventory.GetItemCount() == 0) {
		std::cout << "\nYour inventory is empty.\n"; 
		return; 
	}
	inventory.DisplayInventory(); 

	std::string input; 

	std::cout << "\nSelect an item number (0 to cancel): "; 
	std::getline(std::cin, input); 

	int itemChoice = -1; 

	try {
		size_t position = 0; 
		itemChoice = std::stoi(input, &position); 

		if (position != input.length()) {
			std::cout << "\nInvalid item selection.\n"; 
			return; 
		}
	}
	catch (const std::exception&) {
		std::cout << "\nInvalid item selection.\n"; 
		return; 
	}
	//Cancel item selection.
	if (itemChoice == 0) {
		return;
	}
	//Inventory display must number items starting at 1. 
	int ItemIndex = itemChoice - 1; 

	const Item* item = inventory.GetItem(ItemIndex); 

	if (item == nullptr) {
		std::cout << "\nThat item does not exist.\n"; 
		return; 
	}

	if (item->GetType() != ItemType::Consumable) {
		std::cout << "\nThat item cannot be consumed.\n"; 
		return; 
	}

	std::cout << "\nWho should receive " << item->GetName() << "?\n"; 
	std::cout << "1. " << OraKanu.GetName() << "\n"; 
	std::cout << "2. " << Mbatha.GetName() << "\n"; 
	std::cout << "0. Cancel\n"; 
	std::cout << "\nSelection";

	std::getline(std::cin, input); 

	Character* target = nullptr; 

	if (input == "1") {
		target = &OraKanu;
	}
	else if (input == "2") {
		target = &Mbatha; 
	}
	else {
		return; 
	}
	int restoredHP = std::min(
		item->GetHPRest(),
		target->GetMaxHP() - target->GetHP()
	);

	int restoredAse = std::min(
		item->GetAseRest(),
		target->GetMaxAse() - target->GetAse()
	);

	if (restoredHP <= 0 && restoredAse <= 0)
	{
		std::cout << "\n" << target->GetName()
			<< " does not need this item.\n";
		return;
	}

	std::string itemName = item->GetName();

	target->SetHP(target->GetHP() + restoredHP);
	target->SetAse(target->GetAse() + restoredAse);

	inventory.RemoveItem(ItemIndex);

	std::cout << "\n" << target->GetName()
		<< " used " << itemName << "!\n";

	if (restoredHP > 0)
	{
		std::cout << "Restored " << restoredHP << " HP.\n";
	}

	if (restoredAse > 0)
	{
		std::cout << "Restored " << restoredAse << " Ase.\n";
	}
}
//Allows consumable during combat. 
//Returns true only when an item is successfully consumed. 
bool ItemManager::UseItemInCombat(Inventory& inventory, Character& OraKanu, Character& Mbatha) {
	if (inventory.GetItemCount() == 0) {
		std::cout << "\nYour inventory is empty.\n"; 
		return false; 
	}
	inventory.DisplayInventory(); 

	std::cout << "\nSelect an item number (0 to cancel): "; 

	std::string input;
	std::getline(std::cin, input); 

	int itemChoice = -1; 

	try {
		size_t position = 0; 
		itemChoice = std::stoi(input, &position); 

		if (position != input.length()) {
			std::cout << "\nInvalid item selection.\n"; 
			return false; 
		}
	}
	catch (const std::exception&) {
		std::cout << "\nInvalid item selection.\n"; 
		return false; 
	}
	if (itemChoice == 0) {
		return false; 
	}
	int itemIndex = itemChoice - 1; 

	const Item* item = inventory.GetItem(itemIndex); 

	if (item == nullptr) {
		std::cout << "\nThat item does not exist.\n"; 
		return false; 
	}
	if (item->GetType() != ItemType::Consumable) {
		std::cout << "\nThat item cannot be consumed.\n"; 
		return false; 
	}
	std::cout << "\nWho should receive " << item->GetName() << "?\n"; 
	std::cout << "1. " << OraKanu.GetName() << "\n"; 
	std::cout << "2. " << Mbatha.GetName() << "\n"; 
	std::cout << "0. Cancel\n"; 
	std::cout << "\nSelection: "; 

	std::getline(std::cin, input); 

	Character* target = nullptr; 

	if (input == "1") {
		target = &OraKanu; 
	}
	else if (input == "2") {
		target = &Mbatha; 
	}
	else {
		return false; 
	}
	//Prevent healing a defeated character for new. 
	if (target->GetHP() <= 0) {
		std::cout << "\nCannot use this item on a defeated character.\n"; 
		return false; 
	}
	int restoredHP = std::min(item->GetHPRest(), target->GetMaxHP() - target->GetHP()); 

	int restoredAse = std::min(item->GetAseRest(), target->GetMaxAse() - target->GetAse()); 

	if (restoredHP <= 0 && restoredAse <= 0) {
		std::cout << "\n" << target->GetName() << " does not need this item.\n"; 
		return false; 
	}
	std::string itemName = item->GetName(); 

	target->SetHP(target->GetHP() + restoredHP); 
	target->SetAse(target->GetAse() + restoredAse); 

	inventory.RemoveItem(itemIndex); 

	std::cout << "\n" << target->GetName() << " used " << itemName << "!\n"; 

	if (restoredHP > 0) {
		std::cout << "Restored " << restoredHP << "HP.\n"; 
	}
	if (restoredAse > 0) {
		std::cout << "Restored " << restoredAse << "Ase.\n"; 
	}
	return true; 
}

//=============================================
//v.04 Equip Items Outside of Combat
//=============================================
void ItemManager::EquipItemOutsideofCombat(Inventory& inventory, Character& OraKanu, Character& Mbatha) {
	//Check whether the inventory contains items. 
	if (inventory.GetItemCount() == 0) {
		std::cout << "\nYour inventory is empty.\n"; 
		return; 
	}
	inventory.DisplayInventory(); 

	std::cout << "\nSelect equipment number (0 to cancel): "; 

	std::string input; 
	std::getline(std::cin, input); 

	int itemChoice = -1; 

	try {
		size_t position = 0; 
		itemChoice = std::stoi(input, &position); 

		if (position != input.length()) {
			std::cout << "\nInvalid item selection.\n"; 
			return; 
		}
	}
	catch (const std::exception&) {
		std::cout << "\nInvalid item selection.\n"; 
		return; 
	}
	//Cancel equipment selection. 
	if (itemChoice == 0) {
		return; 
	}
	//Convert displayed number to vector index. 
	int itemIndex = itemChoice - 1; 

	const Item* selectedItem = inventory.GetItem(itemIndex); 

	if (selectedItem == nullptr) {
		std::cout << "\nThat item does not exist.\n"; 
		return; 
	}
	//Only weapons and armor can be equipped. 
	if (selectedItem->GetType() != ItemType::Weapon && selectedItem->GetType() != ItemType::Armor) {
		std::cout << "\nThat item cannot be equipped.\n"; 
		return; 
	}
	//Copy item before modifying inventory. 
	Item equipment = *selectedItem; 

	std::cout << "\nWho should equip " << equipment.GetName() << "?\n"; 
	std::cout << "1. " << OraKanu.GetName() << "\n"; 
	std::cout << "2. " << Mbatha.GetName() << "\n"; 
	std::cout << "0. Cancel!\n"; 
	std::cout << "\nSelection: "; 

	std::getline(std::cin, input); 

	Character* target = nullptr; 

	if (input == "1") {
		target = &OraKanu; 
	}
	else if (input == "2") {
		target = &Mbatha; 
	}
	else {
		return; 
	}
	//Save previously equipped item, if any. 
	const Item* previousEquipment = nullptr; 

	if (equipment.GetType() == ItemType::Weapon) {
		previousEquipment = target->GetEquippedWeapon(); 
	}
	else {
		previousEquipment = target->GetEquippedArmor(); 
	}
	//Copy previous equipment before replacing it. 
	//The character's equipment slot will be overwritten. 
	bool hasPreviousEquipment = (previousEquipment != nullptr); 
	Item oldEquipment = equipment; 

	if (hasPreviousEquipment) {
		oldEquipment = *previousEquipment; 
	}
	//Equip the selected item. 
	if (!target->EquipItem(equipment)) {
		return; 
	}
	//Remove newly equipped item from inventory.
	inventory.RemoveItem(itemIndex);

	//Return replaced equipment to inventory.
	if (hasPreviousEquipment) {
		inventory.AddItem(oldEquipment);

		std::cout << oldEquipment.GetName()
			<< " returned to inventory.\n";
	}
}
