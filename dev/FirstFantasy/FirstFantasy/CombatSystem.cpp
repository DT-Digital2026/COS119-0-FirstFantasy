#include <algorithm> //Needed for std::shuffle
#include <random> //Needed for random number generation.
#include <limits>
#include <iostream>

#include "CombatSystem.h"

//Default Constructor. 
CombatSystem::CombatSystem() {
	//The turn order vector will start empty.
}

//Create turn order. 
void CombatSystem::CreateTurnOrder() {
	//Clear any previous turn order. 
	mTurnOrder.clear(); 

	//Add all combat participants. 
	mTurnOrder.push_back(CombatTurn::OraKanu); 
	mTurnOrder.push_back(CombatTurn::MBatha); 
	mTurnOrder.push_back(CombatTurn::Enemy); 

	//Create random number generator. 
	std::random_device rd; 
	std::mt19937 generator(rd()); 

	//Randomize turn order once per battle. 
	std::shuffle(mTurnOrder.begin(), mTurnOrder.end(), generator);
}

//Calculate Damage. 
int CombatSystem::CalculateDamage(int Attack, int Defense) {
	//Subtract targets defense from attack. 
	int Damage = Attack - Defense; 

	//Every successful attack deals at least 1 damage. 
	if (Damage < 1) {
		Damage = 1; 
	}
	return Damage; 
}

//Player turn
void CombatSystem::PlayerTurn(Character& Character, Enemy& Enemy) {
	//Defeated characters cannot attack. 
	if (Character.GetHP() <= 0) {
		return; 
	}

	std::cout << "\n=================================================================\n"; 
	std::cout << Character.GetName() << "'s Turn\n"; 
	std::cout << "\n=================================================================\n"; 

	std::cout << "HP: " << Character.GetHP() << "\n"; 
	std::cout << "Ase: " << Character.GetAse() << "\n"; 

	//Temporary basic combat menu. 
	std::cout << "\n1. Attack\n"; 
	std::cout << "Choose an Action: "; 

	std::string input; 

	//Only attack is available in this first version. 
	while (true) {
		if (!std::getline(std::cin, input)) {
			return; 
		}
		if (input == "1") {
			break; 
		}
		std::cout << "Invalid choice. Enter 1: "; 
	}
	//Calculate basica attack damage. 
	int Damage = CalculateDamage(Character.GetAttack(), Enemy.GetDefense());

	//Apply damage to the enemy. 
	Enemy.SetHP(Enemy.GetHP() - Damage); 

	std::cout << "\n" << Character.GetName() << " attacks " << Enemy.GetName() << " for " << Damage << " damage!\n"; 

	std::cout << " HP: " << Enemy.GetHP() << "\n"; 
}

//Enemy turn. 
void CombatSystem::EnemyTurn(Enemy& Enemy, Character& OraKanu, Character& MBatha) {
	//A defeated enemy cannot attack. 
	if (Enemy.GetHP() <= 0) {
		return; 
	}
	std::cout << "\n=================================================================\n";
	std::cout << Enemy.GetName() << "'s Turn\n";
	std::cout << "\n=================================================================\n";

	//Build a list of living targets. 
	std::vector<Character*> Targets; 

	if (OraKanu.GetHP() > 0) {
		Targets.push_back(&OraKanu); 
	}
	if (MBatha.GetHP() > 0) {
		Targets.push_back(&MBatha); 
	}
	//No living targets means the party is defeated. 
	if (Targets.empty()) {
		return; 
	}
	//Choose a random living target.
	static std::mt19937 generator(std::random_device{}());		

	std::uniform_int_distribution<int> distribution(
		0,
		static_cast<int>(Targets.size()) - 1
	);

	Character* Target = Targets[distribution(generator)]; 

	//Calculate damage against the chosen character. 
	int Damage = CalculateDamage(Enemy.GetAttack(), Target->GetDefense()); 

	//Apply damage to the target. 
	Target->SetHP(Target->GetHP() - Damage); 

	std::cout << "\n" << Enemy.GetName() << " attacks " << Target->GetName() << " for " << Damage << " damage!\n"; 

	std::cout << Target->GetName() << "HP: " << Target->GetHP() << "\n"; 
}
//Check party defeat.
bool CombatSystem::IsPartyDefeated(const Character& OraKanu, const Character& MBatha) const {
	//Both characters must be defeated. 
	return OraKanu.GetHP() <= 0 && MBatha.GetHP() <= 0; 
}

//Start combat. 
CombatResult CombatSystem::StartCombat(Character& OraKanu, Character& MBatha, Enemy& Enemy) {

	std::cout << "\n=================================================================\n";
	std::cout <<                             "Combat Start"; 
	std::cout << "\n=================================================================\n";

	std::cout << "\nA " << Enemy.GetName() << " appears!\n"; 

	//Determine turn order once per battle. 
	CreateTurnOrder(); 

	//Display randomized turn order. 
	std::cout << "\nTurn Order: \n"; 

	for (CombatTurn Turn : mTurnOrder) {
		switch (Turn) {
		case CombatTurn::OraKanu:
			std::cout << "- " << OraKanu.GetName() << "\n"; 
			break; 

		case CombatTurn::MBatha: 
			std::cout << "- " << MBatha.GetName() << "\n"; 
			break;

		case CombatTurn::Enemy: 
			std::cout << "- " << Enemy.GetName() << "\n"; 
			break;
		}
	}
	int round = 1; 

	//Continue until either the enemy or the party is defeated. 
	while (Enemy.GetHP() > 0 && !IsPartyDefeated(OraKanu, MBatha)) {
		std::cout << "\n=================================\n";
		std::cout << "             ROUND " << round << "\n";
		std::cout << "=================================\n";

	//Process combatants in their turn order. 
		for (CombatTurn Turn : mTurnOrder) {
			//End the round immediately if combat is over. 
			if (Enemy.GetHP() <= 0 || IsPartyDefeated(OraKanu, MBatha)) {
				break;
			}
			switch (Turn) {
			case CombatTurn::OraKanu: PlayerTurn(OraKanu, Enemy); 
				break;

			case CombatTurn::MBatha: PlayerTurn(MBatha, Enemy); 
				break; 

			case CombatTurn::Enemy: EnemyTurn(Enemy, OraKanu, MBatha);
				break;
			}
		}
		//Advance to the next round. 
		++round; 
	}

	//Determine the combat result. 
	if (Enemy.GetHP() <= 0)
	{
		std::cout << "\n=================================\n";
		std::cout << "             VICTORY!            \n";
		std::cout << "=================================\n";

		return CombatResult::Victory;
	}

	std::cout << "\n=================================\n";
	std::cout << "              DEFEAT             \n";
	std::cout << "=================================\n";

	return CombatResult::Defeat;
}