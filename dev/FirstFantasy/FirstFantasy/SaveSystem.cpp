#include <iostream>
#include <fstream>
#include <string> 
#include <limits>

#include "SaveSystem.h"
#include "Game.h"


//v.05 Writes one equipment slot to the save file.
static void SaveEquipment(std::ofstream& saveFile, const Item* item) {

	//0 means this equipment slot is empty.
	if (item == nullptr) {
		saveFile << 0 << "\n";
		return;
	}

	//1 means an item is equipped.
	saveFile << 1 << "\n";

	saveFile << item->GetName() << "\n";
	saveFile << item->GetDescription() << "\n";
	saveFile << static_cast<int>(item->GetType()) << "\n";
	saveFile << item->GetHPRest() << "\n";
	saveFile << item->GetAseRest() << "\n";
	saveFile << item->GetAtkBonus() << "\n";
	saveFile << item->GetDefBonus() << "\n";
	saveFile << item->GetPrice() << "\n";
}
//v.05 Reads one equipment slot from the save file.
//Returns false if the saved equipment data is invalid.
static bool LoadEquipment(std::ifstream& saveFile, Character& character,
	ItemType expectedType) {

	int hasEquipment = 0;

	if (!(saveFile >> hasEquipment) ||
		(hasEquipment != 0 && hasEquipment != 1)) {
		return false;
	}

	//An empty equipment slot needs no further data.
	if (hasEquipment == 0) {
		return true;
	}

	//Move to the next line before reading item text.
	saveFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string name;
	std::string description;

	int type = 0;
	int hpRestore = 0;
	int aseRestore = 0;
	int atkBonus = 0;
	int defBonus = 0;
	int price = 0;

	if (!std::getline(saveFile, name) ||
		!std::getline(saveFile, description) ||
		!(saveFile >> type
			>> hpRestore
			>> aseRestore
			>> atkBonus
			>> defBonus
			>> price)) {
		return false;
	}

	//Check that the item belongs in this equipment slot.
	if (name.empty() ||
		type != static_cast<int>(expectedType) ||
		hpRestore < 0 || aseRestore < 0 ||
		atkBonus < 0 || defBonus < 0 || price < 0) {
		return false;
	}

	Item loadedItem(
		name,
		description,
		static_cast<ItemType>(type),
		hpRestore,
		aseRestore,
		atkBonus,
		defBonus,
		price
	);
	//v.05 Remove the new line after the equipment properties.
	saveFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

	return character.EquipItem(loadedItem);
}

//==================================================
//			   Save System - Save Game
//==================================================

