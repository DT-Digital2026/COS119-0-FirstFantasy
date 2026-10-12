#pragma once

#include "Item.h"

class ItemCatalog {
public:
	Item CreateHealthPotion(); 

	Item CreateAsePotion(); 

	Item CreateGreaterHealthPotion(); 

	Item CreateAntiVenom(); 

	//Ora'Kanu's equipment. 
	Item CreateStormWornBracers(); 

	Item CreateShamanBracers(); 

	Item CreateTempestBracers(); 

	//M'Batha's Equipment. 
	Item CreateDhambeWraps(); 

	Item CreateReinforcedWraps(); 

	Item CreateChampionWraps(); 

	//Armor. 
	Item CreateHideVest(); 

	Item CreateHardenedHideArmor(); 

	//Key Items. 
	Item CreateChildsNecklace(); 

	Item CreateShamanTalisman(); 

	Item CreateBloodRootKey(); 
};