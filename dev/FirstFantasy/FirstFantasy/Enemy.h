#pragma once

#include <string> 

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

	//Method to display enemy stats.
	void DisplayStats() const; 

private:
	//Enemy name.
	std::string mName; 

	//Health.
	int mHP; 
	int mMaxHP; 

	//Attack/Defense stats. 
	int mAttack; 
	int mDefense; 
};