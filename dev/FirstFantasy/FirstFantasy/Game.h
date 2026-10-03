#pragma once

//Creation of the game class. 
class Game {

public:
	//Starts new game, will take no parameters and will return no values.
	void StartNewGame(); 

private: 
	//Bool variable to dictate whether the game is running or not. 
	bool IsGameRunning; 

	//Will initialize the game. Will take no parameters and will return no values. 
	void InitializeGame(); 

	//Game loop definition.
	void GameLoop(); 
};
