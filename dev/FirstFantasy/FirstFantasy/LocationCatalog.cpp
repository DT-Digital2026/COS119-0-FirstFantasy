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

// Creates the village entrance. v.03 changed name to village entrance to support village layout.
Location LocationCatalog::CreateVillageEntrance()
{
    Location village(
        5,
        "Village Entrance",
        "A worn dirt road leads to a modest fishing village nestled against the wilderness. "
        "The villagers go about their daily routines though an uneasy tension hangs in the air.",
        0
    );

    // Connected locations.
    village.AddConnection(3);
    village.AddConnection(4);
    village.AddConnection(6);
    village.AddConnection(8);


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
    wilderness.AddConnection(13);

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
    bloodrootHollow.AddConnection(16);

    // Enemy encounter pool.
    bloodrootHollow.AddEnemy(mBestiary.CreateVampireBat());
    bloodrootHollow.AddEnemy(mBestiary.CreateBatSwarm());
    bloodrootHollow.AddEnemy(mBestiary.CreateBonsamThrall());

    return bloodrootHollow;
}

//==============================================
//       Create Locations within Village
//==============================================

Location LocationCatalog::CreateVillageCenter()
{
    Location village(
        8,
        "Village Center",
        "Villagers gather beneath the shade of towering trees, exchanging goods and conversation. "
        "Children play nearby, seemignly unaware of the worried whispers among their elders.",
        0
    );

    // Connected locations.
    village.AddConnection(5);
    village.AddConnection(9);
    village.AddConnection(10);
    village.AddConnection(11);
    village.AddConnection(12);

    // The village has no random enemy encounters.

    return village;
}

Location LocationCatalog::CreateFishermansWharf()
{
    Location village(
        9,
        "Fisherman's Wharf",
        "Weathered wooden docs stretch into the water, where fishing boats sway gently against their moorings. "
        "The smell of fresh fish fills the air as fishermen mend their nets and prepare their daily catch.",
        0
    );

    // Connected locations.
    village.AddConnection(8);
   
    // The village has no random enemy encounters.

    return village;
}

Location LocationCatalog::CreateItemShop()
{
    Location village(
        10,
        "Item Shop",
        "Shelves lined with herbs, handmade tools, and traveling supplies fill the cramped little shop. "
        "An aging merchant watches attentively from behind a wooden counter.",
        0
    );

    // Connected locations.
    village.AddConnection(8);
   
    // The village has no random enemy encounters.

    return village;
}

Location LocationCatalog::CreateChiefsHut()
{
    Location village(
        11,
        "Chief's Hut",
        "A large carefully constructed hut stands apart from the surrounding village homes. "
        "Carved wooden symbols decorate its entrance, marking the dwelling of the village's respected chief.",
        0
    );

    // Connected locations.
    village.AddConnection(8);
   
    // The village has no random enemy encounters.

    return village;
}

Location LocationCatalog::CreateShamansHut()
{
    Location village(
        12,
        "Shaman's Hut",
        "The scent of burning herbs drifts from a secluded hut adorned with bones and sacred charms. "
        "A faint chanting can be heard from within, carrying the same desperate urgency as the prayer that summoned the heroes.",
        0
    );

    // Connected locations.
    village.AddConnection(8);
   
    // The village has no random enemy encounters.

    return village;
}
//==============================================
//    Create Locations within the Wilderness
//==============================================
Location LocationCatalog::CreateOvergrownTrail()
{
    Location OGTrail(
        13,
        "Overgrown Trail",
        "A narrow trail winds through dense vegetation, its surface nearly swallowed by tangled roots and creeping vines. "
        "Broken branches and disturbed undergrowth suggest something has recently passed through the wilderness. ",
        30
    );

    // Connected locations.
    OGTrail.AddConnection(6);
    OGTrail.AddConnection(14);
    OGTrail.AddConnection(15);

    //Encounter Table
    OGTrail.AddEnemy(mBestiary.CreateVenomousSnake());
    OGTrail.AddEnemy(mBestiary.CreateHyena()); 
    OGTrail.AddEnemy(mBestiary.CreateLeopard()); 

    return OGTrail;
}

Location LocationCatalog::CreateAbandonedCampsite()
{
    Location AbandonedCampsite(
        14,
        "Abandoned Campsite",
        "The remains of a small camp lie beneath the towering trees, its firepit cold and scattered belongings left behind. "
        "Deep scratches scar a nearby tree, while an unsettling silence hangs over the deserted clearing.",
        40
    );

    // Connected locations.
    AbandonedCampsite.AddConnection(13);

    // The village has no random enemy encounters.
    AbandonedCampsite.AddEnemy(mBestiary.CreateHyena()); 
    AbandonedCampsite.AddEnemy(mBestiary.CreateLeopard()); 
    AbandonedCampsite.AddEnemy(mBestiary.CreateVampireBat()); 

    return AbandonedCampsite;
}

