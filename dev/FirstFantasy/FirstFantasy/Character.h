#pragma once

#include <string>
#include <vector>

#include"Ability.h"
#include "Item.h"

class Character {
public: 
	//Method to display character stats. 
	void DisplayStats() const;	

	//Default constructor.
	Character();

	//Overloaded constructor used to create a character with starting stats. 
	Character(const std::string& Name, const std::string& Title, int maxHP, int maxAse, int Attack, int Defense);

	// Adds a new ability to the character.
	void AddAbility(const Ability& ability);

	// Returns the character's learned abilities.
	// Const reference prevents unnecessary copying.
	const std::vector<Ability>& GetAbilities() const;

	// Displays the character's learned abilities.
	void DisplayAbilities() const;

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

	//v.04 Equipment System
	//Equip a weapon or armor piece. 
	bool EquipItem(const Item& item); 

	//v.04 Return the currently equipped weapon and armor.
	const Item* GetEquippedWeapon() const; 
	const Item* GetEquippedArmor() const; 

	AbilityStatus GetStatus() const; 

	//Setters
	void SetHP(int HP); 
	void SetAse(int Ase); 
	void SetStatus(AbilityStatus Status); 

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

	// Stores all abilities learned by the character.
	std::vector<Ability> mAbilities;

	//Setting up so that enemy abilities can afflict players with status effects. 
	AbilityStatus mStatus = AbilityStatus::None; 

	//v.04 Equipment slots. 
	//Each character one weapon and one armor piece. 
	Item mEquippedWeapon; 
	Item mEquippedArmor; 

	bool mHasWeapon = false; 
	bool mHasArmor = false; 
};