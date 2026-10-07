#include <iostream>

#include "Location.h"

//Default Constructor.
Location::Location() {
	mName = "";
	mDescription = "";
	mEncounterChance = 0;
}

//Overloaded Constructor.
Location::Location(const std::string& Name, const std::string& Description, int EncounterChance) {
	mName = Name;
	mDescription = Description;
	mEncounterChance = EncounterChance;
}

//Gets the location name.
std::string Location::GetName() const {
	return mName;
}

//Gets the location description.
std::string Location::GetDescription() const {
	return mDescription;
}

//Gets the encounter chance for the location.
int Location::GetEncounterChance() const {
	return mEncounterChance;
}

//Adds enemies to the location encounter pool.
void Location::AddEnemy(const Enemy& enemy) {
	mEnemies.push_back(enemy);
}

//Gets the number of enemies in the location's encounter pool.
int Location::GetEnemyCount() const {
	return static_cast<int>(mEnemies.size());
}

//Displays the location information.
void Location::DisplayLocation() const {
	std::cout << "\n=-=-= " << mName << " =-=-=\n";
	std::cout << mDescription << std::endl;
}