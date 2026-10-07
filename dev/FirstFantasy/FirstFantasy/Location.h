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
	Location(const std::string& Name, const std::string& Description, int EncounterChance);

	//Getters.
	std::string GetName() const; 

	std::string GetDescription() const; 

	int GetEncounterChance() const; 

	//Encounter Pool. 
	void AddEnemy(const Enemy& enemy); 

	int GetEnemyCount() const; 

	//Location Display. 
	void DisplayLocation() const; 

private:
	std::string mName; 

	std::string mDescription; 

	int mEncounterChance; 

	std::vector<Enemy> mEnemies;
};