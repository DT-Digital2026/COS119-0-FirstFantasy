#pragma once

#include "Ability.h"

//The ability catalog will contain all abilities in the game, player and enemy.
class AbilityCatalog {
public:
	//Default constructor. 
	AbilityCatalog(); 

	//===========================
	//Character Abilities
	//===========================

	//Ora'Kanu - Abilities
	Ability Raincall(); //Calls down rain, inflicting the 'wet' status. 
	Ability LightningStrike(); //Strikes the enemy with lightning, does extra damage if 'wet' status is applied. 
	Ability ThunderClap(); //Uses a thunderous blast with a chance to stun the enemy. 
	Ability Tempest(); //Summons a devastating storm to overwhelm the enemy.

	//M'Batha - Abilities
	Ability Jab(); //Delivers a quick strike to the enemy. Opens combos. 
	Ability SpearStrike(); //Spear hand strike that delivers a forceful blow.
	Ability StunningBlow(); //Heavy strike with a chance to stun the enemy. 
	Ability ChampionCombo(); //Unleash a devastating combo on the enemy. 

	//===========================
	//Enemy Abilities
	//===========================

	//Venomous Snake
	Ability VenomousStrike(); //Quick bite that has a chance to poison.
	Ability CoiledLunge(); //Coils tightly before delivering a powerful attack.

	//Bat
	Ability DivingBite(); //Dives from above to bite the enemy.
	Ability WingBuffet(); //Beats its wings forcefully against the enemy.

	//Hyena
	Ability SavageLunge(); //Lunges forward with a viscious attack.
	Ability RendingBite(); //Tears into the target with powerful jaws. 

	//Leopard
	Ability Pounce(); //Leaps suddenly onto the target with crushing force.
	Ability RakingClaws(); //Rakes the target with a series of clawing strikes.

	//Crocodile
	Ability CrushingBite(); //Crushing bite with its powerful jaws. 
	Ability TailSweep(); //Sweeps its powerful tail with a chance to stun the enemy. 

	//Vampire Bat
	Ability BloodDrain(); //Sinks its fangs into the target to drain their blood.
	Ability Screech(); //Releases a piercing shriek with a chance to stun the target. 

	//Bat Swarm
	Ability SwarmAssault(); //The swarm decends upon the target from all directions.
	Ability FrenziedBites(); //The swarm erupts into a frenzy of snapping fangs. 

	//Bonsam Thrall
	Ability FrenziedStrike(); //Attacks wildly with little regard for its own safety. 
	Ability BloodFrenzy(); //Gives into its hunger and launches into a viscious assault.

	//Bonsam
	Ability BloodClaw(); //Tears into the target with blood soaked claws. 
	Ability DarkHunger(); //Channels its hunger into a powerful attack. 

	//===========================
	//Boss Abilities
	//===========================

	//Bonsam Elder
	Ability EldersWrath(); //Unleashes the ancient fury of the bonsam upon the target. 
	Ability BloodRitual(); //Invokes a dark blood right against the target.

private: 
};