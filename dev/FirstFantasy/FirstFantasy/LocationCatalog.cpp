#include "LocationCatalog.h"

//Default constructor.
LocationCatalog::LocationCatalog() {
	//mBestiary uses its default constructor.
}

//Creates the road leading to the village.
Location LocationCatalog::CreateRoadtoVillage() {
	Location road(
		1, //v.02 added location ID.
		"Road to Village",
		"A worn road winds through the wilderness toward the village.",
		20
	);

	//Adds enemies to the road encounter pool.
	road.AddEnemy(mBestiary.CreateVenomousSnake());
	road.AddEnemy(mBestiary.CreateBat());

	return road;
}

//v.02 Creates the crossroads leading to the village.
Location LocationCatalog::CreateCrossroads() {
	Location crossroads(
		2,//v.02 added location ID.
		"Crossroads",
		"The worn roads divide beneath an ancient tree. "
		"A narrow trail disappears into a dense forest."
		"while another path follows the sound of flowing water.",
		0
	);
	crossroads.AddEnemy(mBestiary.CreateVenomousSnake());
	crossroads.AddEnemy(mBestiary.CreateBat());
	crossroads.AddEnemy(mBestiary.CreateHyena());
	crossroads.AddEnemy(mBestiary.CreateLeopard());


	return crossroads;
}

//v.02 Creates the forest path.
Location LocationCatalog::CreateForestPath() {
	Location ForestPath(
		3,//v.02 added location ID.
		"Forest Path",
		"A narrow trail winds between towering trees. "
		"The undergrowth rustles with unseen movement.",
		0
	);
	ForestPath.AddEnemy(mBestiary.CreateVenomousSnake());
	ForestPath.AddEnemy(mBestiary.CreateLeopard());

	return ForestPath;
}

//v.02 Creates the river path.
Location LocationCatalog::CreateRiverPath() {
	Location RiverPath(
		4,//v.02 added location ID.
		"River Path",
		"The road follows a shallow river. "
		"Water flows and smoothes stones, "
		"and distant animals call through the trees.",
		0
	);
	RiverPath.AddEnemy(mBestiary.CreateVenomousSnake());
	RiverPath.AddEnemy(mBestiary.CreateCrocodile());
	return RiverPath;
}

//Creates the village.
Location LocationCatalog::CreateVillage() {
	Location village(
		5,//v.02 added location ID.
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
		6,//v.02 added location ID.
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
		7,//v.02 added location ID.
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