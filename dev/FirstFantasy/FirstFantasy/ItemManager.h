#pragma once

#include "Item.h"
#include "Inventory.h"
#include "Character.h"

class ItemManager {
public:
	//Allows Item usage while exploring. 
	static void UseItemOutsideofCombat(Inventory& inventory, Character& OraKanu, Character& Mbatha);

	//Allows item usage during combat. 
	//Returns true if an item was succesfully used. 
	static bool UseItemInCombat(Inventory& inventory, Character& OraKanu, Character& Mbatha);

	//Equip weapons and armor outside of combat. 
	static void EquipItemOutsideofCombat(Inventory& inventory, Character& OraKanu, Character& Mbatha); 
}; 
