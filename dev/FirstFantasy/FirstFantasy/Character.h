#pragma once

#include <string>

class Character {
public: 
	void DisplayStats() const;	

	//Default constructor.
	Character();

	//Overloaded constructor used to create a character with starting stats. 
	Character(const std::string& Name, const std::string& Title, int maxHP, int maxAse, int Attack, int Defense);

	//Getters. 
	std::string GetName() const; 
	std::string GetTitle() const; 

	int GetLevel() const; 

	int GetHP() const; 
	int GetMaxHP() const; 

	int GetAse() const; 
	int GetMaxAse() const; 

	int GetAttack() const; 
	int GetDefense() const; 

	//Setters
	void SetHP(int HP); 
	void SetAse(int Ase); 

private: 
	//Character Infromation.
	std::string mName; 
	std::string mTitle; 

	//Character Level. 
	int mLevel; 

	//Health.
	int mHP; 
	int mMaxHP; 

	//Ase. 
	int mAse; 
	int mMaxAse; 

	//Combat Statistics. 
	int mAttack; 
	int mDefense; 
};