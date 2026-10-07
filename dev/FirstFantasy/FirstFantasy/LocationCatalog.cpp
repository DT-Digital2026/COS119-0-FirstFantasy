#include "LocationCatalog.h"

//Default constructor.
LocationCatalog::LocationCatalog() {
	//mBestiary uses its default constructor.
}

//Creates the road leading to the village.
Location LocationCatalog::CreateRoadtoVillage() {
	Location road(
		"Road to Village",
		"A worn road winds through the wilderness toward the village.",
		20
	);

	//Adds enemies to the road encounter pool.
	road.AddEnemy(mBestiary.CreateVenomousSnake());
	road.AddEnemy(mBestiary.CreateBat());

	return road;
}

//Creates the village.
Location LocationCatalog::CreateVillage() {
	Location village(
		"Village",
		"A small settlement near the edge of the wilderness. "
		"An uneasy silence hangs over the village.",
		0
	);

	//The village has no random enemy encounters.

	return village;
}

//Creates the wilderness.
Location LocationCatalog::CreateWilderness() {
	Location wilderness(
		"Wilderness",
		"Dense vegetation and untamed paths surround the village. "
		"Predators stalk beneath the canopy.",
		35
	);

	//Adds enemies to the wilderness encounter pool.
	wilderness.AddEnemy(mBestiary.CreateVenomousSnake());
	wilderness.AddEnemy(mBestiary.CreateBat());
	wilderness.AddEnemy(mBestiary.CreateHyena());
	wilderness.AddEnemy(mBestiary.CreateLeopard());

	return wilderness;
}

//Creates Bloodroot Hollow.
Location LocationCatalog::CreateBloodRootHollow() {
	Location bloodrootHollow(
		"Bloodroot Hollow",
		"The air grows cold beneath twisted roots and dark stone. "
		"Something unnatural has taken hold here.",
		50
	);

	//Adds enemies to the Bloodroot Hollow encounter pool.
	bloodrootHollow.AddEnemy(mBestiary.CreateVampireBat());
	bloodrootHollow.AddEnemy(mBestiary.CreateBatSwarm());
	bloodrootHollow.AddEnemy(mBestiary.CreateBonsamThrall());

	return bloodrootHollow;
}