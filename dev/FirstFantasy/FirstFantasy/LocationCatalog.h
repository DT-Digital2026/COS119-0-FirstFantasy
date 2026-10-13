#pragma once

#include "Location.h"
#include "Bestiary.h"

class LocationCatalog {
public:
	//Default constructor. 
	LocationCatalog(); 

	//Location catalog methods. 
	Location CreateRoadtoVillage(); 

	Location CreateCrossroads(); //v.02 Location creation for the crossroads.

	Location CreateRiverPath(); //v.02 Location creation for the crossroads.

	Location CreateForestPath(); //v.02 Location creation for the crossroads.

	Location CreateVillage(); 

	Location CreateWilderness(); 

	Location CreateBloodRootHollow(); 

	Location GetLocationByID(int LocationID);//v.02 Got the location ID so that the game will track where the user is, and what options they have
	//to go to other locations.		

private:
	Bestiary mBestiary; 
};