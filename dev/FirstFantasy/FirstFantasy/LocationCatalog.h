#pragma once

#include "Location.h"
#include "Bestiary.h"

class LocationCatalog
{
public:
    // Default constructor.
    LocationCatalog();

    // Location creation methods.
    Location CreateRoadtoVillage();
    Location CreateCrossroads();
    Location CreateRiverPath();
    Location CreateForestPath();
    Location CreateVillage();
    Location CreateWilderness();
    Location CreateBloodRootHollow();

    // v.02 - Retrieves a location using its ID.
    // Used for tracking the player's current location
    // and displaying available travel destinations.
    Location GetLocationByID(int LocationID);

private:
    Bestiary mBestiary;
};