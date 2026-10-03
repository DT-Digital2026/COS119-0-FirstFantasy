#include <iostream>

#include "Menu.h"
#include "Game.h"

int main()
{
    //Created menu object. 
    Menu menu; 
    Game game; 

    //Bool variable for program running. 
    bool IsPgmRunning = true; 

    //Loop to determine if program is running. 
    while (IsPgmRunning) {
        int choice = menu.DisplayMainMenu();
        
        switch(choice) {
        case 1:
            game.StartNewGame(); 
            break; 

        case 2: 
            //Load Game/Continue
            //Placeholder
            break; 

        case 3:
            menu.HowToPlay(); 
            break; 

        case 4: 
            menu.DisplayLore(); 
            break;

        case 5: 
            menu.DisplayCredits(); 
            break;

        case 6:
            if (menu.ConfirmExit() == true) {
                IsPgmRunning = false; 
            }
        }
    }

    return 0; 

}
