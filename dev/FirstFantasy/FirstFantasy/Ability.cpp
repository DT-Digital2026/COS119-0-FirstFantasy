#include "Ability.h"

//Building the default constructor. 
Ability::Ability() {
	//Ability Name.
	mAbilityName = ""; 

	//Ability Description.
	mAbilityDescription = ""; 

	//Ase Costs.
	mAseCost = 0;

	//Ability Power. 
	mAbilityPower = 0; 

	//Applies Wet. 
	AbilityStatus mStatusEffect; 

	//Wet damage bonus. 
	mWetDmg = false; 

	//Stun chance. 
	mStatusChance = 0; 
}

//Overloaded Constructor. 
Ability::Ability(const std::string& AbilityName, const std::string& AbilityDescription, int AseCost, int AbilityPower,
	AbilityStatus StatusEffect, bool WetDmg, int StatusChance) {

	mAbilityName = AbilityName;

	mAbilityDescription = AbilityDescription;

	mAseCost = AseCost;

	mAbilityPower = AbilityPower;

	mStatusEffect = StatusEffect;

	mWetDmg = WetDmg;

	mStatusChance = StatusChance;
}

	//Ability Getters.
	std::string Ability::GetAbilityName() const {
		return mAbilityName;
	}

	std::string Ability::GetAbilityDescription() const {
		return mAbilityDescription;
	}

	int Ability::GetAseCost() const {
		return mAseCost;
	}

	int Ability::GetAbilityPower() const {
		return mAbilityPower;
	}

	AbilityStatus Ability::GetStatusEffect() const {
		return mStatusEffect;
	}

	bool Ability::GetWetDmg() const {
		return mWetDmg; 
	}

	int Ability::GetStatusChance() const {
		return mStatusChance;
	}
