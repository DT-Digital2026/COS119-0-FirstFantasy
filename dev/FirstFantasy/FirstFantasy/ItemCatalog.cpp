#include "ItemCatalog.h"

//=======================
//		Consumables
//=======================

Item ItemCatalog::CreateHealthPotion() {
	return Item("Health Potion", "Restores a small amount of HP.", ItemType::Consumable, 25, 0, 0, 0, 15);
}; 

Item ItemCatalog::CreateAsePotion() {
	return Item("Ase Potion", "Restores a small amount of Ase.", ItemType::Consumable, 0, 25, 0, 0, 15);
};

Item ItemCatalog::CreateGreaterHealthPotion() {
	return Item("Greater Health Potion", "Restores a large amount of HP.", ItemType::Consumable, 50, 0, 0, 0, 25);
}; 

Item ItemCatalog::CreateAntiVenom() {
	return Item("Antivenom", "Neutralizes venom and removes poison.", ItemType::Consumable, 0, 0, 0, 0, 20);
}; 

//======================
//Ora'Kanu's Weapons
//======================

	Item ItemCatalog::CreateStormWornBracers() {
		return Item("Stormworn Bracers", "Weathered bracers used to focus Ase.", ItemType::Weapon, 0, 0, 2, 0, 40);
	};

	Item ItemCatalog::CreateShamanBracers() {
		return Item("Shaman Bracers", "Bracers marked with symbols of spiritual power.", ItemType::Weapon, 0, 0, 4, 0);
	};

	Item ItemCatalog::CreateTempestBracers() {
		return Item("Tempest Bracers", "Powerful bracers that amplify the fury of the storm.", ItemType::Weapon, 0, 0, 7, 0);
	};

	//======================
	//M'Batha's Weapons
	//======================

	Item ItemCatalog::CreateDhambeWraps() {
		return Item("Dhambe Wraps", "Traditional fighting wraps worn by M'Batha.", ItemType::Weapon, 0, 0, 2, 0, 40);
	};

	Item ItemCatalog::CreateReinforcedWraps() {
		return Item("Reinforced Wraps", "Heavy fighting wraps reinforced for powerful strikes.", ItemType::Weapon, 0, 0, 5, 0);
	};

	Item ItemCatalog::CreateChampionWraps() {
		return Item("Champion Wraps", "Battleworn wraps worthy of a master warrior.", ItemType::Weapon, 0, 0, 8, 0);
	};

//======================
//Armor
//======================


Item ItemCatalog::CreateHideVest() {
	return Item("Hide Vest", "Simple hide armor offering basic protection.", ItemType::Armor, 0, 0, 0, 2, 35);
};

Item ItemCatalog::CreateHardenedHideArmor() {
	return Item("Hardened Hide Armor", "Layered hide hardened to withstand heavier attacks.", ItemType::Armor, 0, 0, 0, 4);
};

//======================
//Key Items
//======================


Item ItemCatalog::CreateChildsNecklace() {
	return Item("Child's Necklace", "A small necklace belonging to one of the missing children.", ItemType::KeyItem, 0, 0, 0, 0);
};

Item ItemCatalog::CreateShamanTalisman(){
	return Item("Shaman Talisman", "A sacred talisman entrusted to the party by the village shaman.", ItemType::KeyItem, 0, 0, 0, 0);
};

Item ItemCatalog::CreateBloodRootKey() {
	return Item("Blood Root Key", "An ancient key connected to BloodRoot Hollow.", ItemType::KeyItem, 0, 0, 0, 0);
};
