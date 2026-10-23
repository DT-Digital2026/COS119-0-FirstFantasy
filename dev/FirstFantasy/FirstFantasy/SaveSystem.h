#pragma once

//Forward declaration of the game class. 
//Prevents circular dependencies between headers. 

class Game; 

class SaveSystem {
public: 
	//Saves the current game state to a file. 
	//Returns true if saving succeeds. 
	static bool SaveGame(const Game& game); 

	//Loads a save game and restores its state. 
	//Returns true if Loading succeeds. 
	static bool LoadGame(Game& game); 
};
