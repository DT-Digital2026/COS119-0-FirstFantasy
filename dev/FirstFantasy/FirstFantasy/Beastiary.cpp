#include "Beastiary.h"

//Create venomous snake. 
Enemy Beastiary::CreateVenomousSnake() {
	return Enemy("Venomous Snake", 35, 8, 3); 
}

//Create bat. 
Enemy Beastiary::CreateBat() {
	return Enemy("Bat", 25, 7, 2);
}

//Create Hyena. 
Enemy Beastiary::CreateHyena() {
	return Enemy("Hyena", 50, 11, 5);
}

//Create Leopard. 
Enemy Beastiary::CreateLeopard() {
	return Enemy("Leopard", 70, 15, 7);
}

//Create crocodile. 
Enemy Beastiary::CreateCrocodile() {
	return Enemy("Crocodile", 90, 14, 12);
}

//Create vampire bat. 
Enemy Beastiary::CreateVampireBat() {
	return Enemy("Vampire Bat", 55, 13, 6);
}

//Create bat swarm. 
Enemy Beastiary::CreateBatSwarm() {
	return Enemy("Bat Swarm", 80, 12, 4);
}

//Create bonsam thrall. 
Enemy Beastiary::CreateBonsamThrall() {
	return Enemy("Bonsam Thrall", 100, 16, 10);
}

//Create bonsam. 
Enemy Beastiary::CreateBonsam() {
	return Enemy("Bonsam", 140, 19, 12);
}

//Create elder bonsam. 
Enemy Beastiary::CreateBonsamElder() {
	return Enemy("Bonsam Elder", 250, 22, 15);
}