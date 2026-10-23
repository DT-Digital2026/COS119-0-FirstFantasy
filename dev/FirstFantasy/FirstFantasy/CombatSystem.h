#pragma once

#include <vector>

#include "Character.h"
#include "Enemy.h"
#include "Inventory.h"

//Created default enum class to allow for randomization of turns during combat. 
enum class CombatTurn {
	OraKanu, 
	MBatha, 
	Enemy, 
};

enum class CombatResult {
	Victory, 
	Defeat, 
};

class CombatSystem {
public:
	//Default Constructor.
	CombatSystem(); 

	//Starts combat and returns the battle outcome. 
	CombatResult StartCombat(Character& OraKanu, Character& MBatha, Enemy& Enemy, Inventory& Inventory); 

private:
	//Stores the turn order for the current battle. 
	std::vector<CombatTurn> mTurnOrder; 

	//Creates and randomizes the turn order. 
	void CreateTurnOrder(); 

	//Handles the characters' combat order. 
	void PlayerTurn(Character& activeCharacter, Enemy& enemy, Inventory& inventory, Character& OraKanu, Character& Mbatha);

	//Handles the enemy combat order. 
	void EnemyTurn(Enemy& Enemy, Character& OraKanu, Character& MBatha); 

	//Calculates damage after defense. 
	int CalculateDamage(int Attack, int Defense); 

	//Checks where all party members are defeated. 
	bool IsPartyDefeated(const Character& OraKane, const Character& MBatha) const; 
};
