#include <iostream> 
#include <limits>
#include <string>
#include <stdexcept>
#include <random>

#include "Game.h"
#include "AbilityCatalog.h"
#include "ItemCatalog.h"

//Starts a new game.
void Game::StartNewGame()
{
    InitializeGame();
    DisplayOpeningScene(); //v.03 Opening scene method.
    GameLoop();
}

//v.03 Kicks off the opening scene. 
void Game::DisplayOpeningScene() {
    std::cout << "\n============================================================\n" << std::endl;
    std::cout << "                FIRST FANTASY: THE DARK CONTINENT\n         " << std::endl;
    std::cout << "==============================================================\n" << std::endl;

    std::cout << "\nFor generations, the world has existed in a delicate balance.\n"; 
    std::cout << "\nBetween the seen and the unseen.\n"; 
    std::cout << "Between the living and the things that dwell beyond their understand.\n"; 
    std::cout << "\nEven the oldest balances can be broken.\n"; 

    std::cout << "\n------------------------------------------------------------------\n"; 

    std::cout << "\nFar beyond the great cities, where the wilderness swallows\n"; 
    std::cout << "the roads and the rivers run deep, a desperate prayer rises into the night.\n"; 

    std::cout << "\nA prayer for protection.\n"; 
    std::cout << "\nA prayer for those gone missing.\n"; 
    std::cout << "\nA prayer that does not go unanswered.\n"; 

    std::cout << "\n------------------------------------------------------------------\n";

    std::cout << "\nTwo warriors have heard the call.\n"; 
    std::cout << "\nOra'Kanu the voice of the storm.\n"; 
    std::cout << "\nM'Batha the father of Dhambe.\n"; 

    std::cout << "\nDrawn toward a remote fishing village, they travel West\n"; 
    std::cout << "\nbeneath the fading afternoon sun.\n"; 

    std::cout << "\nNeither knows what awaits them.\n"; 
    std::cout << "\nOnly that someone is calling for help.\n"; 
    std::cout << "\nAnd that something in the darkness has begun to stir.\n"; 

    std::cout << "\n------------------------------------------------------------------\n";

    std::cout << "\nPress Enter to begin your journey...\n"; 

    std::string input; 
    std::getline(std::cin, input); 
}

//Sets up everything needed for a new game.
void Game::InitializeGame()
{
    IsGameRunning = true;

    std::cout << "\n============================================================" << std::endl;
    std::cout << "                FIRST FANTASY: THE DARK CONTINENT          " << std::endl;
    std::cout << "============================================================" << std::endl;

    std::cout << "\nStarting a new game..." << std::endl;

    //Create the player characters.
    //Initialize Ora'Kanu
    OraKanu = Character("Ora'Kanu", "Voice of the Storm", 100, 100, 15, 10); 

    //Intialize M'Batha
    Mbatha = Character("M'Batha", "Father of Dhambe", 120, 60, 18, 15); 

    //Create the catalog of abilities. 
    AbilityCatalog abilityCatalog; 

    //Assign Ora'Kanu's starting abilities. 
    OraKanu.AddAbility(abilityCatalog.Raincall()); 
    
    //Assign M'Batha's starting abilities. 
    Mbatha.AddAbility(abilityCatalog.Jab());

    //Set player stats.
    OraKanu.DisplayStats(); 
    OraKanu.DisplayAbilities(); 

    std::cout << std::endl;

    Mbatha.DisplayStats(); 
    Mbatha.DisplayAbilities(); 

    //v.03 Clear inventory when starting a new game.
    mInventory = Inventory(); 

    //v.03 Temporary item for testing the inventory system.
   // Temporary item for testing the inventory system.
    Item healingHerb(
        "Healing Herb",
        "A medicinal herb that restores 25 HP.",
        ItemType::Consumable,
        25,  // HP restored
        0,   // Ase restored
        0,   // Attack bonus
        0    // Defense bonus
    );
    mInventory.AddItem(healingHerb); 
    
    //Set the initial story state.
    mCurrentLocationId = 1; //v.02 Sets the starting location to 1-RoadtoVillage.

    //v.03 Will ensure that every new game begins at the first stage, even if the same Game object is used.
    mRoadProgress = 0; 

    //v.03 Will ensure that every new game begins with the Met Shaman flag set to false. 
    mHasMetShaman = false;
    //v.03 Will ensure that every new game begins with the Met Cheif flag is set to false.
    mHasMetChief = false; 
    //v.03 Sets necklace to being found to false upon a new game. 
    mHasFoundNecklace = false;  
    //v.03 Sets necklace return to false.
    mHasReturnedNecklace = false; 
    //v.04 Resetting the flag for Bloodroot Hollow. 
    mHasEnteredBloodrootHollow = false; 
}

