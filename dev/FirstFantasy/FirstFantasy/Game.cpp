#include <iostream> 
#include <limits>

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
    //Set the starting location.
    //Set the initial story state.
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

                std::cout << "\nAfter some time, the village comes into view.\n";
                std::cout << "They have finally arrived.\n";
            }
            else if (Result == CombatResult::Defeat)
            {
                std::cout << "\nThe heroes fall along the roadside...\n";
                std::cout << "Their journey ends before it can truly begin.\n";
            }

            // Temporary: end gameplay after this encounter.
            // Later, victory will transition into village exploration.
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