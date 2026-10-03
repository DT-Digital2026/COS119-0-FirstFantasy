#pragma once

class Menu {
public:
	//Function declaration to display the main menu. 
	int DisplayMainMenu(); 

	//Function declaration to display the gameplay options. 
	void HowToPlay(); 

	//Function declaration to display the game lore. 
	void DisplayLore(); 

	//function declaration to display the endgame credits. 
	void DisplayCredits(); 
	
	//Function declaration to exit the program. 
	bool ConfirmExit(); 

private:
	//Function declaration to get validated menu choice. 
	int GetValidMenuChoice(int minChoice, int maxChoice);
};