//============================================================
//   v.03 Story Element for Shaman's Hut    
//============================================================

void Game::MeetShaman() {
    //Prevent the introduction from repeating.
    if (mHasMetShaman) {
        return; 
    }
    std::cout << "\n====================================================================\n"; 
    std::cout << "                          The Shaman's Call                             "; 
    std::cout << "\n=====================================================================\n"; 

    std::cout << "\nThe scent of burning herbs fills the small hut.\n"; 
    std::cout << "\nAn elderly shaman sits beside a flickering fire,\n"; 
    std::cout << "\nhis weathered handsresting upon a wooden staff.\n"; 

    std::cout << "\nAs Ora'Kanu and M'Batha enter, the shaman slowly rises.\n"; 

    std::cout << "\nShaman: \"Your have come...you have heard my prayers.\"\n"; 

    std::cout << "\nOra'Kanu: \"Your voice has carried far beyond this village.\n"; 
    std::cout << "Tell us what troubles your people.\"\n"; 

    std::cout << "\nThe Shaman lowers his gaze.\n"; 

    std::cout << "\nShaman: \"Our children have began to disappear.\n"; 
    std::cout << "Fishermen leave for the river and never return.\n"; 
    std::cout << "The people grow frightened, and I fear their\n"; 
    std::cout << "suffering has only just begun.\"\n";

    std::cout << "\nM'Batha: \"Have your hunters searched the wilderness?\"\n";

    std::cout << "\nShaman: \"They have found nothing, but there are places\n"; 
    std::cout << "beyond this village where even our bravest hunters\n"; 
    std::cout << "dare not travel.\"\n"; 

    std::cout << "\nThe shaman glances at the doorway.\n"; 

    std::cout << "\nShaman: \"You must speak with our cheif.\n"; 
    std::cout << "he knows more of these disappearances than I can\n"; 
    std::cout << "explain here. Tell him I sent you.\"\n"; 

    std::cout << "\nOra'Kanu nods.\n"; 

    std::cout << "\nOra'Kanu: \"Then we will speak with him.\"\n";

    std::cout << "=========================================================="; 
    std::cout << "\n Press ENTER to continue.\n"; 

    std::string input; 
    std::getline(std::cin, input); 

    //Record that the introduction has occured. 
    mHasMetShaman = true; 
}

