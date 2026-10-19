#pragma once

#include <string> 
#include <vector>

#include "Ability.h"

class Enemy {
public:
	//Default constructor. 
	Enemy(); 

	//Overloaded constructor. 
	Enemy(std::string Name, int MaxHP, int Attack, int Defense); 

	//Getters. 
	std::string GetName() const; 

	int GetHP() const; 
	int GetMaxHP() const; 

	int GetAttack() const; 

	int GetDefense() const; 

	void SetHP(int EHP); 

	//v.03 Returns an enemies current status. 
	AbilityStatus GetStatus() const; 

	//v.03 Sets ability status. 
	void SetStatus(AbilityStatus Status); 

	//Method to display enemy stats.
	void DisplayStats() const; 

	//Methods/Vector for enemy abilities to support combat system. 
	void AddAbility(const Ability& NewAbility); 

	const std::vector<Ability>& GetAbilities() const; 

private:
	//Enemy name.
	std::string mName; 

	//Health.
	int mHP; 
	int mMaxHP; 

	//Attack/Defense stats. 
	int mAttack; 
	int mDefense; 

	//Vector for enemy abilities. 
	std::vector<Ability> mAbilities; 

	//v.03 Currnet status effect applied to this enemy. 
	AbilityStatus mStatus = AbilityStatus::None;
};