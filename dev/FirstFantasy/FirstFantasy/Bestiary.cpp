#include "Bestiary.h"

//Create venomous snake. 
Enemy Bestiary::CreateVenomousSnake() {
	return Enemy("Venomous Snake", 35, 8, 3); 
}

//Create bat. 
Enemy Bestiary::CreateBat() {
	return Enemy("Bat", 25, 7, 2);
}

//Create Hyena. 
Enemy Bestiary::CreateHyena() {
	return Enemy("Hyena", 50, 11, 5);
}

//Create Leopard. 
Enemy Bestiary::CreateLeopard() {
	return Enemy("Leopard", 70, 15, 7);
}

//Create crocodile. 
Enemy Bestiary::CreateCrocodile() {
	return Enemy("Crocodile", 90, 14, 12);
}

//Create vampire bat. 
Enemy Bestiary::CreateVampireBat() {
	return Enemy("Vampire Bat", 55, 13, 6);
}

//Create bat swarm. 
Enemy Bestiary::CreateBatSwarm() {
	return Enemy("Bat Swarm", 80, 12, 4);
}

//Create bonsam thrall. 
Enemy Bestiary::CreateBonsamThrall() {
	return Enemy("Bonsam Thrall", 100, 16, 10);
}

//Create bonsam. 
Enemy Bestiary::CreateBonsam() {
	return Enemy("Bonsam", 140, 19, 12);
}

//Create elder bonsam. 
Enemy Bestiary::CreateBonsamElder() {
	return Enemy("Bonsam Elder", 250, 22, 15);
}