//============================================================
//   v.03 Story Element for Meeting the Village Cheif   
//============================================================
void Game::MeetChief() {
    if (mHasMetChief) {
        if (mHasFoundNecklace && !mHasReturnedNecklace) {
            ReturnNecklacetoChief(); 
        }
        return; 
    }
    std::cout << "\n=====================================================================\n";
    std::cout << "                          The Chief's Request                            ";
    std::cout << "\n=====================================================================\n";

    std::cout << "\nThe village cheif sits before a wooden table,\n"; 
    std::cout << "studying a collection of markings carved into its surface.\n"; 

    std::cout << "\nChief: \"Strangers, what business brings you to my village?\"\n"; 

    std::cout << "\nOra'Kanu: \"We answered the prayers of your shaman.\n"; 
    std::cout << "He told us your people have gone missing.\"\n";

    std::cout << "\nThe chief's expression grows troubled.\n"; 

    std::cout << "\nChief: \"Then you know why we need help.\n";  
    std::cout << "Children have vanished, and fishermen have failed to\n"; 
    std::cout << "return from the river.\"\n"; 

    std::cout << "\nM'Batha: \"Where were they last seen?\"\n"; 

    std::cout << "\nCheif: \"Near the wilderness beyond our village.\n"; 
    std::cout << "Our hunters searched the nearby trails, but found nothing.\"\n"; 

    std::cout << "\nThe chief pauses before continuing.\n"; 

    std::cout << "\nChief: \"I ask that you investigate those woods.\n"; 
    std::cout << "Search for anything that might explain these disappearances.\n"; 
    std::cout << "If you discover something, return to me.\"\n"; 

    std::cout << "\nOra'Kanu: \"We will search the wilderness.\"\n"; 

    std::cout << "\nChief: \"May the spirits guide your steps.\"\n"; 

    std::cout << "==========================================================";
    std::cout << "\n Press ENTER to continue.\n";

    std::string input;
    std::getline(std::cin, input);

    //Record that the introduction has occured. 
    mHasMetChief = true;
}
//============================================================
//   v.03 Story Element for Ama's Necklace
//============================================================
void Game::DiscoverNecklace() {
    if (!mHasMetChief || mHasFoundNecklace) {
        return; 
    }
    std::cout << "\n============================================================" << std::endl;
    std::cout << "                     A Child's Necklace                       " << std::endl;
    std::cout << "==============================================================" << std::endl;

    std::cout << "\nThe river moves quietly through the clearing.\n"; 
    std::cout << "As the heroes approach the water, something catches\n"; 
    std::cout << "Ora'Kanu's attention just beneath the water near the shore.\n"; 

    std::cout << "\nOra'Kanu: \"M'Batha, come and look at this.\"\n"; 

    std::cout << "\nM'Batha kneels beside the riverbank and carefully\n"; 
    std::cout << "pulls a small necklace from the mud.\n"; 

    std::cout << "\nM'Batha: \"A child's necklace...\"\n";

    std::cout << "\nOra'Kanu: \"Perhaps it belongs to one of the missing.\n";
    std::cout << "We should return to the chief.\"\n";

    //Create the actual quest item.
    Item necklace(
        "Ama's Necklace",
        "A small, mud-stained necklace discovered near the riverbank.",
        ItemType::KeyItem,
        0, 0, 0, 0
    );

    //Add the necklace to the party inventory.
    mInventory.AddItem(necklace);

    //Prevent the discovery from happening again.
    mHasFoundNecklace = true;

    std::cout << "\n[QUEST ITEM ACQUIRED: Ama's Necklace]\n";

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

//============================================================
//   v.03 Story Element for Ama's Necklace
//============================================================
void Game::ReturnNecklacetoChief() {
    if (!mHasFoundNecklace || mHasReturnedNecklace) {
        return; 
    }
    std::cout << "\n============================================================" << std::endl;
    std::cout << "                    The Chief's Sorrow                        " << std::endl;
    std::cout << "==============================================================" << std::endl;

    std::cout << "\nThe chief looks up as Ora'Kanu and M'Batha enter.\n"; 

    std::cout << "\nChief: \"You have returned. What have you discovered?\"\n"; 

    std::cout << "\nM'Batha places the small necklace upon the table.\n"; 

    std::cout << "\nM'Batha: \"We found this near the River Bank.\"\n"; 

    std::cout << "\nThe chief reaches for the necklace, but his hand\n"; 
    std::cout << "stops just short of touching it.\n"; 

    std::cout << "\nChief: \"This belonged to Ama...\n"; 

    std::cout << "\nOra'Kanu: \"You recognize it?\"\n"; 

    std::cout << "\nChief: \"Her mother gave it to her. She never took it off.\"\n"; 

    std::cout << "\nThe chief lowers his head in silence.\n"; 

    std::cout << "\nChief: \"There is a place beyond the river.\n"; 
    std::cout << "Our people have avoided it for generations.\n"; 
    std::cout << "We call it Bloodroot Hollow. It is dangerous, filled with\n";
    std::cout << "darkness. Creatures that live on blood...the Bonsam.\"\n"; 

    std::cout << "\nOra'Kanu: \"Leave it to us, we will investigate this Bloodroot Hollow.\"\n"; 

    std::cout << "\n[QUEST UPDATED: Investigate Bloodroot Hollow.]\n";

    //v.04 Locate Ama's necklace in the party inventory. 
    int necklaceIndex = mInventory.FindItemByName("Ama's Necklace"); 

    if (necklaceIndex == -1) {
        std::cout << "\nAma's Necklace is missing from the inventory.\n"; 
        return; 
    }

    //v.04 Remove the necklace after returning it to the chief.
    mInventory.RemoveItem(necklaceIndex); 

    std::cout << "\n[QUEST ITEM REMOVED: Ama's Necklace]\n"; 

    //v.04 Create the quest rewards. 
    ItemCatalog itemCatalog; 

    Item shamanBracers = itemCatalog.CreateShamanBracers(); 
    Item reinforcedWraps = itemCatalog.CreateReinforcedWraps(); 

    //v.04 Add both to the parties inventory. 
    mInventory.AddItem(shamanBracers); 
    mInventory.AddItem(reinforcedWraps); 

    std::cout << "\nThe chief opens a wooden chest beside his table.\n"; 
    std::cout << "Chief: \"These belonged to warriors who once protected our village.\n"; 
    std::cout << "Take them. You may need their strength in the days ahead.\"\n"; 

    std::cout << "\n[QUEST REWARD: Shaman Bracers]\n";
    std::cout << "[QUEST REWARD: Reinforced Wraps]\n";

    //v.04 Prevents the conversation from repeating. 
    mHasReturnedNecklace = true; 

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}


//Temporary game loop. This will be expanded as the game is developed.
void Game::GameLoop()
{
    while (IsGameRunning)
    {
        std::string input;
        int choice = -1;

        std::cout << "\n============================================================" << std::endl;
        std::cout << "                         GAME                                 " << std::endl;
        std::cout << "==============================================================" << std::endl;

        std::cout << "1. Continue" << std::endl;
        std::cout << "2. Return to Main Menu" << std::endl;

        std::cout << "Enter your choice: ";

        if (!std::getline(std::cin, input))
        {
            IsGameRunning = false;
            break;
        }

        // Validate the player's input.
        try
        {
            size_t position = 0;
            choice = std::stoi(input, &position);

            // Reject inputs such as "1abc" or "2.5".
            if (position != input.length())
            {
                std::cout << "Invalid input. Please enter 1 or 2.\n";
                continue;
            }
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Number is out of range. Please enter 1 or 2.\n";
            continue;
        }

        if (choice == 1)
        {
            if (mRoadProgress < 4)
            {
                AdvanceRoadJourney();
            }
            else
            {
                ExploreLocation();
            }
        }
        else if (choice == 2)
        {
            // Return to the main menu.
            IsGameRunning = false;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }
}

//================================================================================
//v.04             Story Element - Enter Bloodroot Hollow           
//================================================================================
void Game::EnterBloodrootHollow() {
    //Prevent the scene from repeating. 
    if (mHasEnteredBloodrootHollow) {
        return; 
    }
    std::cout << "\n============================================================\n";
    std::cout << "                  BLOODROOT HOLLOW\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe forest grows unnaturally quiet as the heroes\n";
    std::cout << "leave the familiar wilderness behind.\n";

    std::cout << "\nThe trees stand close together, their branches\n";
    std::cout << "intertwining overhead and swallowing the afternoon light.\n";

    std::cout << "\nThick roots, stained a deep crimson, twist across\n";
    std::cout << "the ground like veins beneath the forest floor.\n";

    std::cout << "\nM'Batha: \"Something is wrong with this place.\"\n";

    std::cout << "\nOra'Kanu: \"The forest is old. Older than the village.\"\n";

    std::cout << "\nA faint rattling sound draws their attention.\n";

    std::cout << "\nSmall wooden charms hang from the surrounding trees,\n";
    std::cout << "swaying gently despite the absence of wind.\n";

    std::cout << "\nM'Batha approaches one of the trees.\n";

    std::cout << "\nM'Batha: \"These markings... I've seen some of them before.\"\n";

    std::cout << "\nOra'Kanu: \"Where?\"\n";

    std::cout << "\nM'Batha: \"Protective symbols. Used to mark sacred ground.\n";
    std::cout << "But these others... I don't recognize them.\"\n";

    std::cout << "\nBeyond the hanging charms, a weathered warning\n";
    std::cout << "has been carved deep into the bark of an ancient tree.\n";

    std::cout << "\nThe words have nearly disappeared beneath the moss.\n";

    std::cout << "\nOra'Kanu brushes the moss away.\n";

    std::cout << "\nOra'Kanu: \"A boundary.\"\n";

    std::cout << "\nM'Batha: \"A warning?\"\n";

    std::cout << "\nOra'Kanu: \"Perhaps. But warnings are meant to keep\n";
    std::cout << "something on one side of a line.\"\n";

    std::cout << "\nHe looks toward the darkness beyond the trees.\n";

    std::cout << "\nOra'Kanu: \"The question is which side they feared.\"\n";

    std::cout << "\nFor a moment, neither warrior speaks.\n";

    std::cout << "\nThen, somewhere deeper in the hollow,\n";
    std::cout << "something answers with a low, distant cry.\n";

    std::cout << "\n[LORE DISCOVERED: The Boundary of Bloodroot Hollow]\n";

    // Record that the scene has played.
    mHasEnteredBloodrootHollow = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}


//=========================================
//    v.02 DisplayTravelOptions
//=========================================

//Displays all connected locations the player can travel to. 
void Game::DisplayTravelOptions(const Location& currentLocation) {
    //Retrieve the current locations connections. 
    const std::vector<int>& connections = currentLocation.GetConnections(); 

    int menuNumber = 1; 

    std::cout << "\nWhere would you like to travel?\n"; 

    //Loop through all connected locations. 
    for (int destinationId : connections) {
        //Retrieve the destination location. 
        Location destination = mLocationCatalog.GetLocationByID(destinationId); 

        //v.02 Display the destination number and name.
        std::cout << menuNumber << ". "
            << destination.GetName() << std::endl;

        menuNumber++; 
    }
    std::cout << "9. View Inventory" << std::endl;
    std::cout << "0. Exit Exploration" << std::endl;
}

//=========================================
//    v.02 Explore Location
//=========================================
//v.02 - Handles player-controlled exploration.
void Game::ExploreLocation()
{
    while (IsGameRunning)
    {
        //Retrieve the player's current location.
        Location currentLocation = mLocationCatalog.GetLocationByID(mCurrentLocationId);

        //Display the current location's name and description.
        currentLocation.DisplayLocation();

        //Display available travel destinations.
        DisplayTravelOptions(currentLocation);

        //Retrieve connected destination IDs.
        const std::vector<int>& connections = currentLocation.GetConnections();

        std::string input;
        int choice = -1;

        std::cout << "\nEnter your choice: ";

        //Read the entire line of user input.
        if (!std::getline(std::cin, input))
        {
            //Handle closed or failed input.
            IsGameRunning = false;
            break;
        }

        //Convert input into an integer.
        try
        {
            size_t position = 0;

            choice = std::stoi(input, &position);

            //Reject input containing extra characters.
            if (position != input.length())
            {
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Number is too large. Please try again.\n";
            continue;
        }

        //v.03 View the party inventory. 
        if (choice == 9) {
            mInventory.DisplayInventory(); 

            std::cout << "\nPress ENTER to return to exploration..."; 
            std::string pause; 
            std::getline(std::cin, pause); 

            continue; 
        }

        //Exit exploration.
      // Exit exploration and return to the main menu.
        if (choice == 0)
        {
            std::cout << "\nReturning to Main Menu...\n";

            IsGameRunning = false;
            break;
        }

        //Validate the selected destination.
        if (choice >= 1 && choice <= static_cast<int>(connections.size()))
        {
            //Convert menu selection to vector index.
            int index = choice - 1;

            //Retrieve the selected destination ID.
            int destinationID = connections[index];

            //v.03 The chief will only recieve visitors sent by the shaman. 
            if (destinationID == 11 && !mHasMetShaman) {
                std::cout << "\nTwo village guards stand outside the chief's hut.\n"; 
                std::cout << "\nGuard: \"The chief is not recieving visitors.\"\n"; 
                std::cout << "\nGuard: \"If you seek an audience, speak with the shaman first.\"\n"; 

                continue; 
            }

            //Update the player's current location.
            mCurrentLocationId = destinationID;

            //v.03 Trigger the shaman's introduction when entering his hut. 
            if (mCurrentLocationId == 12) {
                MeetShaman(); 
            }
            //v.03 Trigger the chief's introduction when entering his hut.
            if (mCurrentLocationId == 11)
            {
                MeetChief();
            }

            //v.03 Discover the necklace after accepting the chief's request. 
            if (mCurrentLocationId == 15 && mHasMetChief && !mHasFoundNecklace) {
                DiscoverNecklace(); 
            }

            //v.04 Trigger Bloodroot Hollow's introduction.
            if (mCurrentLocationId == 7 && !mHasEnteredBloodrootHollow) {
                EnterBloodrootHollow();
            }

            //Checks for random encounters.
            CheckRandomEncounter(); 
        }
        else
        {
            std::cout << "Invalid destination. Please try again.\n";
        }
    }
 }
//=====================================
//      v.03 Advance Road Journey
//=====================================
//Handles scripted progression along the 
//road before normal exploration begins. 

void Game::AdvanceRoadJourney() {
    switch (mRoadProgress) {
    case 0:
        std::cout << "\nOra'Kanu and M'Batha travel along the western road.\n"; 
        std::cout << "\nTheir destination is a remote fishing village beyond the wilderness.\n"; 
        std::cout << "\nThe afternoon sun hangs above the trees.\n"; 
        mRoadProgress++; 
        break; 

    case 1: {
        std::cout << "\nThe road narrows as thick vegetation crosses the path.\n";
        std::cout << "Something stirs in the bushes nearby.\n";

        //v.03. Scripted first encounter. 
        Bestiary bestiary;

        Enemy snake = bestiary.CreateVenomousSnake();

        std::cout << "\nA Venomous Snake emerges from the bushes!\n";

        CombatResult result = mCombatSystem.StartCombat(
            OraKanu,
            Mbatha,
            snake
        );

        if (result == CombatResult::Victory)
        {
            std::cout << "\nThe snake collapses to the ground.\n";
            std::cout << "The heroes have survived their first encounter.\n";

            mRoadProgress++;
        }
        else if (result == CombatResult::Defeat)
        {
            std::cout << "\nThe heroes fall along the roadside...\n";
            std::cout << "Their journey ends before it can truly begin.\n";

            IsGameRunning = false;
        }
    }
        break;

    case 2: 
        std::cout << "\nThe road grows quiet once more.\n"; 
        std::cout << "\nOra'Kanu and M'Batha continue toward the distant village.\n"; 

        mRoadProgress++; 
        break; 

    case 3: 
        std::cout << "\nThe road opens beneath an ancient tree.\n"; 
        std::cout << "\nPaths branch off in a couple of directions.\n"; 
        std::cout << "\nThe heroes have reached the Crossroads.\n"; 

        mCurrentLocationId = 2; 
        mRoadProgress++; 
        break; 

    default:
        break;
    }
}

//=====================================
//   v.03 Random Encounter System 
//=====================================

void Game::CheckRandomEncounter() {
    //Retrieve players current location. 
    Location currentLocation = mLocationCatalog.GetLocationByID(mCurrentLocationId);

    //Retrieve the encounter settings. 
    int encounterChance = currentLocation.GetEncounterChance();

    const std::vector<Enemy>& enemies = currentLocation.GetEnemies();

    //Safe locations or emtpy rooms cannot trigger combat. 
    if (encounterChance <= 0 || enemies.empty()) {
        return; 
    }
    //Create  a random number generator. 
    static std::mt19937 generator(std::random_device{}()); 

    //Roll a number between 1 and 100. 
    std::uniform_int_distribution<int> encounterRoll(1, 100);

    int roll = encounterRoll(generator); 

    //No encounter occured. 
    if (roll > encounterChance) {
        return; 
    }
    //Randomly select an enemy from this locations pool. 
    std::uniform_int_distribution<int> enemyRoll(0, static_cast<int>(enemies.size()) - 1); 

    int enemyIndex = enemyRoll(generator); 

    //Create a fresh copy so combat does not modify the encounter pool. 
    Enemy selectedEnemy = enemies[enemyIndex]; 

    std::cout << "\nAn enemy approaches1\n"; 

    //Start combat using the existing combat system. 
    CombatResult result = mCombatSystem.StartCombat(OraKanu, Mbatha, selectedEnemy); 

    //Handle defeat. 
    if (result == CombatResult::Defeat) {
        std::cout << "\nYour journey has come to an end.\n"; 
        IsGameRunning = false; 
    }
}
