#pragma once

#include "Character.h"
#include "Bestiary.h"
#include "CombatSystem.h"
#include "LocationCatalog.h" //v.02 added location catalog header so we can access those methods.

//Creation of the game class. 
class Game {

public:
	//Starts new game, will take no parameters and will return no values.
	void StartNewGame(); 

private: 
	//Bool variable to dictate whether the game is running or not. 
	bool IsGameRunning; 

	//Character Objects for Ora and Mbatha.
	Character OraKanu; 

	Character Mbatha; 

	//v.02 LocationCatalog declaration that will give access to our locations. 
	LocationCatalog mLocationCatalog; 

	//v.02 mCurrentLocationId will store the players current location, but the default location is set to 1. 
	int mCurrentLocationId; 

	//Will initialize the game. Will take no parameters and will return no values. 
	void InitializeGame(); 

	//Game loop definition.
	void GameLoop(); 

	//v.02 Explore location will handle player controlled exploration.
	void ExploreLocation(); 


	//v.02 DisplayTravelOptions constant method to a location object. Will display connected locations. 
	void DisplayTravelOptions(const Location& currentLocation); 

	//Combat system. 
	CombatSystem mCombatSystem;
};