bool SaveSystem::SaveGame(const Game& game) {
	//Open the save file for writing. 
	std::ofstream saveFile("FirstFantasySave.txt"); 

	//Check that the file opened successfully. 
	if (!saveFile.is_open()) {
		std::cout << "\nERROR: Unable to create the save file.\n"; 
		return false; 
	}
	//Save file version identifier. 
	saveFile << "First_Fantasy_Save_V1\n"; 

	//v.04 Save the party's currency. 
	saveFile << game.mCowries << "\n"; 

	//v.04 Save the current location. 
	saveFile << game.mCurrentLocationId << "\n"; 

	//v.04 Save progress along the open road. 
	saveFile << game.mRoadProgress << "\n"; 

	//v.05 Save story progression flags.
	saveFile << game.mHasMetShaman << "\n";
	saveFile << game.mHasMetChief << "\n";

	saveFile << game.mHasFoundNecklace << "\n";
	saveFile << game.mHasReturnedNecklace << "\n";

	//v.05 Save Bloodroot Hollow progression.
	saveFile << game.mHasEnteredBloodrootHollow << "\n";
	saveFile << game.mHasExploredWitheredGrove << "\n";
	saveFile << game.mHasExploredBoneStrewnPath << "\n";
	saveFile << game.mHasExploredDesecratedShrine << "\n";
	saveFile << game.mHasExploredHeartoftheHollow << "\n";
	saveFile << game.mHasDefeatedBonsamElder << "\n";

	//v.05 Save ending progression.
	saveFile << game.mHasHeardChiefsConfession << "\n";
	saveFile << game.mHasHeardShamansWarning << "\n";

	//v.05 Save Ora'Kanu's current HP and Ase.
	saveFile << game.OraKanu.GetHP() << "\n";
	saveFile << game.OraKanu.GetAse() << "\n";

	//v.05 Save M'Batha's current HP and Ase.
	saveFile << game.Mbatha.GetHP() << "\n";
	saveFile << game.Mbatha.GetAse() << "\n";

	//v.05 Save the number of items in the party inventory.
	saveFile << game.mInventory.GetItemCount() << "\n";

	//v.05 Save each inventory item and its properties.
	for (int i = 0; i < game.mInventory.GetItemCount(); i++) {

		const Item* item = game.mInventory.GetItem(i);

		if (item == nullptr) {
			std::cout << "\nERROR: Unable to read inventory item.\n";
			return false;
		}

		saveFile << item->GetName() << "\n";
		saveFile << item->GetDescription() << "\n";
		saveFile << static_cast<int>(item->GetType()) << "\n";
		saveFile << item->GetHPRest() << "\n";
		saveFile << item->GetAseRest() << "\n";
		saveFile << item->GetAtkBonus() << "\n";
		saveFile << item->GetDefBonus() << "\n";
		saveFile << item->GetPrice() << "\n";
	}

	//v.05 Save Ora'Kanu's equipped weapon and armor.
	SaveEquipment(saveFile, game.OraKanu.GetEquippedWeapon());
	SaveEquipment(saveFile, game.OraKanu.GetEquippedArmor());

	//v.05 Save M'Batha's equipped weapon and armor.
	SaveEquipment(saveFile, game.Mbatha.GetEquippedWeapon());
	SaveEquipment(saveFile, game.Mbatha.GetEquippedArmor());

	//Additional game data will be written here. 
	//Check for writing errors before closing. 
	bool saveSuccessful = saveFile.good(); 

	saveFile.close(); 

	if (!saveSuccessful) {
		std::cout << "\nERROR: Failed to write save data.\n"; 
		return false; 
	}
	std::cout << "\nSave file created successfully.\n"; 
	return true;	
}
//==================================================
//			   Save System - Load Game
//==================================================
bool SaveSystem::LoadGame(Game& game) {

	//v.05 Work with a temporary game until loading succeeds.
	Game loadedGame = game; 

	//Open the save file for reading. 
	std::ifstream saveFile("FirstFantasySave.txt"); 

	//Check that the save file exists and opens. 
	if (!saveFile.is_open()) {
		std::cout << "\nERROR: No save file found.\n"; 
		return false; 
	}
	//Read the save file version. 
	std::string saveVersion; 
	std::getline(saveFile, saveVersion); 

	//Make sure the save file is compatible. 
	if (saveVersion != "First_Fantasy_Save_V1") {
		std::cout << "\nERROR: Invalid or incompatible save file.\n"; 
		return false; 
	}
	//v.04 Read the party's saved currency, location, and road progress. 
	int SavedCowries = 0; 
	int SavedLocationId = 0; 
	int SavedRoadProgress = 0; 

	if (!(saveFile >> SavedCowries >> SavedLocationId >> SavedRoadProgress)) {
		std::cout << "\nERROR: Save file contains missing or invalid data.\n"; 
		return false; 
	}

	//Validate the saved values before applying them. 
	if (SavedCowries < 0 || SavedLocationId < 1 || SavedRoadProgress < 0 || SavedRoadProgress > 4) {
		std::cout << "\nERROR: Save file contains invalid game progress."; 
		return false; 
	}

	//Restore the saved game values. 
	loadedGame.mCowries = SavedCowries; 
	loadedGame.mCurrentLocationId = SavedLocationId; 
	loadedGame.mRoadProgress = SavedRoadProgress; 

	//v.05 Read the saved story progression flags.
	int savedFlags[12] = {};

	for (int i = 0; i < 12; i++) {
		if (!(saveFile >> savedFlags[i])) {
			std::cout << "\nERROR: Missing story progression data.\n";
			return false;
		}

		//Story flags must be either 0 (false) or 1 (true).
		if (savedFlags[i] != 0 && savedFlags[i] != 1) {
			std::cout << "\nERROR: Invalid story progression data.\n";
			return false;
		}
	}

	//Restore the story progression flags.
	loadedGame.mHasMetShaman = savedFlags[0];
	loadedGame.mHasMetChief = savedFlags[1];

	loadedGame.mHasFoundNecklace = savedFlags[2];
	loadedGame.mHasReturnedNecklace = savedFlags[3];

	loadedGame.mHasEnteredBloodrootHollow = savedFlags[4];
	loadedGame.mHasExploredWitheredGrove = savedFlags[5];
	loadedGame.mHasExploredBoneStrewnPath = savedFlags[6];
	loadedGame.mHasExploredDesecratedShrine = savedFlags[7];
	loadedGame.mHasExploredHeartoftheHollow = savedFlags[8];
	loadedGame.mHasDefeatedBonsamElder = savedFlags[9];

	loadedGame.mHasHeardChiefsConfession = savedFlags[10];
	loadedGame.mHasHeardShamansWarning = savedFlags[11];


	//v.05 Read Ora'Kanu's saved HP and Ase.
	int savedOraHP = 0;
	int savedOraAse = 0;

	//v.05 Read M'Batha's saved HP and Ase.
	int savedMbathaHP = 0;
	int savedMbathaAse = 0;

	if (!(saveFile >> savedOraHP
		>> savedOraAse
		>> savedMbathaHP
		>> savedMbathaAse)) {

		std::cout << "\nERROR: Missing or invalid character data.\n";
		return false;
	}

	//Validate Ora'Kanu's saved stats.
	if (savedOraHP < 0 ||
		savedOraHP > game.OraKanu.GetMaxHP() ||
		savedOraAse < 0 ||
		savedOraAse > game.OraKanu.GetMaxAse()) {

		std::cout << "\nERROR: Invalid Ora'Kanu stats.\n";
		return false;
	}

	//Validate M'Batha's saved stats.
	if (savedMbathaHP < 0 ||
		savedMbathaHP > game.Mbatha.GetMaxHP() ||
		savedMbathaAse < 0 ||
		savedMbathaAse > game.Mbatha.GetMaxAse()) {

		std::cout << "\nERROR: Invalid M'Batha stats.\n";
		return false;
	}

	//Restore Ora'Kanu's HP and Ase.
	loadedGame.OraKanu.SetHP(savedOraHP);
	loadedGame.OraKanu.SetAse(savedOraAse);

	//Restore M'Batha's HP and Ase.
	loadedGame.Mbatha.SetHP(savedMbathaHP);
	loadedGame.Mbatha.SetAse(savedMbathaAse);

	//v.05 Read the number of saved inventory items.
	int savedItemCount = 0;

	if (!(saveFile >> savedItemCount) ||
		savedItemCount < 0 || savedItemCount > 1000) {

		std::cout << "\nERROR: Invalid inventory item count.\n";
		return false;
	}

	//Remove the newline left behind by reading the item count.
	saveFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//Build a temporary inventory before changing the game's inventory.
	Inventory loadedInventory;

	for (int i = 0; i < savedItemCount; i++) {

		std::string name;
		std::string description;

		int type = 0;
		int hpRestore = 0;
		int aseRestore = 0;
		int atkBonus = 0;
		int defBonus = 0;
		int price = 0;

		//Read the item's name and description.
		if (!std::getline(saveFile, name) ||
			!std::getline(saveFile, description)) {

			std::cout << "\nERROR: Missing inventory item text.\n";
			return false;
		}

		//Read the item's numerical properties.
		if (!(saveFile >> type
			>> hpRestore
			>> aseRestore
			>> atkBonus
			>> defBonus
			>> price)) {

			std::cout << "\nERROR: Missing inventory item properties.\n";
			return false;
		}

		//Validate the item type and numerical properties.
		if (name.empty() ||
			type < static_cast<int>(ItemType::Consumable) ||
			type > static_cast<int>(ItemType::KeyItem) ||
			hpRestore < 0 || aseRestore < 0 ||
			atkBonus < 0 || defBonus < 0 || price < 0) {

			std::cout << "\nERROR: Invalid inventory item data.\n";
			return false;
		}

		//Reconstruct the saved item.
		Item loadedItem(
			name,
			description,
			static_cast<ItemType>(type),
			hpRestore,
			aseRestore,
			atkBonus,
			defBonus,
			price
		);

		loadedInventory.AddItem(loadedItem);

		//Prepare to read the next item's name.
		saveFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	//Restore the party inventory.
	loadedGame.mInventory = loadedInventory;

	//v.05 Restore Ora'Kanu's equipped weapon and armor.
	if (!LoadEquipment(saveFile, game.OraKanu, ItemType::Weapon) ||
		!LoadEquipment(saveFile, game.OraKanu, ItemType::Armor)) {

		std::cout << "\nERROR: Invalid Ora'Kanu equipment data.\n";
		return false;
	}

	//v.05 Restore M'Batha's equipped weapon and armor.
	if (!LoadEquipment(saveFile, game.Mbatha, ItemType::Weapon) ||
		!LoadEquipment(saveFile, game.Mbatha, ItemType::Armor)) {

		std::cout << "\nERROR: Invalid M'Batha equipment data.\n";
		return false;
	}
	//v.05 Apply the loaded state only after all data is valid.
	game = loadedGame;

	//Additional game data will be read here. 
	std::cout << "\nSave file recognized successfully.\n"; 
	return true; 
}