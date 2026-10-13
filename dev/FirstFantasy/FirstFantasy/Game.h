
#pragma once

#include "Character.h"
#include "Bestiary.h"
#include "CombatSystem.h"
#include "LocationCatalog.h" // v.02 - Access to the location catalog.

// Creation of the game class.
class Game
{
public:
    // Starts a new game.
    void StartNewGame();

private:
    // Tracks whether the game is running.
    bool IsGameRunning;

    // Player characters.
    Character OraKanu;
    Character Mbatha;

    // v.02 - Location system.
    LocationCatalog mLocationCatalog;

    // Stores the player's current location ID.
    int mCurrentLocationId;

    // Initializes the game.
    void InitializeGame();

    // Main gameplay loop.
    void GameLoop();

    // v.02 - Handles player-controlled exploration.
    void ExploreLocation();

    // v.02 - Displays connected travel destinations.
    void DisplayTravelOptions(const Location& currentLocation);

    // Combat system.
    CombatSystem mCombatSystem;
};