#include <algorithm> //Needed for std::shuffle
#include <random> //Needed for random number generation.
#include <limits>
#include <iostream>
#include <string> 

#include "CombatSystem.h"
#include "ItemManager.h"
#include "Menu.h"

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
void CombatSystem::PlayerTurn(Character& activeCharacter, Enemy& enemy, Inventory& Inventory, Character& OraKanu, Character& Mbatha)
{
    //Defeated characters cannot attack.
    if (activeCharacter.GetHP() <= 0)
    {
        return;
    }
    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n+----------------------------------------------------------+\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "  " << activeCharacter.GetName() << " - COMMAND\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "+----------------------------------------------------------+\n";

    Menu::SetTextColor(Menu::IVORY);
    std::cout << "  HP: " << activeCharacter.GetHP()
        << "/" << activeCharacter.GetMaxHP()
        << "    Ase: " << activeCharacter.GetAse() << "\n";

    //Retrieve the character's learned abilities.
    const std::vector<Ability>& abilities = activeCharacter.GetAbilities();

    while (true) {
        Menu::SetTextColor(Menu::GREEN);
        std::cout << "------------------------------------------------------------\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "  1. Attack\n";

        // Display learned abilities dynamically.
        for (size_t i = 0; i < abilities.size(); ++i)
        {
            std::cout << "  " << i + 2 << ". "
                << abilities[i].GetAbilityName()
                << " (Ase: " << abilities[i].GetAseCost() << ")\n";
        }

        // Keep Item's number after all learned abilities.
        int itemChoice = static_cast<int>(abilities.size()) + 2;

        std::cout << "  " << itemChoice << ". Item\n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "+----------------------------------------------------------+\n";

        Menu::SetTextColor(Menu::GOLD);
        std::cout << "  Choose an Action: ";

        Menu::SetTextColor(Menu::IVORY);
        std::string input;
        int choice = -1;

        //Validate the player's combat selection.
        while (true)
        {
            if (!std::getline(std::cin, input)) {
                return;
            }

            try {
                size_t position = 0;
                choice = std::stoi(input, &position);

                if (position == input.length() && choice >= 1 && choice <= itemChoice) {
                    //v.03 Check whether the selected ability cost to much Ase. 
                    if (choice > 1 && choice < itemChoice) {
                        const Ability& selectedAbility = abilities[choice - 2];

                        if (activeCharacter.GetAse() < selectedAbility.GetAseCost()) {
                            std::cout << "Not enough Ase to use this ability." << selectedAbility.GetAbilityName() << "!\n";
                            std::cout << "Choose another action: ";
                            continue;
                        }
                    }
                    break;
                }
            }
            catch (const std::invalid_argument&) {
                //Invalid input handled below.
            }
            catch (const std::out_of_range&) {
                //Invalid input handled below.
            }

            std::cout << "Invalid choice. Please try again: ";
        }

        //=========================================
        // Basic Attack
        //=========================================
        if (choice == 1)
        {
            int Damage = CalculateDamage(
                activeCharacter.GetAttack(),
                enemy.GetDefense()
            );

            enemy.SetHP(enemy.GetHP() - Damage);

            // =========================================
            // CLASSIC RPG BATTLE MESSAGE WINDOW
            // =========================================

            Menu::SetTextColor(Menu::GREEN);
            std::cout << "\n+----------------------------------------------------------+\n";

            Menu::SetTextColor(Menu::GOLD);
            std::cout << "                      BATTLE LOG\n";

            Menu::SetTextColor(Menu::GREEN);
            std::cout << "+----------------------------------------------------------+\n";

            Menu::SetTextColor(Menu::IVORY);
            std::cout << "  " << activeCharacter.GetName()
                << " attacks " << enemy.GetName() << "!\n";

            Menu::SetTextColor(Menu::RED);
            std::cout << "  " << enemy.GetName()
                << " takes " << Damage << " damage!\n";

            Menu::SetTextColor(Menu::IVORY);
            std::cout << "  Enemy HP: " << std::max(0, enemy.GetHP()) << "\n";

            Menu::SetTextColor(Menu::GREEN);
            std::cout << "+----------------------------------------------------------+\n";

            Menu::SetTextColor(Menu::IVORY);
        }

        //=========================================
        // Item Usage
        // ========================================
        else if (choice == itemChoice)
        {
            bool itemUsed = ItemManager::UseItemInCombat(Inventory, OraKanu, Mbatha);

            if (itemUsed)
            {
                return; // Item used successfully. End turn.
            }

            // Cancelled or invalid item.
            // Return to the combat action menu.
            continue;
        }

        //=========================================
        // Ability Attack
        //=========================================
        else
        {
            int abilityIndex = choice - 2;

            const Ability& selectedAbility = abilities[abilityIndex];

            //Deduct Ase cost.
            activeCharacter.SetAse(
                activeCharacter.GetAse() - selectedAbility.GetAseCost()
            );

            // =========================================
            // ABILITY BATTLE MESSAGE WINDOW
            // =========================================

            Menu::SetTextColor(Menu::GREEN);
            std::cout << "\n+----------------------------------------------------------+\n";

            Menu::SetTextColor(Menu::GOLD);
            std::cout << "                      ABILITY USED\n";

            Menu::SetTextColor(Menu::GREEN);
            std::cout << "+----------------------------------------------------------+\n";

            Menu::SetTextColor(Menu::IVORY);
            std::cout << "  " << activeCharacter.GetName() << " uses ";

            Menu::SetTextColor(Menu::GOLD);
            std::cout << selectedAbility.GetAbilityName() << "!\n";

            Menu::SetTextColor(Menu::GREEN);
            std::cout << "+----------------------------------------------------------+\n";

            Menu::SetTextColor(Menu::IVORY);
            //============================
            //v.04 Healing Rain 
            //============================
            if (selectedAbility.GetAbilityName() == "Healing Rain")
            {
                const int HealingAmount = selectedAbility.GetAbilityPower();

                Menu::SetTextColor(Menu::GOLD);
                std::cout << "\n                  HEALING RAIN\n";

                Menu::SetTextColor(Menu::GREEN);
                std::cout << "------------------------------------------------------------\n";

                // Heal Ora'Kanu without exceeding maximum HP.
                if (OraKanu.GetHP() > 0)
                {
                    int missingHP = OraKanu.GetMaxHP() - OraKanu.GetHP();
                    int actualHealing = std::min(HealingAmount, missingHP);

                    Menu::SetTextColor(Menu::GREEN);
                    std::cout << "  " << OraKanu.GetName()
                        << " restores " << actualHealing << " HP!\n";
                }

                // Heal M'Batha without exceeding maximum HP.
                if (Mbatha.GetHP() > 0)
                {
                    int missingHP = Mbatha.GetMaxHP() - Mbatha.GetHP();
                    int actualHealing = std::min(HealingAmount, missingHP);

                    Menu::SetTextColor(Menu::GREEN);
                    std::cout << "  " << Mbatha.GetName()
                        << " restores " << actualHealing << " HP!\n";
                }

                Menu::SetTextColor(Menu::GOLD);
                std::cout << "\n  " << activeCharacter.GetName()
                    << " Ase: " << activeCharacter.GetAse() << "\n";

                // Close the ability battle window.
                Menu::SetTextColor(Menu::GREEN);
                std::cout << "+----------------------------------------------------------+\n";

                Menu::SetTextColor(Menu::IVORY);

                return; // Healing Rain ends the character's turn.
            }

            //=========================================
            // Status Effect Application
            //=========================================
            if (enemy.GetStatus() == AbilityStatus::Wet)
            {
                Menu::SetTextColor(Menu::GREEN);
                std::cout << "\n  " << enemy.GetName() << " is now ";

                Menu::SetTextColor(Menu::IVORY);
                std::cout << "WET!\n";
            }
            else if (enemy.GetStatus() == AbilityStatus::Stun)
            {
                Menu::SetTextColor(Menu::GOLD);
                std::cout << "\n  " << enemy.GetName()
                    << " has been STUNNED!\n";
            }
            else if (enemy.GetStatus() == AbilityStatus::Poison)
            {
                Menu::SetTextColor(Menu::GREEN);
                std::cout << "\n  " << enemy.GetName()
                    << " has been POISONED!\n";
            }
            else if (enemy.GetStatus() == AbilityStatus::Bleed)
            {
                Menu::SetTextColor(Menu::RED);
                std::cout << "\n  " << enemy.GetName()
                    << " is now BLEEDING!\n";
            }

            // Always restore the default color.
            Menu::SetTextColor(Menu::IVORY);

            //=========================================
            // Ability Damage
            //=========================================
            int Damage = 0;

            //Zero-power abilities like Raincall deal no direct damage.
            if (selectedAbility.GetAbilityPower() > 0)
            {
                Damage = CalculateDamage(
                    activeCharacter.GetAttack() + selectedAbility.GetAbilityPower(),
                    enemy.GetDefense()
                );

                //Apply additional damage against Wet enemies.
                if (selectedAbility.GetWetDmg() &&
                    enemy.GetStatus() == AbilityStatus::Wet)
                {
                    //Temporary 50% damage bonus.
                    int wetBonus = Damage / 2;

                    Damage += wetBonus;

                    std::cout << "\nThe Wet status amplifies the attack!\n";
                }

                enemy.SetHP(enemy.GetHP() - Damage);
            }

            if (Damage > 0)
            {
                Menu::SetTextColor(Menu::RED);
                std::cout << "\n  " << enemy.GetName()
                    << " takes " << Damage << " damage!\n";

                Menu::SetTextColor(Menu::IVORY);
                std::cout << "  Enemy HP: "
                    << std::max(0, enemy.GetHP()) << "\n";
            }

            // Display remaining Ase.
            Menu::SetTextColor(Menu::GOLD);
            std::cout << "  " << activeCharacter.GetName()
                << " Ase: " << activeCharacter.GetAse() << "\n";

            // Close the ability results window.
            Menu::SetTextColor(Menu::GREEN);
            std::cout << "+----------------------------------------------------------+\n";

            Menu::SetTextColor(Menu::IVORY);
        }
        return;
    }
}
//Enemy turn. 
void CombatSystem::EnemyTurn(Enemy& Enemy, Character& OraKanu, Character& MBatha) {

	//A defeated enemy cannot attack. 
	if (Enemy.GetHP() <= 0) {
		return; 
	}
    //==========================
    //      Stunned Status
    //========================== 
    
    //Check whether the enemy is stunned. 
    if (Enemy.GetStatus() == AbilityStatus::Stun) {
        std::cout << "\n" << Enemy.GetName() << " is stunned and cannot attack!\n"; 

        //Stun lasts for one skipped turn. 
        Enemy.SetStatus(AbilityStatus::None); 

        return; 
    }

    //===========================
    //      Poison Status
    //===========================
    //Check whether the enemy is poisoned. 

    if (Enemy.GetStatus() == AbilityStatus::Poison) {
        //Poison deals 3 damage at the start of the enemies turn. 
        const int PoisonDamage = 3; 

        Enemy.SetHP(Enemy.GetHP() - PoisonDamage); 

        std::cout << "\n" << Enemy.GetName() << " suffers " << PoisonDamage << " poison damage!\n"; 

        std::cout << Enemy.GetName() << " HP: " << Enemy.GetHP() << "\n"; 

        //If poison defeats the enemy it cannot attack. 
        if (Enemy.GetHP() <= 0) {

            std::cout << "\n" << Enemy.GetName() << " has fallen to poison.\n"; 

            return; 
        }

    //============================
    //      Bleed Status
    //============================

        if (Enemy.GetStatus() == AbilityStatus::Bleed) {
        //Bleed damage deals 5 damage at the start of the enemy's turn. 
            const int BleedDamage = 5; 

            Enemy.SetHP(Enemy.GetHP() - BleedDamage); 

            std::cout << "\n" << Enemy.GetName() << " suffers " << BleedDamage << " Bleed Damage!\n"; 

            std::cout << Enemy.GetName() << " HP: " << Enemy.GetHP() << "\n"; 

            //If bleed defeats the enemy, it cannot attack. 
            if (Enemy.GetHP() <= 0) {
                std::cout << "\n" << Enemy.GetName() << " has fallen from blood loss!\n"; 

                return; 
            }
    }
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

    //Get the enemy's available abilities.
    const std::vector<Ability>& abilities = Enemy.GetAbilities();

    //0 = Basic Attack.
    //1 or higher = An ability.
    int action = 0;

    if (!abilities.empty())
    {
        std::uniform_int_distribution<int> actionDistribution(
            0,
            static_cast<int>(abilities.size())
        );

        action = actionDistribution(generator);
    }

    if (action == 0)
    {
        // Calculate and apply damage.
        int Damage = CalculateDamage(
            Enemy.GetAttack(),
            Target->GetDefense()
        );

        Target->SetHP(Target->GetHP() - Damage);

        // =========================================
        // ENEMY BASIC ATTACK BATTLE WINDOW
        // =========================================

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "\n+----------------------------------------------------------+\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "                     ENEMY ATTACK\n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "+----------------------------------------------------------+\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "  " << Enemy.GetName()
            << " attacks " << Target->GetName() << "!\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "  " << Target->GetName()
            << " takes " << Damage << " damage!\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "  Remaining HP: "
            << std::max(0, Target->GetHP()) << "\n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "+----------------------------------------------------------+\n";

        Menu::SetTextColor(Menu::IVORY);
    }
    else
    {
        const Ability& selectedAbility = abilities[action - 1];
        // =========================================
 // ENEMY ABILITY BATTLE WINDOW
 // =========================================

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "\n+----------------------------------------------------------+\n";

        Menu::SetTextColor(Menu::RED);
        std::cout << "                     ENEMY ABILITY\n";

        Menu::SetTextColor(Menu::GREEN);
        std::cout << "+----------------------------------------------------------+\n";

        Menu::SetTextColor(Menu::IVORY);
        std::cout << "  " << Enemy.GetName() << " uses ";

        Menu::SetTextColor(Menu::GOLD);
        std::cout << selectedAbility.GetAbilityName() << "!\n";

        Menu::SetTextColor(Menu::IVORY);

        //Calculate ability damage.
        int Damage = 0;

        if (selectedAbility.GetAbilityPower() > 0)
        {
            Damage = CalculateDamage(
                Enemy.GetAttack() + selectedAbility.GetAbilityPower(),
                Target->GetDefense()
            );

            //Apply bonus damage against Wet targets.
            if (selectedAbility.GetWetDmg() &&
                Target->GetStatus() == AbilityStatus::Wet)
            {
                Damage += Damage / 2;
            }

            Target->SetHP(Target->GetHP() - Damage);

            Menu::SetTextColor(Menu::RED);
            std::cout << "  " << Target->GetName()
                << " takes " << Damage << " damage!\n";

            Menu::SetTextColor(Menu::IVORY);
        }

        //Attempt to apply a status effect.
        if (selectedAbility.GetStatusEffect() != AbilityStatus::None &&
            Target->GetHP() > 0)
        {
            std::uniform_int_distribution<int> statusRoll(1, 100);

            if (statusRoll(generator) <= selectedAbility.GetStatusChance())
            {
                Target->SetStatus(selectedAbility.GetStatusEffect());

                Menu::SetTextColor(Menu::GOLD);
                std::cout << "  " << Target->GetName()
                    << " has been afflicted with a status effect!\n";

                Menu::SetTextColor(Menu::IVORY);
                Menu::SetTextColor(Menu::GREEN);
                std::cout << "+----------------------------------------------------------+\n";

                Menu::SetTextColor(Menu::IVORY);
            }
        }
    }
    //Display the target's remaining HP.
    std::cout << Target->GetName()
        << " HP: " << Target->GetHP() << "\n";
}

//Check party defeat.
bool CombatSystem::IsPartyDefeated(
    const Character& OraKanu,
    const Character& MBatha) const
{
    return OraKanu.GetHP() <= 0 && MBatha.GetHP() <= 0;
}
//Start combat. 
CombatResult CombatSystem::StartCombat(Character& OraKanu, Character& MBatha, Enemy& Enemy, Inventory& Inventory) {

    //Reset the status effects at the beginning of combat so statuses do not carry over from one to the next. 
    OraKanu.SetStatus(AbilityStatus::None);
    MBatha.SetStatus(AbilityStatus::None); 
    Enemy.SetStatus(AbilityStatus::None); 

    
    //Display the combat screen heading.
        Menu::ClearScreen();

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "\n============================================================\n";

    Menu::SetTextColor(Menu::GOLD);
    std::cout << "                 FIRST FANTASY: COMBAT\n";

    Menu::SetTextColor(Menu::GREEN);
    std::cout << "============================================================\n";

    // Display the enemy encounter.
    Menu::SetTextColor(Menu::RED);
    std::cout << "\n              [ " << Enemy.GetName() << " ]\n";

    Menu::SetTextColor(Menu::IVORY);
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

    while (Enemy.GetHP() > 0 && !IsPartyDefeated(OraKanu, MBatha))
    {
        // Process combatants in their turn order.
        for (CombatTurn Turn : mTurnOrder)
        {
            if (Enemy.GetHP() <= 0 || IsPartyDefeated(OraKanu, MBatha))
            {
                break;
            }

            // Your existing battlefield redraw code goes HERE.
            // Keep lines 709–747 exactly as they are.

            switch (Turn)
            {
            case CombatTurn::OraKanu:
                PlayerTurn(OraKanu, Enemy, Inventory, OraKanu, MBatha);
                break;

            case CombatTurn::MBatha:
                PlayerTurn(MBatha, Enemy, Inventory, OraKanu, MBatha);
                break;

            case CombatTurn::Enemy:
                EnemyTurn(Enemy, OraKanu, MBatha);
                break;
            }

            Menu::SetTextColor(Menu::GOLD);
            std::cout << "\nPress ENTER for the next turn...";

            Menu::SetTextColor(Menu::IVORY);

            std::string turnInput;
            std::getline(std::cin, turnInput);

        } // Closes the FOR loop

        ++round;

    } // Closes the WHILE loop

    // Victory and defeat checks remain INSIDE StartCombat().
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

} // Closes StartCombat()