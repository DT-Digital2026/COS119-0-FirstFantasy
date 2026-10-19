#include <iostream>
#include <string>

#include "Enemy.h"

//Building the default constructor. 
Enemy::Enemy() {
	//Enemy Name.
	mName = ""; 
	
	//Enemy Health.
	mHP = 0;
	mMaxHP = 0; 

	//Enemy attack/defense.
	mAttack = 0; 
	mDefense = 0; 
}
//Building overloaded constructor. 
Enemy::Enemy(std::string Name, int MaxHP, int Attack, int Defense) {
	//Enemy Information. 
	mName = Name;

	//Enemy Health.
	mMaxHP = MaxHP;
	mHP = mMaxHP;

	//Attack/Defense.
	mAttack = Attack;
	mDefense = Defense;
}

//Implementing vectors for enemy abilities. 
void Enemy::AddAbility(const Ability& NewAbility) {
	mAbilities.push_back(NewAbility); 
}

const std::vector<Ability>& Enemy::GetAbilities() const {
	return mAbilities; 
}

//Enemy getters. 
std::string Enemy::GetName() const {
	return mName;
}

int Enemy::GetHP() const {
	return mHP;
}

int Enemy::GetMaxHP() const {
	return mMaxHP;
}

int Enemy::GetAttack() const {
	return mAttack;
}

int Enemy::GetDefense() const {
	return mDefense;
}

//Current status effect applied to this enemy. 
AbilityStatus Enemy::GetStatus() const {
	return mStatus;
}

//Enemy setters. 
void Enemy::SetHP(int HP)
{
	if (HP < 0)
	{
		mHP = 0;
	}
	else if (HP > mMaxHP)
	{
		mHP = mMaxHP;
	}
	else
	{
		mHP = HP;
	}
}

//Applies a status effect to the enemy. 
void Enemy::SetStatus(AbilityStatus Status) {
	mStatus = Status; 
}

void Enemy::DisplayStats() const {
	std::cout << "Name: " << mName << std::endl;
	std::cout << "HP: " << mHP << "/" << mMaxHP << std::endl;
	std::cout << "Attack: " << mAttack << std::endl;
	std::cout << "Defense: " << mDefense << std::endl;
}