Location LocationCatalog::CreateRiverBankClearing()
{
    Location RiverBankClearing(
        15,
        "Riverbank Clearing",
        "A shallow river winds through a secluded clearing, its muddy banks lined with exposed roots and smooth stones. "
        "Something small glimmers along the tangled roots near the waters edge, partially buried beneath the silt.",
        25
    );

    // Connected locations.
    RiverBankClearing.AddConnection(13);
    RiverBankClearing.AddConnection(7);


    // The village has no random enemy encounters.
    RiverBankClearing.AddEnemy(mBestiary.CreateVampireBat()); 
    RiverBankClearing.AddEnemy(mBestiary.CreateCrocodile()); 
    RiverBankClearing.AddEnemy(mBestiary.CreateVenomousSnake()); 

    return RiverBankClearing;
}

//==============================================
//   Create Locations within Bloodroot Hollow
//==============================================
Location LocationCatalog::CreateTheWitheredGrove()
{
    Location WitheredGrove(
        16,
        "The Withered Grove",
        "Towering trees stand lifeless beneath a canopy of twisted branches, their bark split by veins of dark crimson sap. "
        "The earth feels unnaturally warm beneath your feet, and distant whispers seem to drift between the trunks",
        40
    );

    // Connected locations.
    WitheredGrove.AddConnection(7);
    WitheredGrove.AddConnection(17);
    WitheredGrove.AddConnection(18); 


    // The village has no random enemy encounters.
    WitheredGrove.AddEnemy(mBestiary.CreateVampireBat()); 
    WitheredGrove.AddEnemy(mBestiary.CreateBatSwarm()); 
    WitheredGrove.AddEnemy(mBestiary.CreateBonsamThrall()); 

    return WitheredGrove;
}
Location LocationCatalog::CreateTheBoneStrewnPath()
{
    Location BoneStrewnPath(
        17,
        "The Bone Strewn Path",
        "Fragments of weathered bones litter a narrow passage winding deeper into the hollow, some unmistakeably belonging to animals, others to humans. "
        "Strange markings have been carved into the surrounding trees, their meaning obscured by age and decay.",
        50
    );

    // Connected locations.
    BoneStrewnPath.AddConnection(16);
    BoneStrewnPath.AddConnection(19);


    // The village has no random enemy encounters.
    BoneStrewnPath.AddEnemy(mBestiary.CreateBatSwarm()); 
    BoneStrewnPath.AddEnemy(mBestiary.CreateBonsamThrall()); 

    return BoneStrewnPath;
}
Location LocationCatalog::CreateTheDesecratedShrine()
{
    Location DesecratedShrine(
        18,
        "The Desecrated Shrine",
        "A crumbling stone altar rests beneath the roots of an ancient tree, surrounding by broken offerings and shattered ceremonial vessels. "
        "Faint symbols glow across its surface, suggesting that something sacred once stood here before being violently disturbed.",
        35
    );

    // Connected locations.
    DesecratedShrine.AddConnection(16);
    DesecratedShrine.AddConnection(19);


    // The village has no random enemy encounters.
    DesecratedShrine.AddEnemy(mBestiary.CreateVampireBat()); 
    DesecratedShrine.AddEnemy(mBestiary.CreateBonsam()); 

    return DesecratedShrine;
}
Location LocationCatalog::CreateHeartoftheHollow()
{
    Location HeartoftheHollow(
        19,
        "The Heart of the Hollow",
        "An enormous, ancient tree rises from the center of a sunken clearing, its exposed roots twisting through the earth like grapsing fingers. "
        "A suffocating presence fills the air, and something powerful stirs within the darkness beneath the trunk.",
        0 //Scripted boss fight.
    );

    // Connected locations.
    HeartoftheHollow.AddConnection(17);
    HeartoftheHollow.AddConnection(18);


    // The village has no random enemy encounters.
    HeartoftheHollow.AddEnemy(mBestiary.CreateBonsamElder());

    return HeartoftheHollow;
}


//====================================================
// v.02 - Retrieves a location by its unique ID.
//====================================================
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
        return CreateVillageEntrance();

    case 6:
        return CreateWilderness();

    case 7:
        return CreateBloodRootHollow();

    case 8:
        return CreateVillageCenter(); 

    case 9:
        return CreateFishermansWharf(); 

    case 10:
        return CreateItemShop(); 

    case 11: 
        return CreateChiefsHut(); 

    case 12: 
        return CreateShamansHut(); 

    case 13:
        return CreateOvergrownTrail(); 

    case 14:
        return CreateAbandonedCampsite(); 

    case 15: 
        return CreateRiverBankClearing(); 

    case 16:
        return CreateTheWitheredGrove(); 

    case 17: 
        return CreateTheBoneStrewnPath(); 

    case 18: 
        return CreateTheDesecratedShrine(); 

    case 19:
        return CreateHeartoftheHollow(); 

    default:
        return Location();
    }
}