#include <iostream>
#include <string> 

#include "Character.h"

//Building default constructor.
Character::Character() {
	//Character Infromation.
	mName = ""; 
	mTitle = ""; 

	mLevel = 1; 

	//Character Health.
	mHP = 0; 
	mMaxHP = 0; 

	//Character Ase. 
	mAse = 0; 
	mMaxAse = 0; 

	//Attack/Defense.
	mAttack = 0; 
	mDefense = 0; 
}
//Built overloaded constructor. 
Character::Character(const std::string& Name, const std::string& Title, int maxHP, int maxAse, int Attack, int Defense) {
	//Character Information. 
	mName = Name; 
	mTitle = Title; 
	mLevel = 1; 

	//Character Health.
	mMaxHP = maxHP; 
	mHP = mMaxHP; 

	//Character Ase.
	mMaxAse = maxAse; 
	mAse = mMaxAse; 

	//Attack/Defense.
	mAttack = Attack; 
	mDefense = Defense; 
}

//Character getters. 
std::string Character::GetName() const {
	return mName; 
}
std::string Character::GetTitle() const {
	return mTitle; 
}

int Character::GetLevel() const {
	return mLevel; 
}

int Character::GetHP() const {
	return mHP; 
}

int Character::GetMaxHP() const{
	return mMaxHP; 
}

int Character::GetAse() const{
	return mAse; 
}

int Character::GetMaxAse() const{
	return mMaxAse; 
}

int Character::GetAttack() const {
	return mAttack;
}

int Character::GetDefense() const{
	return mDefense; 
}

//Character setters. 
void Character::SetHP(int HP)
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
void Character::SetAse(int Ase) {
	if (Ase < 0)
	{
		mAse = 0;
	}
	else if (Ase > mMaxAse)
	{
		mAse = mMaxAse;
	}
	else
	{
		mAse = Ase;
	}
}

	void Character::DisplayStats() const {
		std::cout << "Name: " << mName << std::endl;
		std::cout << "Title: " << mTitle << std::endl;
		std::cout << "Level: " << mLevel << std::endl;
		std::cout << "HP: " << mHP << "/" << mMaxHP << std::endl;
		std::cout << "Ase: " << mAse << "/" << mMaxAse << std::endl;
		std::cout << "Attack: " << mAttack << std::endl;
		std::cout << "Defense: " << mDefense << std::endl;
	}