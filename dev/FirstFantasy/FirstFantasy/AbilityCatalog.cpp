#include "AbilityCatalog.h"

//Default constructor. 
AbilityCatalog::AbilityCatalog() {

}

//===========================
// Character Abilities
//===========================

//Ora'Kanu Abilities
Ability AbilityCatalog::Raincall() {
	Ability Ability("Raincall", "Calls the rains, inflicts Wet status.", 5, 0, AbilityStatus::Wet, false, 100);
	return Ability; 
}

Ability AbilityCatalog::LightningStrike() {
	Ability Ability("Lightning Strike", "Strikes the enemy with lightning, does extra damage if 'wet' status is applied.", 8, 15, AbilityStatus::None, true, 0);
	return Ability;
}

Ability AbilityCatalog::HealingRain() {
	Ability Ability("Healing Rain", "Calls on a calming rain to lightly heal the characters. ", 10, 18, AbilityStatus::None, false, 0);
	return Ability;
}

Ability AbilityCatalog::Tempest() {
	Ability Ability("Tempest", "Summons a devastating storm to overwhelm the enemy.", 18, 25, AbilityStatus::None, true, 0);
	return Ability;
}

//M'Batha Abilities
Ability AbilityCatalog::Jab() {
	Ability Ability("Jab", "Delivers a quick strike to the enemy. Opens combos. ", 0, 8, AbilityStatus::None, false, 0);
	return Ability;
}

Ability AbilityCatalog::SpearStrike() {
	Ability Ability("Spear Hand Strike", "Spear hand strike that delivers a forceful blow.", 4, 14, AbilityStatus::None, false, 0);
	return Ability;
}

Ability AbilityCatalog::StunningBlow() {
	Ability Ability("Stunning Blow", "Heavy strike with a chance to stun the enemy. ", 7, 12, AbilityStatus::Stun, false, 35);
	return Ability;
}

Ability AbilityCatalog::ChampionCombo() {
	Ability Ability("Champion Combo", "Unleash a devastating combo on the enemy.", 14, 24, AbilityStatus::None, false, 0);
	return Ability;
}
//===========================
// Enemy Abilities
//===========================

//Venomous Snake
Ability AbilityCatalog::VenomousStrike() {
	Ability Ability("Venomous Strike", "Strikes quickly with venomous fangs.", 0, 8, AbilityStatus::Poison, false, 35);
	return Ability;
}
Ability AbilityCatalog::CoiledLunge() {
	Ability Ability("Coiled Lunge", "Coils tightly before delivering a powerful lunging attack", 0, 12, AbilityStatus::None, false, 0);
	return Ability; 
}

//Bat
Ability AbilityCatalog::DivingBite() {
	Ability Ability("Diving Bite", "Dives from above to bite the target.", 0, 7, AbilityStatus::None, false, 0); 
	return Ability; 
}
Ability AbilityCatalog::WingBuffet() {
	Ability Ability("Wing Buffet", "Beats its wings violently against the target.", 0, 5, AbilityStatus::Stun, false, 15); 
	return Ability; 
}

//Hyena
Ability AbilityCatalog::SavageLunge() {
	Ability Ability("Savage Lunge", "Lunges forward with a vicious attack.", 0, 11, AbilityStatus::None, false, 0);
	return Ability; 
}
Ability AbilityCatalog::RendingBite() {
	Ability Ability("Rending Bite", "Tears into the target with powerful jaws.", 0, 9, AbilityStatus::Bleed, false, 30); 
	return Ability; 
}

//Leopard
Ability AbilityCatalog::Pounce() {
	Ability Ability("Pounce", "Leaps suddenly onto the target with crushing force.", 0, 15, AbilityStatus::None, false, 0); 
	return Ability; 
}
Ability AbilityCatalog::RakingClaws() {
	Ability Ability("Raking Claws", "Rakes the target with a rapid series of claw strikes.", 0, 12, AbilityStatus::Bleed, false, 35);
	return Ability; 
}

//Crocodile
Ability AbilityCatalog::CrushingBite() {
	Ability Ability("Crushing Bite", "Clamps down with its massive jaws.", 0, 14, AbilityStatus::None, false, 0);
	return Ability; 
}
Ability AbilityCatalog::TailSweep() {
	Ability Ability("Tail Sweep", "Swings its powerful tail with a chance to stun.", 0, 10, AbilityStatus::Stun, false, 25);
	return Ability; 
}

//Vampire Bat
Ability AbilityCatalog::BloodDrain() {
	Ability Ability("Blood Drain", "Sinks its fangs into the target and feasts on their blood.", 0, 13, AbilityStatus::Bleed, false, 20);
	return Ability; 
}
Ability AbilityCatalog::Screech() {
	Ability Ability("Screech", "Releases a piercing shriek with a chance to stun the enemy.", 0, 5, AbilityStatus::Stun, false, 30);
	return Ability; 
}

//Bat Swarm
Ability AbilityCatalog::SwarmAssault() {
	Ability Ability("Swarm Assault", "The swarm descends on the opponent from all directions.", 0, 12, AbilityStatus::None, false, 0);
	return Ability; 
}
Ability AbilityCatalog::FrenziedBites() {
	Ability Ability("Frenzied Bites", "The swarm erupts into a frenzy of snapping fangs.", 0, 10, AbilityStatus::Bleed, false, 40);
	return Ability; 
}

//Bonsam Thrall
Ability AbilityCatalog::FrenziedStrike() {
	Ability Ability("Frenzied Strike", "Attacks wildly with litter regard for its own safety.", 0, 16, AbilityStatus::None, false, 0);
	return Ability; 
}
Ability AbilityCatalog::BloodFrenzy() {
	Ability Ability("Blood Frenzy", "Gives in to its hunger and launches a vicious assault.", 0, 13, AbilityStatus::Bleed, false, 35);
	return Ability; 
}

//Bonsam
Ability AbilityCatalog::BloodClaw() {
	Ability Ability("Blood Claw", "Tears into its target with blood soaked claws.", 0, 19, AbilityStatus::Poison, false, 40);
	return Ability; 
}
Ability AbilityCatalog::DarkHunger() {
	Ability Ability("Dark Hunger", "Channels its unnatural hunger into a powerful attack.", 0, 17, AbilityStatus::None, false, 0);
	return Ability; 
}

//===========================
//Boss Abilities
//===========================

//Bonsam Elder
Ability AbilityCatalog::EldersWrath() {
	Ability Ability("Elders Wrath", "Unleashes the ancient fury of the Bonsam on a target.", 0, 22, AbilityStatus::Stun, false, 25);
	return Ability;
}

Ability AbilityCatalog::BloodRitual() {
	Ability Ability("Blood Ritual", "Invokes a dark blood rite against the target.", 0, 20, AbilityStatus::Bleed, false, 50);
	return Ability;
}