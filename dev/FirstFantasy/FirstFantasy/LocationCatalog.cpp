#include "LocationCatalog.h"

// Default constructor.
LocationCatalog::LocationCatalog()
{
    // mBestiary uses its default constructor.
}

// Creates the road leading to the village.
Location LocationCatalog::CreateRoadtoVillage()
{
    Location road(
        1,
        "Road to Village",
        "A worn road winds through the wilderness toward the village.",
        20
    );

    // Connected locations.
    road.AddConnection(2);

    // Enemy encounter pool.
    road.AddEnemy(mBestiary.CreateVenomousSnake());
    road.AddEnemy(mBestiary.CreateBat());

    return road;
}

// Creates the crossroads.
Location LocationCatalog::CreateCrossroads()
{
    Location crossroads(
        2,
        "Crossroads",
        "The worn roads divide beneath an ancient tree. "
        "A narrow trail disappears into a dense forest "
        "while another path follows the sound of flowing water.",
        0
    );

    // Connected locations.
    crossroads.AddConnection(1);
    crossroads.AddConnection(3);
    crossroads.AddConnection(4);

    // Enemy encounter pool.
    crossroads.AddEnemy(mBestiary.CreateVenomousSnake());
    crossroads.AddEnemy(mBestiary.CreateBat());
    crossroads.AddEnemy(mBestiary.CreateHyena());
    crossroads.AddEnemy(mBestiary.CreateLeopard());

    return crossroads;
}

// Creates the forest path.
Location LocationCatalog::CreateForestPath()
{
    Location ForestPath(
        3,
        "Forest Path",
        "A narrow trail winds between towering trees. "
        "The undergrowth rustles with unseen movement.",
        0
    );

    // Connected locations.
    ForestPath.AddConnection(2);
    ForestPath.AddConnection(5);

    // Enemy encounter pool.
    ForestPath.AddEnemy(mBestiary.CreateVenomousSnake());
    ForestPath.AddEnemy(mBestiary.CreateLeopard());

    return ForestPath;
}

// Creates the river path.
Location LocationCatalog::CreateRiverPath()
{
    Location RiverPath(
        4,
        "River Path",
        "The road follows a shallow river. "
        "Water flows and smoothes stones, "
        "and distant animals call through the trees.",
        0
    );

    // Connected locations.
    RiverPath.AddConnection(2);
    RiverPath.AddConnection(5);

    // Enemy encounter pool.
    RiverPath.AddEnemy(mBestiary.CreateVenomousSnake());
    RiverPath.AddEnemy(mBestiary.CreateCrocodile());

    return RiverPath;
}

// Creates the village.
Location LocationCatalog::CreateVillage()
{
    Location village(
        5,
        "Village",
        "A small settlement near the edge of the wilderness. "
        "An uneasy silence hangs over the village.",
        0
    );

    // Connected locations.
    village.AddConnection(3);
    village.AddConnection(4);
    village.AddConnection(6);

    // The village has no random enemy encounters.

    return village;
}

// Creates the wilderness.
Location LocationCatalog::CreateWilderness()
{
    Location wilderness(
        6,
        "Wilderness",
        "Dense vegetation and untamed paths surround the village. "
        "Predators stalk beneath the canopy.",
        35
    );

    // Connected locations.
    wilderness.AddConnection(5);
    wilderness.AddConnection(7);

    // Enemy encounter pool.
    wilderness.AddEnemy(mBestiary.CreateVenomousSnake());
    wilderness.AddEnemy(mBestiary.CreateBat());
    wilderness.AddEnemy(mBestiary.CreateHyena());
    wilderness.AddEnemy(mBestiary.CreateLeopard());

    return wilderness;
}

// Creates Bloodroot Hollow.
Location LocationCatalog::CreateBloodRootHollow()
{
    Location bloodrootHollow(
        7,
        "Bloodroot Hollow",
        "The air grows cold beneath twisted roots and dark stone. "
        "Something unnatural has taken hold here.",
        50
    );

    // Connected locations.
    bloodrootHollow.AddConnection(6);

    // Enemy encounter pool.
    bloodrootHollow.AddEnemy(mBestiary.CreateVampireBat());
    bloodrootHollow.AddEnemy(mBestiary.CreateBatSwarm());
    bloodrootHollow.AddEnemy(mBestiary.CreateBonsamThrall());

    return bloodrootHollow;
}

// v.02 - Retrieves a location by its unique ID.
Location LocationCatalog::GetLocationByID(int LocationID)
{
    switch (LocationID)
    {
    case 1:
        return CreateRoadtoVillage();

    case 2:
        return CreateCrossroads();

    case 3:
        return CreateForestPath();

    case 4:
        return CreateRiverPath();

    case 5:
        return CreateVillage();

    case 6:
        return CreateWilderness();

    case 7:
        return CreateBloodRootHollow();

    default:
        return Location();
    }
}