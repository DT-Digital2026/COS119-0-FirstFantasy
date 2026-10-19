#include "Bestiary.h"
#include "AbilityCatalog.h"

//Create venomous snake. 
Enemy Bestiary::CreateVenomousSnake() {
	//Create the enemy with existing stats. 
	Enemy Snake("Venomous Snake", 35, 8, 3); 

	//Access ability catalog. 
	AbilityCatalog abilityCatalog; 

	//Assign both of the snakes abilities.
	Snake.AddAbility(abilityCatalog.VenomousStrike()); 
	Snake.AddAbility(abilityCatalog.CoiledLunge()); 

	//Return the fully configured enemy. 
	return Snake; 

}

//Create bat. 
Enemy Bestiary::CreateBat() {
	Enemy Bat("Bat", 25, 7, 2);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	Bat.AddAbility(abilityCatalog.DivingBite());
	Bat.AddAbility(abilityCatalog.WingBuffet());

	//Return the fully configured enemy. 
	return Bat;
}

//Create Hyena. 
Enemy Bestiary::CreateHyena() {
	Enemy Hyena("Hyena", 50, 11, 5);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	Hyena.AddAbility(abilityCatalog.SavageLunge());
	Hyena.AddAbility(abilityCatalog.RendingBite());

	//Return the fully configured enemy. 
	return Hyena;
}

//Create Leopard. 
Enemy Bestiary::CreateLeopard() {
	Enemy Leopard("Leopard", 70, 15, 7);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	Leopard.AddAbility(abilityCatalog.Pounce());
	Leopard.AddAbility(abilityCatalog.RakingClaws());

	//Return the fully configured enemy. 
	return Leopard;
}

//Create crocodile. 
Enemy Bestiary::CreateCrocodile() {
	Enemy Crocodile("Crocodile", 90, 14, 12);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	Crocodile.AddAbility(abilityCatalog.CrushingBite());
	Crocodile.AddAbility(abilityCatalog.TailSweep());

	//Return the fully configured enemy. 
	return Crocodile;
}

//Create vampire bat. 
Enemy Bestiary::CreateVampireBat() {
	Enemy vBat("Vampire Bat", 55, 13, 6);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	vBat.AddAbility(abilityCatalog.BloodDrain());
	vBat.AddAbility(abilityCatalog.Screech());

	//Return the fully configured enemy. 
	return vBat;
}

//Create bat swarm. 
Enemy Bestiary::CreateBatSwarm() {
	Enemy BatSwarm("Bat Swarm", 80, 12, 4);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	BatSwarm.AddAbility(abilityCatalog.SwarmAssault());
	BatSwarm.AddAbility(abilityCatalog.FrenziedBites());

	//Return the fully configured enemy. 
	return BatSwarm;
}

//Create bonsam thrall. 
Enemy Bestiary::CreateBonsamThrall() {
	Enemy BonsamThrall("Bonsam Thrall", 100, 16, 10);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	BonsamThrall.AddAbility(abilityCatalog.FrenziedStrike());
	BonsamThrall.AddAbility(abilityCatalog.BloodFrenzy());

	//Return the fully configured enemy. 
	return BonsamThrall;
}

//Create bonsam. 
Enemy Bestiary::CreateBonsam() {
	Enemy Bonsam("Bonsam", 140, 19, 12);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	Bonsam.AddAbility(abilityCatalog.BloodClaw());
	Bonsam.AddAbility(abilityCatalog.DarkHunger());

	//Return the fully configured enemy. 
	return Bonsam;
}

//Create elder bonsam. 
Enemy Bestiary::CreateBonsamElder() {
	Enemy ElderBonsam("Bonsam Elder", 250, 22, 15);

	//Access ability catalog. 
	AbilityCatalog abilityCatalog;

	//Assign both of the snakes abilities.
	ElderBonsam.AddAbility(abilityCatalog.EldersWrath());
	ElderBonsam.AddAbility(abilityCatalog.BloodRitual());

	//Return the fully configured enemy. 
	return ElderBonsam;
}