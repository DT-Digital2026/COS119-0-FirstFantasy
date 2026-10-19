#pragma once

#include "Location.h"
#include "Bestiary.h"

class LocationCatalog
{
public:
    // Default constructor.
    LocationCatalog();

    // Location Methods for gamespace leading up to the village. 
    Location CreateRoadtoVillage();
    Location CreateCrossroads();
    Location CreateRiverPath();
    Location CreateForestPath();

    //Location Methods for the village. 
    Location CreateVillageEntrance();
    Location CreateVillageCenter();
    Location CreateFishermansWharf(); 
    Location CreateItemShop(); 
    Location CreateChiefsHut(); 
    Location CreateShamansHut(); 

    //Location Methods for the wilderness. 
    Location CreateWilderness();
    Location CreateOvergrownTrail(); 
    Location CreateAbandonedCampsite(); 
    Location CreateRiverBankClearing(); 

    //Location Methods for Bloodroot Hollow.
    Location CreateBloodRootHollow();
    Location CreateTheWitheredGrove(); 
    Location CreateTheBoneStrewnPath(); 
    Location CreateTheDesecratedShrine(); 
    Location CreateHeartoftheHollow();


    // v.02 - Retrieves a location using its ID.
    // Used for tracking the player's current location
    // and displaying available travel destinations.
    Location GetLocationByID(int LocationID);

private:
    Bestiary mBestiary;
};