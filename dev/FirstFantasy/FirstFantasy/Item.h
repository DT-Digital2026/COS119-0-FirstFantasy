#pragma once

#include <string>
//Enum class to build out the different types of items. 
enum class ItemType {
	Consumable, 
	Weapon, 
	Armor, 
	KeyItem, 
};
//Class for specific items. 
class Item {
public:
	//Default constructor. 
	Item();

	//Overloaded constructor. 
	Item(const std::string& Name, const std::string& Description, ItemType Type, int HPRestore, int AseRestore, int ATKBonus, int DefBonus);

	//Getters. 
	std::string GetName() const;

	std::string GetDescription() const;

	ItemType GetType() const;

	int GetHPRest() const;

	int GetAseRest() const;

	int GetAtkBonus() const;

	int GetDefBonus() const;

private:
	std::string mName;

	std::string mDescription;

	ItemType mType;

	int mHPRestore;

	int mAseRestore;

	int mAtkBonus;

	int mDefBonus;
};