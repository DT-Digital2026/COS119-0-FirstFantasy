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

	//v.05 Function to clear screen as game progresses. 
	static void ClearScreen(); 

	//v.05 Will pause to allow the users to enter. 
	static void PauseForEnter();

	//Method for beautification.
	static void SetTextColor(int color);

	// Match the existing main palette.
	static constexpr int GOLD = 14;
	static constexpr int GREEN = 2;
	static constexpr int IVORY = 7;
	static constexpr int RED = 12;
	// Additional character colors.
	static constexpr int CYAN = 11;
	static constexpr int BLUE = 9;
	static constexpr int PURPLE = 13;
	static constexpr int YELLOW = 6;
	static constexpr int WHITE = 15;
	static constexpr int GRAY = 8;

private:
	//Function declaration to get validated menu choice. 
	int GetValidMenuChoice(int minChoice, int maxChoice);
};
