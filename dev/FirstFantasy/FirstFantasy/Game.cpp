#include <iostream> 
#include <limits>
#include <string>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <vector>

#include "SaveSystem.h"
#include "Game.h"
#include "AbilityCatalog.h"
#include "ItemCatalog.h"
#include "ItemManager.h"
#include "Menu.h"

//Starts a new game.
void Game::StartNewGame() {
    InitializeGame();
    DisplayOpeningScene(); //v.03 Opening scene method.
    GameLoop();
}
//==================================================
//          v.05 - Continue Saved Game
//==================================================
void Game::ContinueSavedGame() {

    //Initialize characters, abilities, and game systems.
    InitializeGame();

    //Attempt to load saved progress.
    if (!SaveSystem::LoadGame(*this)) {
        std::cout << "\nUnable to load saved game.\n";
        return;
    }

    //Resume gameplay without replaying the opening scene.
    IsGameRunning = true;
    GameLoop();
}
//Sets up everything needed for a new game.
void Game::InitializeGame()
{
    IsGameRunning = true;

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================" << std::endl;

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                FIRST FANTASY: THE DARK CONTINENT          " << std::endl;

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================" << std::endl;

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nStarting a new game..." << std::endl;

    //Create the player characters.
    //Initialize Ora'Kanu
    Menu::SetTextColor(Menu::IVORY);
    OraKanu = Character("Ora'Kanu", "Voice of the Storm", 100, 100, 15, 10);

    //Intialize M'Batha
    Menu::SetTextColor(Menu::IVORY);
    Mbatha = Character("M'Batha", "Father of Dhambe", 120, 60, 18, 15);

    //Create the catalog of abilities. 
    AbilityCatalog abilityCatalog;

    //Assign Ora'Kanu's starting abilities. 
    OraKanu.AddAbility(abilityCatalog.Raincall());
    OraKanu.AddAbility(abilityCatalog.LightningStrike());
    OraKanu.AddAbility(abilityCatalog.HealingRain());
    OraKanu.AddAbility(abilityCatalog.Tempest());

    //Assign M'Batha's starting abilities. 
    Mbatha.AddAbility(abilityCatalog.Jab());
    Mbatha.AddAbility(abilityCatalog.SpearStrike());
    Mbatha.AddAbility(abilityCatalog.StunningBlow());
    Mbatha.AddAbility(abilityCatalog.ChampionCombo());

    //Set player stats.
    OraKanu.DisplayStats();
    OraKanu.DisplayAbilities();

    std::cout << std::endl;

    Mbatha.DisplayStats();
    Mbatha.DisplayAbilities();

    //v.03 Clear inventory when starting a new game.
    mInventory = Inventory();

    //v.04 Starting party currency. 
    mCowries = 100;

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
    //v.04 Reset flag for Withered Grove. 
    mHasExploredWitheredGrove = false;
    //v.04 Reset flag for Bone Strewn Path. 
    mHasExploredBoneStrewnPath = false;
    //v.04 Reset flag for Desecrated Shrine. 
    mHasExploredDesecratedShrine = false;
    //v.04 Reset flag for Heart of the Hollow. 
    mHasExploredHeartoftheHollow = false;
    //v.04 Reset flag for Bonsam Elder. 
    mHasDefeatedBonsamElder = false;

    //v.04 Game ending. 
    mHasHeardChiefsConfession = false;
    mHasHeardShamansWarning = false;
}
//v.03 Kicks off the opening scene. 
void Game::DisplayOpeningScene() {
    //Gives the opening cinematic a clear screen. 
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n" << std::endl;

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                FIRST FANTASY: THE DARK CONTINENT\n         " << std::endl;

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "==============================================================\n" << std::endl;

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nFor generations, the world has existed in a delicate balance.\n"; 
    std::cout << "\nBetween the seen and the unseen.\n"; 
    std::cout << "Between the living and the things that dwell beyond their understand.\n"; 
    std::cout << "\nEven the oldest balances can be broken.\n"; 

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n------------------------------------------------------------------\n"; 

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nFar beyond the great cities, where the wilderness swallows\n"; 
    std::cout << "the roads and the rivers run deep, a desperate prayer rises into the night.\n"; 

    std::cout << "\nA prayer for protection.\n"; 
    std::cout << "\nA prayer for those gone missing.\n"; 
    std::cout << "\nA prayer that does not go unanswered.\n"; 

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n------------------------------------------------------------------\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nTwo warriors have heard the call.\n"; 
    std::cout << "\nOra'Kanu the voice of the storm.\n"; 
    std::cout << "\nM'Batha the father of Dhambe.\n"; 

    std::cout << "\nDrawn toward a remote fishing village, they travel West\n"; 
    std::cout << "\nbeneath the fading afternoon sun.\n"; 

    std::cout << "\nNeither knows what awaits them.\n"; 
    std::cout << "\nOnly that someone is calling for help.\n"; 
    std::cout << "\nAnd that something in the darkness has begun to stir.\n"; 

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n------------------------------------------------------------------\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "\nPress Enter to begin your journey...\n"; 

    std::string input; 
    std::getline(std::cin, input); 
}
void Game::GameLoop() {
    while (IsGameRunning) {
        // Clear exploration before displaying the Chief's Sorrow.
        Menu::ClearScreen();

        std::string input;
        int choice = -1;

        // Display the in-game menu.
        Menu::SetTextColor(Menu::GREEN);
        std::cout << "\n============================================================\n";

        Menu::SetTextColor(Menu::GOLD);
        std::cout << "                    THE DARK CONTINENT\n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "============================================================\n";

        Menu::SetTextColor(Menu::IVORY);

        std::cout << "\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "  1. ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "Continue Adventure\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "  2. ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "Save Game\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "  3. ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "Return to Main Menu\n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "\n------------------------------------------------------------\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nEnter your choice: ";

        if (!std::getline(std::cin, input)) {
            IsGameRunning = false;
            break;
        }

        // Validate the player's input.
        try {
            size_t position = 0;
            choice = std::stoi(input, &position);

            // Reject inputs such as "1abc" or "2.5".
            if (position != input.length()) {
                std::cout << "Invalid input. Please enter 1 or 2.\n";
                continue;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }
        catch (const std::out_of_range&) {
            std::cout << "Number is out of range. Please enter 1 or 2.\n";
            continue;
        }
        if (choice == 1) {
            while (mRoadProgress < 4 && IsGameRunning) {
                AdvanceRoadJourney();

                if (IsGameRunning) {
                    Menu::PauseForEnter();
                }
            }

            if (IsGameRunning) {
                ExploreLocation();
            }
        }
        else if (choice == 2) {
            //v.05 Save the current game.
            SaveSystem::SaveGame(*this);

            Menu::PauseForEnter();

        }
        else if (choice == 3) {
            // Return to the main menu.
            IsGameRunning = false;
        }
        else {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
}
//=====================================
//      v.03 Advance Road Journey
//=====================================
//Handles scripted progression along the 
//road before normal exploration begins. 

void Game::AdvanceRoadJourney() {

    // Give each stage of the road journey a clean screen.
    Menu::ClearScreen();

    switch (mRoadProgress) {
    case 0:
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nOra'Kanu and M'Batha travel along the western road.\n";
        std::cout << "\nTheir destination is a remote fishing village beyond the wilderness.\n";
        std::cout << "\nThe afternoon sun hangs above the trees.\n";
        mRoadProgress++;
        break;

    case 1: {
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nThe road narrows as thick vegetation crosses the path.\n";
        std::cout << "Something stirs in the bushes nearby.\n";

        //v.03. Scripted first encounter. 
        Bestiary bestiary;

        Enemy snake = bestiary.CreateVenomousSnake();

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nA Venomous Snake emerges from the bushes!\n";

        CombatResult result = mCombatSystem.StartCombat(OraKanu, Mbatha, snake, mInventory);

        if (result == CombatResult::Victory) {
            //Award Cowries for defeating the snake.
            mCowries += snake.GetCowrieReward();

            Menu::SetTextColor(Menu::IVORY);
            std::cout << "\nYou collected " << snake.GetCowrieReward() << " Cowries!\n";
            std::cout << "Party Cowries: " << mCowries << "\n";

            std::cout << "\nThe snake collapses to the ground.\n";
            std::cout << "The heroes have survived their first encounter.\n";

            mRoadProgress++;
        }
        else if (result == CombatResult::Defeat) {
            Menu::SetTextColor(Menu::IVORY);
            std::cout << "\nThe heroes fall along the roadside...\n";
            std::cout << "Their journey ends before it can truly begin.\n";

            IsGameRunning = false;
        }
    }
          break;

    case 2:
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nThe road grows quiet once more.\n";
        std::cout << "\nOra'Kanu and M'Batha continue toward the distant village.\n";

        mRoadProgress++;
        break;

    case 3:
        Menu::SetTextColor(Menu::IVORY);
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
//=========================================
//    v.02 Explore Location
//=========================================
//v.02 - Handles player-controlled exploration.
void Game::ExploreLocation() {
    while (IsGameRunning) {
        //v.05 Clear screen. 
        Menu::ClearScreen();

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

        std::cout << "\n[S] Save Game\n";

        std::cout << "\nEnter your choice: ";

        //Read the entire line of user input.
        if (!std::getline(std::cin, input)) {
            //Handle closed or failed input.
            IsGameRunning = false;
            break;
        }
        //v.05 Save the game directly from exploration.
        if (input == "S" || input == "s") {
            SaveSystem::SaveGame(*this);

            // Keep the save result visible before refreshing exploration.
            Menu::PauseForEnter();

            continue;
        }
        //Convert input into an integer.
        try {
            size_t position = 0;

            choice = std::stoi(input, &position);

            //Reject input containing extra characters.
            if (position != input.length()) {
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        catch (const std::out_of_range&) {
            std::cout << "Number is too large. Please try again.\n";
            continue;
        }

        //v.03 View the party inventory. 
        if (choice == 9) {
            mInventory.DisplayInventory();
            Menu::SetTextColor(Menu::IVORY);
            std::cout << "\n1. Use Item\n";
            std::cout << "2. Equip Item\n"; //v.04 Add entry for equip item.
            std::cout << "0. Return\n";
            std::cout << "\nSelection: ";

            std::string inventoryInput;
            int inventoryChoice = -1;

            std::getline(std::cin, inventoryInput);

            try {
                size_t position = 0;
                inventoryChoice = std::stoi(inventoryInput, &position);

                //Rejects inputs like 1abd and 1.5
                if (position != inventoryInput.length()) {
                    std::cout << "\nInvalid Selection.\n";
                    continue;
                }
            }
            catch (const std::invalid_argument&) {
                std::cout << "\nInvalid Selection.\n";
                continue;
            }
            catch (const std::out_of_range&) {
                std::cout << "\nSelection out of range.\n";
                continue;
            }

            if (inventoryChoice == 1) {
                ItemManager::UseItemOutsideofCombat(mInventory, OraKanu, Mbatha);
            }
            else if (inventoryChoice == 2) {
                ItemManager::EquipItemOutsideofCombat(mInventory, OraKanu, Mbatha); //v.04 Added equip item.
            }
            else if (inventoryChoice != 0) {
                std::cout << "\nInvalid selection.\n";
            }

            // Return to exploration after viewing inventory.
            std::cout << "\nPress ENTER to return to exploration...";
            std::string pause;
            std::getline(std::cin, pause);

            continue;
        }
        //Exit exploration.
      // Exit exploration and return to the main menu.
        if (choice == 0) {
            std::cout << "\nReturning to Main Menu...\n";

            IsGameRunning = false;
            break;
        }

        //Validate the selected destination.
        if (choice >= 1 && choice <= static_cast<int>(connections.size())) {
            //Convert menu selection to vector index.
            int index = choice - 1;

            //Retrieve the selected destination ID.
            int destinationID = connections[index];

            //v.03 The chief will only recieve visitors sent by the shaman. 
            if (destinationID == 11 && !mHasMetShaman) {

                Menu::ClearScreen();

                // Scene heading.
                Menu::SetTextColor(Menu::GREEN);
                std::cout << "\n==========================================================\n";

                Menu::SetTextColor(Menu::GOLD);
                std::cout << "                     CHIEF'S HUT                            \n";

                Menu::SetTextColor(Menu::GREEN);
                std::cout << "============================================================\n";

                // Narration.
                Menu::SetTextColor(Menu::IVORY);
                std::cout << "\nTwo village guards stand outside the chief's hut.\n";

                // NPC name.
                Menu::SetTextColor(Menu::RED);
                std::cout << "\nGuard: ";

                // NPC dialogue.
                Menu::SetTextColor(Menu::IVORY);
                std::cout << "\"The chief is not receiving visitors.\"\n";

                // Second line of dialogue.
                Menu::SetTextColor(Menu::RED);
                std::cout << "\nGuard: ";

                Menu::SetTextColor(Menu::IVORY);
                std::cout << "\"If you seek an audience, speak with the shaman first.\"\n";

                // Restore the default text color.
                Menu::SetTextColor(Menu::IVORY);

                Menu::PauseForEnter();
                continue;
            }

            //Update the player's current location.
            mCurrentLocationId = destinationID;

            //v.03 Trigger the shaman's introduction when entering his hut. 
            if (mCurrentLocationId == 12) {
                MeetShaman();
            }
            //v.03 Trigger the chief's introduction when entering his hut.
            if (mCurrentLocationId == 11) {
                MeetChief();

            }
            //v.04 Visit Merchant.
            if (mCurrentLocationId == 10) {
                VisitMerchant();
            }

            //v.03 Discover the necklace after accepting the chief's request. 
            if (mCurrentLocationId == 15 && mHasMetChief && !mHasFoundNecklace) {
                DiscoverNecklace();
            }

            //v.04 Trigger Bloodroot Hollow's introduction.
            if (mCurrentLocationId == 7 && !mHasEnteredBloodrootHollow) {
                EnterBloodrootHollow();
            }

            //v.04 Trigger the withered grove story scene. 
            if (mCurrentLocationId == 16 && !mHasExploredWitheredGrove) {
                ExploreWitheredGrove();
            }

            // v.04 Trigger the Bone-Strewn Path story scene.
            if (mCurrentLocationId == 17 && !mHasExploredBoneStrewnPath) {
                ExploreBoneStrewnPath();
            }

            //v.04 Trigger the Desecrated Shrine story scene. 
            if (mCurrentLocationId == 18 && !mHasExploredDesecratedShrine) {
                ExploreDesecratedShrine();
            }

            //v.04 Trigger the Heart of the Hollow story scene.
            if (mCurrentLocationId == 19 && !mHasExploredHeartoftheHollow) {
                ExploreHeartoftheHollow();
            }

            //v.04 Trigger the end game boss fight.
            if (mCurrentLocationId == 19 && mHasExploredHeartoftheHollow && !mHasDefeatedBonsamElder) {
                StartBonsamElderFight();
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
//============================================================
//   v.03 Story Element for Shaman's Hut    
//============================================================

void Game::MeetShaman() {
    // Handle returning to the shaman after the chief's confession.
    if (mHasMetShaman) {
        if (mHasDefeatedBonsamElder && mHasHeardChiefsConfession && !mHasHeardShamansWarning) {
            ShamansWarning();
        }
        Menu::SetTextColor(Menu::IVORY);
        return;
    }
    //Give the shaman's intro his own screen. 
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n====================================================================\n"; 

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                          The Shaman's Call                             "; 

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n=====================================================================\n"; 

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe scent of burning herbs fills the small hut.\n"; 
    std::cout << "\nAn elderly shaman sits beside a flickering fire,\n"; 
    std::cout << "\nhis weathered handsresting upon a wooden staff.\n"; 

    std::cout << "\nAs Ora'Kanu and M'Batha enter, the shaman slowly rises.\n"; 
    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: "; 
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Your have come...you have heard my prayers.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: "; 
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Your voice has carried far beyond this village.\n";
    std::cout << "Tell us what troubles your people.\"\n"; 

    std::cout << "\nThe Shaman lowers his gaze.\n"; 

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: "; 
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Our children have began to disappear.\n";
    std::cout << "Fishermen leave for the river and never return.\n"; 
    std::cout << "The people grow frightened, and I fear their\n"; 
    std::cout << "suffering has only just begun.\"\n";

    Menu::SetTextColor(Menu::GRAY);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Have your hunters searched the wilderness?\"\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: "; 
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"They have found nothing, but there are places\n";
    std::cout << "beyond this village where even our bravest hunters\n"; 
    std::cout << "dare not travel.\"\n"; 

    std::cout << "\nThe shaman glances at the doorway.\n"; 

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You must speak with our cheif.\n";
    std::cout << "he knows more of these disappearances than I can\n"; 
    std::cout << "explain here. Tell him I sent you.\"\n"; 

    std::cout << "\nOra'Kanu nods.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    std::cout << "\"Then we will speak with him.\"\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "==========================================================";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "\nPress ENTER to continue.\n";

    std::string input;
    std::getline(std::cin, input);

    // Restore the default text color.
    Menu::SetTextColor(Menu::IVORY);
    //Record that the introduction has occured. 
    mHasMetShaman = true; 
}
//============================================================
//   v.03 Story Element for Meeting the Village Cheif   
//============================================================
void Game::MeetChief() {
    if (mHasMetChief) {
        // The boss has been defeated.
        // 
        // Trigger the Chief's Confession first.
        if (mHasDefeatedBonsamElder && !mHasHeardChiefsConfession) {
            ChiefsConfession();
        }

        // Handle Ama's Necklace if the quest is still pending.
        else if (mHasFoundNecklace && !mHasReturnedNecklace) {
            ReturnNecklacetoChief();
        }
        Menu::SetTextColor(Menu::IVORY);
        return;
    }
    //Clear for the chief's introduction. 
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n=====================================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                          The Chief's Request                            ";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n=====================================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe village cheif sits before a wooden table,\n"; 
    std::cout << "studying a collection of markings carved into its surface.\n"; 
    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Strangers, what business brings you to my village?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We answered the prayers of your shaman.\n";
    std::cout << "He told us your people have gone missing.\"\n";

    std::cout << "\nThe chief's expression grows troubled.\n"; 

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then you know why we need help.\n";
    std::cout << "Children have vanished, and fishermen have failed to\n"; 
    std::cout << "return from the river.\"\n"; 

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Where were they last seen?\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nCheif: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Near the wilderness beyond our village.\n";
    std::cout << "Our hunters searched the nearby trails, but found nothing.\"\n"; 

    std::cout << "\nThe chief pauses before continuing.\n"; 

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"I ask that you investigate those woods.\n";
    std::cout << "Search for anything that might explain these disappearances.\n"; 
    std::cout << "If you discover something, return to me.\"\n"; 

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We will search the wilderness.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"May the spirits guide your steps.\"\n";
    
    Menu::SetTextColor(Menu::GREEN);
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
    //Give the necklace discovery its own screen. 
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================" << std::endl;

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                     A Child's Necklace                       " << std::endl;

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "==============================================================" << std::endl;

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe river moves quietly through the clearing.\n"; 
    std::cout << "As the heroes approach the water, something catches\n"; 
    std::cout << "Ora'Kanu's attention just beneath the water near the shore.\n"; 

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"M'Batha, come and look at this.\"\n";

    std::cout << "\nM'Batha kneels beside the riverbank and carefully\n"; 
    std::cout << "pulls a small necklace from the mud.\n"; 

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"A child's necklace...\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Perhaps it belongs to one of the missing.\n";
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
    // Clear exploration before displaying the Chief's Sorrow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================" << std::endl;
    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                    The Chief's Sorrow                        " << std::endl;

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "==============================================================" << std::endl;

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe chief looks up as Ora'Kanu and M'Batha enter.\n"; 

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You have returned. What have you discovered?\"\n";

    std::cout << "\nM'Batha places the small necklace upon the table.\n"; 

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We found this near the River Bank.\"\n";

    std::cout << "\nThe chief reaches for the necklace, but his hand\n"; 
    std::cout << "stops just short of touching it.\n"; 

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"This belonged to Ama...\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You recognize it?\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Her mother gave it to her. She never took it off.\"\n";

    std::cout << "\nThe chief lowers his head in silence.\n"; 

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    std::cout << "\"There is a place beyond the river.\n";
    std::cout << "Our people have avoided it for generations.\n"; 
    std::cout << "We call it Bloodroot Hollow. It is dangerous, filled with\n";
    std::cout << "darkness. Creatures that live on blood...the Bonsam.\"\n"; 

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Leave it to us, we will investigate this Bloodroot Hollow.\"\n";

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
    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "Chief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"These belonged to warriors who once protected our village.\n";
    std::cout << "Take them. You may need their strength in the days ahead.\"\n"; 

    std::cout << "\n[QUEST REWARD: Shaman Bracers]\n";
    std::cout << "[QUEST REWARD: Reinforced Wraps]\n";

    //v.04 Prevents the conversation from repeating. 
    mHasReturnedNecklace = true; 

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}
//================================================================================
//v.04             Story Elemtns -  Bloodroot Hollow           
//================================================================================
void Game::EnterBloodrootHollow() {
    //Prevent the scene from repeating. 
    if (mHasEnteredBloodrootHollow) {
        return;
    }
    // Clear the screen before entering Bloodroot Hollow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n===========================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                  BLOODROOT HOLLOW\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe forest grows unnaturally quiet as the heroes\n";
    std::cout << "leave the familiar wilderness behind.\n";

    std::cout << "\nThe trees stand close together, their branches\n";
    std::cout << "intertwining overhead and swallowing the afternoon light.\n";

    std::cout << "\nThick roots, stained a deep crimson, twist across\n";
    std::cout << "the ground like veins beneath the forest floor.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Something is wrong with this place.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The forest is old. Older than the village.\"\n";

    std::cout << "\nA faint rattling sound draws their attention.\n";

    std::cout << "\nSmall wooden charms hang from the surrounding trees,\n";
    std::cout << "swaying gently despite the absence of wind.\n";

    std::cout << "\nM'Batha approaches one of the trees.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"These markings... I've seen some of them before.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Where?\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Protective symbols. Used to mark sacred ground.\n";
    std::cout << "But these others... I don't recognize them.\"\n";

    std::cout << "\nBeyond the hanging charms, a weathered warning\n";
    std::cout << "has been carved deep into the bark of an ancient tree.\n";

    std::cout << "\nThe words have nearly disappeared beneath the moss.\n";

    std::cout << "\nOra'Kanu brushes the moss away.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"A boundary.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"A warning?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Perhaps. But warnings are meant to keep\n";
    std::cout << "something on one side of a line.\"\n";

    std::cout << "\nHe looks toward the darkness beyond the trees.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The question is which side they feared.\"\n";

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

void Game::ExploreWitheredGrove() {
    //Prevent the scene from repeating. 
    if (mHasExploredWitheredGrove) {
        return;
    }
    // Clear the screen before entering Bloodroot Hollow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n=======================================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                       The Withered Grove                                  ";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "=========================================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe deeper the heroes travel into Bloodroot Hollow,\n";
    std::cout << "the more the forest begins to change.\n";

    std::cout << "\nThe crimson roots that once twisted beneath their feet\n";
    std::cout << "have turned black and brittle.\n";

    std::cout << "\nLeaves hang lifeless from the branches overhead.\n";
    std::cout << "The earth is dry, cracked, and strangely warm.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"These trees have been dead for some time.\"\n";

    std::cout << "\nOra'Kanu kneels beside a fallen branch.\n";

    std::cout << "\nShe presses her palm against the darkened wood.\n";

    std::cout << "\nFor a brief moment, a faint current of Ase moves\n";
    std::cout << "through her fingertips.\n";

    std::cout << "\nThen it vanishes.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"No. They are still dying.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"What do you mean?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    std::cout << "\"There is life beneath the bark.\n";
    std::cout << "Something is draining it away.\"\n";

    std::cout << "\nA sudden gust moves through the grove.\n";

    std::cout << "\nThe branches tremble, but not a single leaf falls.\n";

    std::cout << "\nOra'Kanu closes her eyes.\n";

    std::cout << "\nShe reaches outward with her Ase, searching for\n";
    std::cout << "the familiar rhythm of the wind and approaching rain.\n";

    std::cout << "\nBut the air feels wrong.\n";

    std::cout << "\nHeavy. Restless.\n";

    std::cout << "\nLike a storm trapped beneath the earth.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"There is something beneath this place.\n";
    std::cout << "I can feel it moving through the roots.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Toward us?\"\n";

    std::cout << "\nOra'Kanu slowly shakes her head.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Toward the village.\"\n";

    std::cout << "\nM'Batha looks back along the path they traveled.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then whatever is happening here will not\n";
    std::cout << "remain hidden in these woods for much longer.\"\n";

    std::cout << "\nA sharp cracking sound echoes through the grove.\n";

    std::cout << "\nOne of the ancient trees splits down its center.\n";

    std::cout << "\nFrom within its hollow trunk, a thick black substance\n";
    std::cout << "slowly seeps into the surrounding soil.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We need to find where this began.\"\n";

    std::cout << "\n[LORE DISCOVERED: The Withering of Bloodroot Hollow]\n";

    // Record that the scene has played.
    mHasExploredWitheredGrove = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

void Game::ExploreBoneStrewnPath()
{
    // Prevent this scene from repeating.
    if (mHasExploredBoneStrewnPath) {
        return;
    }
    // Clear the screen before entering Bloodroot Hollow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                    THE BONE-STREWN PATH\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe narrow trail winds between ancient trees,\n";
    std::cout << "their exposed roots twisting through the dark soil.\n";

    std::cout << "\nWith each step, the ground becomes increasingly uneven.\n";

    std::cout << "\nA sharp cracking sound breaks the silence.\n";

    std::cout << "\nM'Batha stops walking.\n";

    std::cout << "\nBeneath his foot lies a small, weathered bone.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Ora'Kanu. Look at the ground.\"\n";

    std::cout << "\nOra'Kanu lowers her gaze.\n";

    std::cout << "\nScattered among the roots are dozens of bones,\n";
    std::cout << "some bleached white, others nearly swallowed by the earth.\n";

    std::cout << "\nThe remains of animals lie alongside fragments\n";
    std::cout << "that appear unmistakably human.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"This place has claimed many lives.\"\n";

    std::cout << "\nM'Batha kneels beside a collection of broken remains.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Not all of them recently.\"\n";

    std::cout << "\nHe lifts an old bone from the soil.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Some have been here for years.\n";
    std::cout << "Perhaps longer.\"\n";

    std::cout << "\nA few steps farther along the path,\n";
    std::cout << "something catches Ora'Kanu's attention.\n";

    std::cout << "\nA torn fishing net hangs from a low branch,\n";
    std::cout << "its fibers tangled around the crimson roots.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"This doesn't belong here.\"\n";

    std::cout << "\nM'Batha approaches the net.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"One of the missing fishermen?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Possibly. But look at the fibers.\"\n";

    std::cout << "\nThe net has been torn apart with tremendous force.\n";

    std::cout << "\nNearby, the remains of a wooden fishing spear\n";
    std::cout << "lie partially buried beneath the roots.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Someone fought here.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"And whatever happened was recent.\"\n";

    std::cout << "\nM'Batha looks toward the deeper forest.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then the chief was right to fear this place.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Perhaps. But something troubles me.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"What is it?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"These older remains have been here for years.\n";
    std::cout << "Yet the village survived beside this forest for generations.\"\n";

    std::cout << "\nShe looks again at the torn fishing net.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Why has the danger suddenly reached beyond\n";
    std::cout << "the hollow?\"\n";

    std::cout << "\nBefore M'Batha can answer, a distant rustling\n";
    std::cout << "moves through the surrounding trees.\n";

    std::cout << "\nSomething shifts among the branches overhead.\n";

    std::cout << "\nThen the forest falls silent once more.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We are not alone.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"No. And I suspect we have not been alone\n";
    std::cout << "since entering these woods.\"\n";

    std::cout << "\n[LORE DISCOVERED: The Bones of Bloodroot Hollow]\n";

    // Mark the story event as completed.
    mHasExploredBoneStrewnPath = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

void Game::ExploreDesecratedShrine()
{
    // Prevent this scene from repeating.
    if (mHasExploredDesecratedShrine) {
        return;
    }
    // Clear the screen before entering Bloodroot Hollow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                    THE DESECRATED SHRINE\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe twisted trees begin to thin as Ora'Kanu and\n";
    std::cout << "M'Batha approach a small clearing.\n";

    std::cout << "\nAt its center stands the remains of an ancient shrine.\n";

    std::cout << "\nWeathered stone pillars rise from the earth,\n";
    std::cout << "their surfaces covered in faded carvings.\n";

    std::cout << "\nA massive stone altar rests between them.\n";

    std::cout << "\nOr rather, what remains of one.\n";

    std::cout << "\nThe altar has been shattered into several pieces.\n";
    std::cout << "Broken offerings lie scattered across the ground.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Someone has destroyed this place.\"\n";

    std::cout << "\nOra'Kanu approaches one of the stone pillars.\n";

    std::cout << "\nShe runs her fingers across the ancient markings.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"These symbols...\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You've seen them before?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"At the entrance to Bloodroot Hollow.\n";
    std::cout << "The markings carved into the trees.\"\n";

    std::cout << "\nM'Batha examines the base of the broken altar.\n";

    std::cout << "\nBeneath the rubble, he discovers several small\n";
    std::cout << "wooden bowls and fragments of woven cloth.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Offerings.\"\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"To whom?\"\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Or to what?\"\n";

    std::cout << "\nThe two warriors examine the shrine more closely.\n";

    std::cout << "\nSeveral carvings depict figures standing on\n";
    std::cout << "opposite sides of a winding river.\n";

    std::cout << "\nBetween them stands a great tree,\n";
    std::cout << "its roots stretching beneath both shores.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Look at the figures.\"\n";

    std::cout << "\nOn one side, human forms carry baskets and bowls.\n";

    std::cout << "\nOn the other, strange elongated figures emerge\n";
    std::cout << "from the shadows beneath the trees.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"These are not scenes of battle.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"No. They are exchanging something.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"An offering?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Perhaps an agreement.\"\n";

    std::cout << "\nA sudden breeze passes through the clearing.\n";

    std::cout << "\nLoose dust rises from the shattered altar.\n";

    std::cout << "\nOra'Kanu kneels beside the largest broken stone.\n";

    std::cout << "\nIts fractured edges are sharp and pale,\n";
    std::cout << "unlike the weathered surfaces surrounding them.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"This destruction is recent.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then someone wanted the shrine gone.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"And whatever understanding existed here\n";
    std::cout << "may have been destroyed along with it.\"\n";

    std::cout << "\nM'Batha looks toward the deeper forest.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    std::cout << "\"Could this explain the disappearances?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"It may explain why they began.\n";
    std::cout << "But we still do not know who broke the agreement.\"\n";

    std::cout << "\nShe rises and looks toward the path ahead.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Someone knows what happened here.\n";
    std::cout << "We need to find them.\"\n";

    std::cout << "\nAs the heroes turn away from the altar,\n";
    std::cout << "a low whisper moves through the surrounding trees.\n";

    std::cout << "\nThe sound resembles a voice,\n";
    std::cout << "but its words cannot be understood.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Did you hear that?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Yes.\"\n";

    std::cout << "\nShe watches the darkness beyond the clearing.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"And I believe it heard us.\"\n";

    std::cout << "\n[LORE DISCOVERED: The Broken Covenant]\n";

    // Record that the story event has played.
    mHasExploredDesecratedShrine = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

void Game::ExploreHeartoftheHollow() {
    if (mHasExploredHeartoftheHollow) {
        return;
    }
    // Clear the screen before entering Bloodroot Hollow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                    HEART OF THE HOLLOW\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "\nThe trees part to reveal an enormous clearing.\n";
    std::cout << "At its center stands a colossal, ancient tree.\n";

    std::cout << "\nIts roots rise from the ground like the bones\n";
    std::cout << "of some long-forgotten giant.\n";

    std::cout << "\nThe earth beneath it is black and lifeless.\n";
    std::cout << "Not a single blade of grass grows within the clearing.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"This must be the heart of the forest.\"\n";

    std::cout << "\nOra'Kanu studies the enormous tree.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Whatever is draining the hollow...\n";
    std::cout << "I can feel it gathering here.\"\n";

    std::cout << "\nA deep vibration moves through the ground.\n";

    std::cout << "\nThe roots begin to tremble.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Ora'Kanu...\"\n";

    std::cout << "\nFrom the darkness beneath the ancient tree,\n";
    std::cout << "a towering figure slowly emerges.\n";

    std::cout << "\nIts limbs are unnaturally long, its body thin\n";
    std::cout << "and twisted beneath layers of darkened bark.\n";

    std::cout << "\nTwo pale eyes open within the shadows.\n";

    std::cout << "\nA voice rises from the creature,\n";
    std::cout << "deep and ancient, like wood splitting beneath pressure.\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Children of the world beyond the roots...\"\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Why have you entered my domain?\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We seek those who have vanished from the village.\"\n";

    std::cout << "\nThe Elder's pale eyes narrow.\n";

    std::cout << "\nBonsam Elder: \"The village...\"\n";

    std::cout << "\nA low, bitter sound escapes its throat.\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"For generations, we kept our distance.\n";
    std::cout << "Your people remained beyond the boundary.\n";
    std::cout << "Mine remained beneath the roots.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then you know of the agreement.\"\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"An agreement carved in stone.\n";
    std::cout << "An agreement your people shattered.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We found the shrine.\n";
    std::cout << "But we do not know who destroyed it.\"\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"And yet it lies broken.\n";
    std::cout << "The roots wither. The old protections fail.\"\n";

    std::cout << "\nThe ancient tree groans overhead.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The village is suffering as well.\n";
    std::cout << "Children have disappeared. Fishermen have not returned.\"\n";

    std::cout << "\nFor a moment, the Elder remains silent.\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The hunger has awakened.\n";
    std::cout << "Even my own have begun to lose themselves to it.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then help us stop it.\"\n";

    std::cout << "\nThe Elder steps forward.\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You speak of stopping what you do not understand.\"\n";

    std::cout << "\nIts enormous claws dig into the blackened earth.\n";

    Menu::SetTextColor(Menu::PURPLE);
    std::cout << "\nBonsam Elder: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"If you would challenge the darkness\n";
    std::cout << "beneath these roots, first prove you can survive it.\"\n";

    std::cout << "\nM'Batha raises his fists.\n";

    std::cout << "\nOra'Kanu calls upon the gathering storm.\n";

    std::cout << "\nThe Elder releases a terrible cry.\n";

    std::cout << "\n[ BOSS ENCOUNTER: BONSAM ELDER ]\n";

    mHasExploredHeartoftheHollow = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}
void Game::StartBonsamElderFight()
{
    // Prevent the boss from respawning after victory.
    if (mHasDefeatedBonsamElder) {
        return;
    }

    // Create the boss using our existing Bestiary.
    Bestiary bestiary;
    Enemy elder = bestiary.CreateBonsamElder();

    // Clear the screen before entering Bloodroot Hollow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                 BOSS: BONSAM ELDER\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    // Start the scripted boss encounter.
    CombatResult result = mCombatSystem.StartCombat(OraKanu, Mbatha, elder, mInventory);

    if (result == CombatResult::Victory) {
        mHasDefeatedBonsamElder = true;
        //Award Cowries for defeating the Bonsam Elder.
        mCowries += elder.GetCowrieReward();

        std::cout << "\nYou collected "
            << elder.GetCowrieReward()
            << " Cowries!\n";

        std::cout << "Party Cowries: " << mCowries << "\n";

        // Allow the player to read the combat rewards before the story resumes.
        Menu::PauseForEnter();

        // Begin the post-battle story on a fresh screen.
        Menu::ClearScreen();
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nThe Bonsam Elder collapses beneath the ancient tree.\n";
        std::cout << "Its enormous claws scrape against the blackened earth.\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "\nM'Batha: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"It is finished.\"\n";

        Menu::SetTextColor(Menu::CYAN);
        std::cout << "\nOra'Kanu: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"No. Something is still moving beneath us.\"\n";

        std::cout << "\nA faint trembling passes through the roots.\n";

        Menu::SetTextColor(Menu::PURPLE);
        std::cout << "\nBonsam Elder: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"You have defeated a guardian...\n";
        std::cout << "not the thing it guarded against.\"\n";

        Menu::SetTextColor(Menu::CYAN);
        std::cout << "\nOra'Kanu: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"The missing villagers. Where are they?\"\n";

        std::cout << "\nThe Elder's pale eyes turn toward the ancient tree.\n";

        Menu::SetTextColor(Menu::PURPLE);
        std::cout << "\nBonsam Elder: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"Some were brought beneath the roots.\n";
        std::cout << "Others wandered here when the old protections failed.\"\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "\nM'Batha: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"Are they alive?\"\n";

        std::cout << "\nFor a long moment, the Elder says nothing.\n";

        Menu::SetTextColor(Menu::PURPLE);
        std::cout << "\nBonsam Elder: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"Many are not.\"\n";

        std::cout << "\nThe clearing falls silent.\n";

        Menu::SetTextColor(Menu::PURPLE);
        std::cout << "\nBonsam Elder: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"Their bodies fed the earth.\n";
        std::cout << "Their Ase fed something far beneath it.\"\n";

        std::cout << "\nOra'Kanu kneels and places her palm against a root.\n";

        std::cout << "\nA cold pulse answers her touch.\n";

        std::cout << "\nFor an instant, she senses dozens of faint echoes.\n";
        std::cout << "Voices without words. Lives without warmth.\n";

        std::cout << "\nThen something vast stirs beneath them.\n";

        std::cout << "\nOra'Kanu recoils.\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "\nM'Batha: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"What did you feel?\"\n";

        Menu::SetTextColor(Menu::CYAN);
        std::cout << "\nOra'Kanu: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"Something that knows we're here.\"\n";

        std::cout << "\nThe Elder struggles to raise its head.\n";

        Menu::SetTextColor(Menu::PURPLE);
        std::cout << "\nBonsam Elder: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"The covenant kept it sleeping.\n";
        std::cout << "The shrine was broken. The hunger returned.\"\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "\nM'Batha: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"Who destroyed the shrine?\"\n";

        Menu::SetTextColor(Menu::PURPLE);
        std::cout << "\nBonsam Elder: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"I do not know.\"\n";

        std::cout << "\nIts voice weakens.\n";

        Menu::SetTextColor(Menu::PURPLE);
        std::cout << "\nBonsam Elder: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"But someone wished for the hunger\n";
        std::cout << "to awaken.\"\n";

        std::cout << "\nA final shudder passes through the Elder's body.\n";

        std::cout << "\nIts pale eyes close.\n";

        std::cout << "\nThe ancient tree stands silent above the fallen guardian.\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "\nM'Batha: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"We came here to save those people.\"\n";

        Menu::SetTextColor(Menu::CYAN);
        std::cout << "\nOra'Kanu: ";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\"And now we must tell their families\n";
        std::cout << "what we've discovered.\"\n";

        std::cout << "\n[QUEST UPDATED: RETURN TO THE VILLAGE]\n";

        std::cout << "\nPress ENTER to continue...";
        std::string pause;
        std::getline(std::cin, pause);
    }
    else if (result == CombatResult::Defeat) {
        std::cout << "\nThe heroes fall beneath the ancient tree.\n";
        std::cout << "The darkness of Bloodroot Hollow claims another victory.\n";

        IsGameRunning = false;
    }
}
//============================================================
// v.04        Story Element - The Chief's Confession
//============================================================

void Game::ChiefsConfession() {
    // Prevent the scene from repeating.
    if (mHasHeardChiefsConfession) {
        return;
    }

    // Clear exploration before displaying the Chief's Sorrow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n==========================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                    THE CHIEF'S CONFESSION\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe chief rises as Ora'Kanu and M'Batha enter his hut.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You have returned from Bloodroot Hollow.\"\n";

    std::cout << "\nHis eyes search the doorway behind them.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Did you find our people?\"\n";

    std::cout << "\nNeither warrior answers immediately.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We found evidence of what happened to them.\"\n";

    std::cout << "\nThe chief slowly lowers himself into his chair.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Tell me.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Many of those who disappeared are dead.\"\n";

    std::cout << "\nThe chief closes his eyes.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Something beneath the forest has been\n";
    std::cout << "feeding upon their Ase.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We confronted the Bonsam Elder.\n";
    std::cout << "It spoke of an ancient agreement with your village.\"\n";

    std::cout << "\nThe chief's expression changes.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then you found the shrine.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You knew about it?\"\n";

    std::cout << "\nThe chief looks toward the markings carved into\n";
    std::cout << "the wooden table before him.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"My father told me the stories.\n";
    std::cout << "And his father told them to him.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Long before this village stood beside the river,\n";
    std::cout << "our ancestors made a covenant with the Bonsam.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"What kind of covenant?\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We would remain beyond the marked boundary.\n";
    std::cout << "The Bonsam would remain within the hollow.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Each season, offerings were carried to the shrine.\n";
    std::cout << "They were a promise that neither side had forgotten.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"And the offerings stopped.\"\n";

    std::cout << "\nThe chief lowers his head.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Yes.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Why?\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The old traditions frightened our people.\n";
    std::cout << "They began to question why we honored creatures\n";
    std::cout << "they had never seen.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"I believed the danger had passed.\n";
    std::cout << "I allowed the offerings to end.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"But someone destroyed the shrine.\"\n";

    std::cout << "\nThe chief looks up sharply.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Destroyed?\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The altar was shattered.\n";
    std::cout << "The markings broken.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"I ordered no such thing.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then someone acted without your knowledge.\"\n";

    std::cout << "\nA long silence fills the hut.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"I thought abandoning the offerings\n";
    std::cout << "would free us from the old fears.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Instead, I may have invited something worse.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The Elder believed your people\n";
    std::cout << "had broken the covenant.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"And perhaps we did.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"There is something else.\"\n";

    std::cout << "\nThe chief raises his eyes.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The Elder said something beneath the roots\n";
    std::cout << "had awakened. Something even the Bonsam feared.\"\n";

    std::cout << "\nThe chief's face grows pale.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then you must speak with the shaman.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"What does he know?\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"There are stories older than our village.\n";
    std::cout << "Stories I was never permitted to hear.\"\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"If anyone understands what sleeps beneath\n";
    std::cout << "that forest, it will be him.\"\n";

    std::cout << "\nOra'Kanu turns toward the doorway.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then we have no time to waste.\"\n";

    std::cout << "\nAs the warriors prepare to leave,\n";
    std::cout << "the chief speaks once more.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Ora'Kanu... M'Batha...\"\n";

    std::cout << "\nThey stop.\n";

    Menu::SetTextColor(Menu::YELLOW);
    std::cout << "\nChief: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"When you learn what happened to the others...\n";
    std::cout << "please tell me.\"\n";

    std::cout << "\nHis gaze falls upon the empty place on the table\n";
    std::cout << "where Ama's necklace once rested.\n";

    std::cout << "\nNeither warrior makes a promise.\n";

    std::cout << "\n[QUEST UPDATED: SPEAK WITH THE SHAMAN]\n";

    // Record completion.
    mHasHeardChiefsConfession = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}
//============================================================
// v.04 Story Element - The Shaman's Warning
// Prototype Finale
//============================================================

void Game::ShamansWarning() {
    // Prevent the finale from repeating.
    if (mHasHeardShamansWarning) {
        return;
    }
    // Clear exploration before displaying the Chief's Sorrow.
    Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                    THE SHAMAN'S WARNING\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe shaman's hut is unusually cold.\n";

    std::cout << "\nThe fire at its center burns low,\n";
    std::cout << "casting long shadows across the wooden walls.\n";

    std::cout << "\nThe shaman sits beside the flames,\n";
    std::cout << "his eyes fixed upon the darkness beyond them.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"You have returned.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We have seen what lies within\n";
    std::cout << "Bloodroot Hollow.\"\n";

    std::cout << "\nThe shaman closes his eyes.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then you have seen the Bonsam.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"We fought their Elder.\"\n";

    std::cout << "\nThe shaman's hands tighten around his staff.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"And yet you stand before me.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The Elder was not our true enemy.\"\n";

    std::cout << "\nShe approaches the fire.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Something beneath the forest is feeding\n";
    std::cout << "upon the Ase of the living.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Many of the missing villagers are dead.\n";
    std::cout << "Their lives were taken to feed it.\"\n";

    std::cout << "\nFor a long moment, the shaman says nothing.\n";

    std::cout << "\nThen he reaches into a small wooden chest.\n";

    std::cout << "\nFrom within, he removes a bundle of cloth,\n";
    std::cout << "darkened with age and bound with a leather cord.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"There are stories my teachers forbade\n";
    std::cout << "me from speaking aloud.\"\n";

    std::cout << "\nHe carefully unwraps the bundle.\n";

    std::cout << "\nInside lies a fragment of ancient parchment.\n";

    std::cout << "\nIts surface bears a faded drawing of a great tree.\n";

    std::cout << "\nBeneath its roots, something enormous has been\n";
    std::cout << "drawn in black ink.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"What is that creature?\"\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"I do not know its name.\"\n";

    std::cout << "\nOra'Kanu studies the drawing.\n";

    std::cout << "\nThe shape beneath the tree resembles neither\n";
    std::cout << "man nor beast.\n";

    std::cout << "\nIts countless limbs stretch outward,\n";
    std::cout << "disappearing beyond the parchment's edges.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Long ago, our ancestors believed\n";
    std::cout << "that the world itself could become hungry.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The world?\"\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Not the earth beneath our feet.\n";
    std::cout << "Something that dwells within it.\"\n";

    std::cout << "\nThe shaman points toward the ancient tree.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"The old shrines were not built\n";
    std::cout << "merely to honor the spirits.\"\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"They were built to keep something sleeping.\"\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then the covenant was a protection.\"\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"For the village. For the Bonsam.\n";
    std::cout << "Perhaps for all who live upon this land.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Someone destroyed the shrine.\"\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Then someone has broken the seal.\"\n";

    std::cout << "\nA sudden gust extinguishes the fire.\n";

    std::cout << "\nThe hut falls into darkness.\n";

    std::cout << "\nOutside, the village dogs begin to howl.\n";

    std::cout << "\nOra'Kanu raises her hand.\n";

    std::cout << "\nA faint current of Ase dances across her fingers,\n";
    std::cout << "illuminating the parchment.\"\n";

    std::cout << "\nSomething in the drawing has changed.\n";

    std::cout << "\nWhere the ancient tree once stood alone,\n";
    std::cout << "several smaller markings now surround it.\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Were those there before?\"\n";

    std::cout << "\nThe shaman stares at the parchment.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"No.\"\n";

    std::cout << "\nThe markings spread across the parchment,\n";
    std::cout << "branching outward like veins beneath skin.\n";

    Menu::SetTextColor(Menu::CYAN);
    std::cout << "\nOra'Kanu: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"These are other places.\"\n";

    std::cout << "\nThe shaman nods slowly.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"Other seals.\"\n";

    Menu::SetTextColor(Menu::RED);
    std::cout << "\nM'Batha: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"How many?\"\n";

    std::cout << "\nThe shaman looks toward the doorway.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\nShaman: ";
    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\"I fear we are about to discover that.\"\n";

    std::cout << "\nA distant rumble passes beneath the village.\n";

    std::cout << "\nThe wooden walls tremble.\n";

    std::cout << "\nFor a brief moment, something whispers\n";
    std::cout << "from beneath the floorboards.\n";

    std::cout << "\nThe voice is faint.\n";

    std::cout << "\nBut Ora'Kanu understands its meaning.\n";

    std::cout << "\nIt is not calling for help.\n";

    std::cout << "\nIt is calling for more.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                    THE JOURNEY CONTINUES\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "\nThe darkness beneath Bloodroot Hollow has awakened.\n";

    std::cout << "\nAnd somewhere beyond the village,\n";
    std::cout << "other ancient protections are beginning to fail.\n";

    std::cout << "\nOra'Kanu and M'Batha have survived their first trial.\n";

    std::cout << "\nBut their journey across the Dark Continent\n";
    std::cout << "has only just begun.\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "            FIRST FANTASY: THE DARK CONTINENT\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "\n                    END OF PROTOTYPE\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "\n              Thank you for playing!\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    // Record the finale as completed.
    mHasHeardShamansWarning = true;

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

    // Clear the screen only when an encounter actually occurs.
    Menu::ClearScreen();

    std::cout << "\nAn enemy approaches!\n"; 

    //Start combat using the existing combat system. 
    CombatResult result = mCombatSystem.StartCombat(OraKanu, Mbatha, selectedEnemy, mInventory); 

    //Award Cowries after winning a random encounter.
    if (result == CombatResult::Victory) {
        mCowries += selectedEnemy.GetCowrieReward();

        std::cout << "\nYou collected "
            << selectedEnemy.GetCowrieReward()
            << " Cowries!\n";

        std::cout << "Party Cowries: " << mCowries << "\n";
    }

    // Handle defeat.
    if (result == CombatResult::Defeat) {

        // Display the defeat message on its own screen.
        Menu::ClearScreen();

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "\n============================================================\n";

        Menu::SetTextColor(Menu::GOLD);
        std::cout << "                       GAME OVER\n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "============================================================\n";
        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nOra'Kanu and M'Batha have fallen in battle.\n";
        std::cout << "\nYour journey has come to an end.\n";

        // Allow the player to read the defeat screen.
        Menu::PauseForEnter();

        // End the current game and return to the main menu.
        IsGameRunning = false;
    }
}
//=================================================
//v.04 Visit the Item Shop
//=================================================
void Game::VisitMerchant() {
    //Create the item catalog and the merchant's inventory. 
    ItemCatalog catalog; 

    std::vector<Item> ShopItems = {
        catalog.CreateHealthPotion(),
        catalog.CreateAsePotion(),
        catalog.CreateAntiVenom(),
        catalog.CreateStormWornBracers(),
        catalog.CreateDhambeWraps(),
        catalog.CreateHideVest(),
    }; 
    //Keep the shop open until the player chooses to leave. 
    while (true) {
        // Refresh the merchant's shop screen.
        Menu::ClearScreen();

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "\n==========================================\n";

        Menu::SetTextColor(Menu::GOLD);
        std::cout << "\n           Village Item Shop              \n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "\n==========================================\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "\nMerchant: \"Welcome, travelers! Care to see my wares?\"\n";

        std::cout << "\nParty Cowries: " << mCowries << "\n";

        // Display the merchant's available items.
        for (int i = 0; i < static_cast<int>(ShopItems.size()); i++) {

            std::cout << i + 1 << ". "
                << ShopItems[i].GetName()
                << " - " << ShopItems[i].GetPrice()
                << " Cowries\n";
        }

        std::cout << "0. Leave Shop\n";
        std::cout << "\nEnter your choice: ";

        std::string input;

        if (!std::getline(std::cin, input)) {
            return;
        }

        int choice = -1;

        // Validate the player's input.
        try {
            size_t position = 0;
            choice = std::stoi(input, &position);

            if (position != input.length()) {
                std::cout << "\nInvalid selection.\n";
                continue;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "\nInvalid selection.\n";
            continue;
        }
        catch (const std::out_of_range&) {
            std::cout << "\nSelection out of range.\n";
            continue;
        }

        // Leave the merchant.
        if (choice == 0) {
            Menu::SetTextColor(Menu::GRAY);
            std::cout << "\nMerchant: ";
            Menu::SetTextColor(Menu::IVORY);
            std::cout << "\"Safe travels, friends!\"\n";
            return;
        }

        // Check that the selected item exists.
        if (choice < 1 || choice > static_cast<int>(ShopItems.size())) {
            std::cout << "\nInvalid item selection.\n";
            continue;
        }

        // Retrieve the selected item.
        Item selectedItem = ShopItems[choice - 1];

        int price = selectedItem.GetPrice();

        // Check whether the party can afford the item.
        if (mCowries < price) {
            Menu::SetTextColor(Menu::GRAY);
            std::cout << "\nMerchant: ";
            Menu::SetTextColor(Menu::IVORY);
            std::cout << "\"You haven't enough Cowries for that!\"\n";
            continue;
        }

        // Complete the purchase.
        mCowries -= price;
        mInventory.AddItem(selectedItem);

        std::cout << "\nPurchased: " << selectedItem.GetName() << "\n";
        std::cout << "Cowries spent: " << price << "\n";
        std::cout << "Remaining Cowries: " << mCowries << "\n";
    }
}
