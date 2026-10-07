#pragma once

#include "Location.h"
#include "Bestiary.h"

class LocationCatalog {
public:
	//Default constructor. 
	LocationCatalog(); 

	//Location catalog methods. 
	Location CreateRoadtoVillage(); 

	Location CreateVillage(); 

	Location CreateWilderness(); 

	Location CreateBloodRootHollow(); 

private:
	Bestiary mBestiary; 
};