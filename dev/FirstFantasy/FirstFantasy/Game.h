
#pragma once

#include "Character.h"
#include "Bestiary.h"
#include "CombatSystem.h"
#include "LocationCatalog.h" // v.02 - Access to the location catalog.
#include "Inventory.h" //v.03 Adding inventory system to the game. 

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

    //v.03 Track  progress through the opening road sequence. 
    int mRoadProgress = 0; 

    //v.03 Variable and method to determine if the player has entered the shaman's hut and met the shaman for the first time. 
    bool mHasMetShaman = false; 

    void MeetShaman(); 

    //v.03 Variable and method to determine if the player has spoken to the shaman and then moved on to the cheif.
    bool mHasMetChief = false; 

    void MeetChief(); 

    // Initializes the game.
    void InitializeGame();

    ////v.03 Method to display the opening scene. 
    void DisplayOpeningScene(); 

    // Main gameplay loop.
    void GameLoop();

    //v.02 Handles player-controlled exploration.
    void ExploreLocation();

    //v.03 Advances the opening journey along the road. 
    void AdvanceRoadJourney(); 

    //v.02 Displays connected travel destinations.
    void DisplayTravelOptions(const Location& currentLocation);

    //v.03 Method to check for random enemy encounters. 
    void CheckRandomEncounter(); 

    //v.03 Shared party Inventory system. 
    Inventory mInventory; 

    //v.04 Expanding the inventory system to allow for item usage in and out of combat.
    void UseItemOutsideofCombat(); 

    //v.03 Ama's necklace.
    bool mHasFoundNecklace = false; 
    bool mHasReturnedNecklace = false; 

    void DiscoverNecklace(); 
    void ReturnNecklacetoChief(); 

    //v.04 Methods for exploring the endgame dungeon, Bloodroot Hollow.
    void EnterBloodrootHollow(); 
    void ExploreWitheredGrove(); 
    void ExploreBoneStrewnPath(); 
    void ExploreDesecratedShrine(); 
    void ExploreHeartoftheHollow();    
    void StartBonsamElderFight(); 

    //v.04 Story variables for Bloodroot Hollow. 
    bool mHasEnteredBloodrootHollow = false; 
    bool mHasExploredWitheredGrove = false; 
    bool mHasExploredBoneStrewnPath = false; 
    bool mHasExploredDesecratedShrine = false; 
    bool mHasExploredHeartoftheHollow = false; 
    bool mHasDefeatedBonsamElder = false; 

    //v.04 Game Ending. 
    bool mHasHeardChiefsConfession = false; 
    bool mHasHeardShamansWarning = false; 

    void ChiefsConfession(); 
    void ShamansWarning(); 

    // Combat system.
    CombatSystem mCombatSystem;
};