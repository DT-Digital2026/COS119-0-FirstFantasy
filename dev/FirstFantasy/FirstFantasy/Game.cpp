#include <iostream> 
#include <limits>
#include <string>
#include <stdexcept>

#include "Game.h"
#include "AbilityCatalog.h"

//Starts a new game.
void Game::StartNewGame()
{
    InitializeGame();
    GameLoop();
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

    //Create the starting inventory.
    //Set the initial story state.
    mCurrentLocationId = 1; //v.02 Sets the starting location to 1-RoadtoVillage.
}


//Temporary game loop. This will be expanded as the game is developed.
void Game::GameLoop()
{
    while (IsGameRunning)
    {
        int choice;

        std::cout << "\n============================================================" << std::endl;
        std::cout << "                         GAME                               " << std::endl;
        std::cout << "============================================================" << std::endl;

        std::cout << "1. Continue" << std::endl;
        std::cout << "2. Return to Main Menu" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "Invalid input. Please enter 1 or 2." << std::endl;

            //Clears the error state.
            std::cin.clear();

            //Removes the invalid input from the input buffer.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (choice == 1)
        {
            //=========================================
             // Opening Story
             //=========================================

            std::cout << "\nOra'Kane and M'Batha travel along the western road"; 
            std::cout << "\ntoward a remote village.\n"; 

            std::cout << "\nSuddenly, something stirs in the vegetation...\n"; 

            //=========================================
            // Scripted Encounter
            //=========================================
            
            //Create a bestiary object. 
            Bestiary Bestiary; 

            Enemy snake = Bestiary.CreateVenomousSnake();

            //Create the enemy using the Bestiary. 
            std::cout << "\nA Venomous Snake Emerges from the bushes.\n"; 

            //=========================================
            // Opening Story
            //=========================================
            
            //Start combat and store the result. 
            CombatResult Result = mCombatSystem.StartCombat(OraKanu, Mbatha, snake); 



            //=========================================
            // Handle Combat Result
            //=========================================

if (Result == CombatResult::Victory)
{
    std::cout << "\nThe snake collapses to the ground.\n";
    std::cout << "Ora'Kanu and M'Batha continue their journey.\n";

//Clear the leftover newline from the game menu.
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    // v.02 - Begin player-controlled navigation
    // starting at the road to the village.
    ExploreLocation();

            }
            else if (Result == CombatResult::Defeat)
            {
                std::cout << "\nThe heroes fall along the roadside...\n";
                std::cout << "Their journey ends before it can truly begin.\n";
            }

            // End the current gamplay session after combat and player controlled exploration.
            IsGameRunning = false;
        }

        else if (choice == 2)
        {
            IsGameRunning = false;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
        }
    }
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

        //Exit exploration.
        if (choice == 0)
        {
            std::cout << "\nLeaving exploration...\n";
            break;
        }

        //Validate the selected destination.
        if (choice >= 1 && choice <= static_cast<int>(connections.size()))
        {
            //Convert menu selection to vector index.
            int index = choice - 1;

            //Retrieve the selected destination ID.
            int destinationID = connections[index];

            //Update the player's current location.
            mCurrentLocationId = destinationID;
        }
        else
        {
            std::cout << "Invalid destination. Please try again.\n";
        }
    }
}