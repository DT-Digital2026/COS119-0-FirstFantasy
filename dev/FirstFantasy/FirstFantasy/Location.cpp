#include <iostream>

#include "Location.h"

//Default Constructor.
Location::Location() {
	mID = 0; //v.02 Added location ID to default constructor. 
	mName = "";
	mDescription = "";
	mEncounterChance = 0;
}

//Overloaded Constructor.
Location::Location(const int LocationID, const std::string& Name, const std::string& Description, int EncounterChance) {
	mID = LocationID; //v.02 Added LocationId parameters to overloaded constructor. 
	mName = Name;
	mDescription = Description;
	mEncounterChance = EncounterChance;
}

//v.02 GetLocationID method. 
int Location::GetLocationID() const {
	return mID; 
}

//v.02 Vector to store the locations and their connections. 
const std::vector<int>& Location::GetConnections() const {
	return mDestinationID; 
}

//v.02 Connection method.
void Location::AddConnection(const int DestinationID) {
	mDestinationID.push_back(DestinationID); 
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

//v.03 Returns location encounter pool. 
const std::vector<Enemy>& Location::GetEnemies() const {
	return mEnemies; 
}

//Displays the location information.
void Location::DisplayLocation() const {
	std::cout << "\n=-=-= " << mName << " =-=-=\n";
	std::cout << mDescription << std::endl;
}