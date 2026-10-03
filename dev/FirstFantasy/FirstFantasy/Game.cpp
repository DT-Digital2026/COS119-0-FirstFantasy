#include <iostream> 
#include <limits>

#include "Game.h"

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

    //Later we will:
    //Create the player characters.
    //Set player stats.
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
            std::cout << "\nThe adventure will continue here..." << std::endl;
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