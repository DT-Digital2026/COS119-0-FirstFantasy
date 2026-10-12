#pragma once

#include <string>

//Status effects that can be applied by abilities. 
enum class AbilityStatus {
	None, 
	Wet, 
	Stun, 
	Poison, 
	Bleed
};
//Class creation. 
class Ability {
public:
	//Default constructor. 
	Ability(); 

	//Overloaded constructor. 
	Ability(const std::string& AbilityName, const std::string& AbilityDescription, int AseCost, int AbilityPower,
		AbilityStatus StatusEffect, bool WetDmg, int StatusChance); 

	//Getters
	std::string GetAbilityName() const; 

	std::string GetAbilityDescription() const; 

	int GetAseCost() const; 

	int GetAbilityPower() const; 

	AbilityStatus GetStatusEffect() const; 

	bool GetWetDmg() const; 

	int GetStatusChance() const;

private:
	std::string mAbilityName; 

	std::string mAbilityDescription; 

	int mAseCost; 

	int mAbilityPower; 

	AbilityStatus mStatusEffect; 

	bool mWetDmg; 

	int mStatusChance; 
};
