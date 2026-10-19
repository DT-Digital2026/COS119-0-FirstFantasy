#pragma once

#include <string>
#include <vector>

#include "Enemy.h"

//Location class. 
class Location {
public: 
	//Default constructor. 
	Location(); 

	//Overloaded constructor. 
	Location(const int LocationID, const std::string& Name, const std::string& Description, int EncounterChance);

	//Getters.
	int GetLocationID() const; //v.02, Added the location ID so that we could add in an exploration system to the game. 

	std::string GetName() const; 

	const std::vector<int>& GetConnections() const; //v.02 Vector of connections allow the user to travel to areas connected to other areas. Made const to prevent other 
	//classes from changing the directions. 

	std::string GetDescription() const; 

	int GetEncounterChance() const; 

	void AddConnection(const int DestinationID); //v.02 This method will allow me to dictate "Crossroads Connects to Main Road" as well as other connections.

	//Encounter Pool. 
	void AddEnemy(const Enemy& enemy); 

	int GetEnemyCount() const; 

	//v.03 Vector to return enemies avialable at a given location. 
	const std::vector<Enemy>& GetEnemies() const; 

	//Location Display. 
	void DisplayLocation() const; 

private:
	int mID; //v.02 This variable will store a locations unique identifier. 

	std::vector<int> mDestinationID;//v.02 Vector added to store a locations available destinations.  

	std::string mName; 

	std::string mDescription; 

	int mEncounterChance; 

	std::vector<Enemy> mEnemies;
};