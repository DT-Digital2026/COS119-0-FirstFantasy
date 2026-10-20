#include <iostream> 
#include <limits>
#include <string>
#include <stdexcept>
#include <random>

#include "Game.h"
#include "AbilityCatalog.h"
#include "ItemCatalog.h"

//Starts a new game.
void Game::StartNewGame()
{
    InitializeGame();
    DisplayOpeningScene(); //v.03 Opening scene method.
    GameLoop();
}

//v.03 Kicks off the opening scene. 
void Game::DisplayOpeningScene() {
    std::cout << "\n============================================================\n" << std::endl;
    std::cout << "                FIRST FANTASY: THE DARK CONTINENT\n         " << std::endl;
    std::cout << "==============================================================\n" << std::endl;

    std::cout << "\nFor generations, the world has existed in a delicate balance.\n"; 
    std::cout << "\nBetween the seen and the unseen.\n"; 
    std::cout << "Between the living and the things that dwell beyond their understand.\n"; 
    std::cout << "\nEven the oldest balances can be broken.\n"; 

    std::cout << "\n------------------------------------------------------------------\n"; 

    std::cout << "\nFar beyond the great cities, where the wilderness swallows\n"; 
    std::cout << "the roads and the rivers run deep, a desperate prayer rises into the night.\n"; 

    std::cout << "\nA prayer for protection.\n"; 
    std::cout << "\nA prayer for those gone missing.\n"; 
    std::cout << "\nA prayer that does not go unanswered.\n"; 

    std::cout << "\n------------------------------------------------------------------\n";

    std::cout << "\nTwo warriors have heard the call.\n"; 
    std::cout << "\nOra'Kanu the voice of the storm.\n"; 
    std::cout << "\nM'Batha the father of Dhambe.\n"; 

    std::cout << "\nDrawn toward a remote fishing village, they travel West\n"; 
    std::cout << "\nbeneath the fading afternoon sun.\n"; 

    std::cout << "\nNeither knows what awaits them.\n"; 
    std::cout << "\nOnly that someone is calling for help.\n"; 
    std::cout << "\nAnd that something in the darkness has begun to stir.\n"; 

    std::cout << "\n------------------------------------------------------------------\n";

    std::cout << "\nPress Enter to begin your journey...\n"; 

    std::string input; 
    std::getline(std::cin, input); 
}

//Sets up everything needed for a new game.
void Game::InitializeGame()
{
    IsGameRunning = true;

    std::cout << "\n============================================================" << std::endl;
    std::cout << "                FIRST FANTASY: THE DARK CONTINENT          " << std::endl;
    std::cout << "============================================================" << std::endl;

    std::cout << "\nStarting a new game..." << std::endl;

    //Create the player characters.
    //Initialize Ora'Kanu
    OraKanu = Character("Ora'Kanu", "Voice of the Storm", 100, 100, 15, 10); 

    //Intialize M'Batha
    Mbatha = Character("M'Batha", "Father of Dhambe", 120, 60, 18, 15); 

    //Create the catalog of abilities. 
    AbilityCatalog abilityCatalog; 

    //Assign Ora'Kanu's starting abilities. 
    OraKanu.AddAbility(abilityCatalog.Raincall()); 
    
    //Assign M'Batha's starting abilities. 
    Mbatha.AddAbility(abilityCatalog.Jab());

    //Set player stats.
    OraKanu.DisplayStats(); 
    OraKanu.DisplayAbilities(); 

    std::cout << std::endl;

    Mbatha.DisplayStats(); 
    Mbatha.DisplayAbilities(); 

    //v.03 Clear inventory when starting a new game.
    mInventory = Inventory(); 

    //v.03 Temporary item for testing the inventory system.
   // Temporary item for testing the inventory system.
    Item healingHerb(
        "Healing Herb",
        "A medicinal herb that restores 25 HP.",
        ItemType::Consumable,
        25,  // HP restored
        0,   // Ase restored
        0,   // Attack bonus
        0    // Defense bonus
    );
    mInventory.AddItem(healingHerb); 
    
    //Set the initial story state.
    mCurrentLocationId = 1; //v.02 Sets the starting location to 1-RoadtoVillage.

    //v.03 Will ensure that every new game begins at the first stage, even if the same Game object is used.
    mRoadProgress = 0; 

    //v.03 Will ensure that every new game begins with the Met Shaman flag set to false. 
    mHasMetShaman = false;
    //v.03 Will ensure that every new game begins with the Met Cheif flag is set to false.
    mHasMetChief = false; 
    //v.03 Sets necklace to being found to false upon a new game. 
    mHasFoundNecklace = false;  
    //v.03 Sets necklace return to false.
    mHasReturnedNecklace = false; 

    //v.04 Resetting the flag for Bloodroot Hollow. 
    mHasEnteredBloodrootHollow = false; 
    //v.04 Reset flag for Withered Grove. 
    mHasExploredWitheredGrove = false; 
    //v.04 Reset flag for Bone Strewn Path. 
    mHasExploredBoneStrewnPath = false; 
    //v.04 Reset flag for Desecrated Shrine. 
    mHasExploredDesecratedShrine = false; 
    //v.04 Reset flag for Heart of the Hollow. 
    mHasExploredHeartoftheHollow = false;
    //v.04 Reset flag for Bonsam Elder. 
    mHasDefeatedBonsamElder = false; 

    //v.04 Game ending. 
    mHasHeardChiefsConfession = false; 
    mHasHeardShamansWarning = false; 
}

//============================================================
//   v.03 Story Element for Shaman's Hut    
//============================================================

void Game::MeetShaman() {
    // Handle returning to the shaman after the chief's confession.
    if (mHasMetShaman) {
        if (mHasDefeatedBonsamElder && mHasHeardChiefsConfession && !mHasHeardShamansWarning) {
            ShamansWarning();
        }

        return;
    }
    std::cout << "\n====================================================================\n"; 
    std::cout << "                          The Shaman's Call                             "; 
    std::cout << "\n=====================================================================\n"; 

    std::cout << "\nThe scent of burning herbs fills the small hut.\n"; 
    std::cout << "\nAn elderly shaman sits beside a flickering fire,\n"; 
    std::cout << "\nhis weathered handsresting upon a wooden staff.\n"; 

    std::cout << "\nAs Ora'Kanu and M'Batha enter, the shaman slowly rises.\n"; 

    std::cout << "\nShaman: \"Your have come...you have heard my prayers.\"\n"; 

    std::cout << "\nOra'Kanu: \"Your voice has carried far beyond this village.\n"; 
    std::cout << "Tell us what troubles your people.\"\n"; 

    std::cout << "\nThe Shaman lowers his gaze.\n"; 

    std::cout << "\nShaman: \"Our children have began to disappear.\n"; 
    std::cout << "Fishermen leave for the river and never return.\n"; 
    std::cout << "The people grow frightened, and I fear their\n"; 
    std::cout << "suffering has only just begun.\"\n";

    std::cout << "\nM'Batha: \"Have your hunters searched the wilderness?\"\n";

    std::cout << "\nShaman: \"They have found nothing, but there are places\n"; 
    std::cout << "beyond this village where even our bravest hunters\n"; 
    std::cout << "dare not travel.\"\n"; 

    std::cout << "\nThe shaman glances at the doorway.\n"; 

    std::cout << "\nShaman: \"You must speak with our cheif.\n"; 
    std::cout << "he knows more of these disappearances than I can\n"; 
    std::cout << "explain here. Tell him I sent you.\"\n"; 

    std::cout << "\nOra'Kanu nods.\n"; 

    std::cout << "\nOra'Kanu: \"Then we will speak with him.\"\n";

    std::cout << "=========================================================="; 
    std::cout << "\n Press ENTER to continue.\n"; 

    std::string input; 
    std::getline(std::cin, input); 

    //Record that the introduction has occured. 
    mHasMetShaman = true; 
}

//============================================================
//   v.03 Story Element for Meeting the Village Cheif   
//============================================================
void Game::MeetChief() {
    if (mHasMetChief) {
        // The boss has been defeated.
        // Trigger the Chief's Confession first.
        if (mHasDefeatedBonsamElder && !mHasHeardChiefsConfession) {
            ChiefsConfession();
        }

        // Handle Ama's Necklace if the quest is still pending.
        else if (mHasFoundNecklace && !mHasReturnedNecklace) {
            ReturnNecklacetoChief();
        }

        return;
    }
    std::cout << "\n=====================================================================\n";
    std::cout << "                          The Chief's Request                            ";
    std::cout << "\n=====================================================================\n";

    std::cout << "\nThe village cheif sits before a wooden table,\n"; 
    std::cout << "studying a collection of markings carved into its surface.\n"; 

    std::cout << "\nChief: \"Strangers, what business brings you to my village?\"\n"; 

    std::cout << "\nOra'Kanu: \"We answered the prayers of your shaman.\n"; 
    std::cout << "He told us your people have gone missing.\"\n";

    std::cout << "\nThe chief's expression grows troubled.\n"; 

    std::cout << "\nChief: \"Then you know why we need help.\n";  
    std::cout << "Children have vanished, and fishermen have failed to\n"; 
    std::cout << "return from the river.\"\n"; 

    std::cout << "\nM'Batha: \"Where were they last seen?\"\n"; 

    std::cout << "\nCheif: \"Near the wilderness beyond our village.\n"; 
    std::cout << "Our hunters searched the nearby trails, but found nothing.\"\n"; 

    std::cout << "\nThe chief pauses before continuing.\n"; 

    std::cout << "\nChief: \"I ask that you investigate those woods.\n"; 
    std::cout << "Search for anything that might explain these disappearances.\n"; 
    std::cout << "If you discover something, return to me.\"\n"; 

    std::cout << "\nOra'Kanu: \"We will search the wilderness.\"\n"; 

    std::cout << "\nChief: \"May the spirits guide your steps.\"\n"; 

    std::cout << "==========================================================";
    std::cout << "\n Press ENTER to continue.\n";

    std::string input;
    std::getline(std::cin, input);

    //Record that the introduction has occured. 
    mHasMetChief = true;
}
//============================================================
//   v.03 Story Element for Ama's Necklace
//============================================================
void Game::DiscoverNecklace() {
    if (!mHasMetChief || mHasFoundNecklace) {
        return; 
    }
    std::cout << "\n============================================================" << std::endl;
    std::cout << "                     A Child's Necklace                       " << std::endl;
    std::cout << "==============================================================" << std::endl;

    std::cout << "\nThe river moves quietly through the clearing.\n"; 
    std::cout << "As the heroes approach the water, something catches\n"; 
    std::cout << "Ora'Kanu's attention just beneath the water near the shore.\n"; 

    std::cout << "\nOra'Kanu: \"M'Batha, come and look at this.\"\n"; 

    std::cout << "\nM'Batha kneels beside the riverbank and carefully\n"; 
    std::cout << "pulls a small necklace from the mud.\n"; 

    std::cout << "\nM'Batha: \"A child's necklace...\"\n";

    std::cout << "\nOra'Kanu: \"Perhaps it belongs to one of the missing.\n";
    std::cout << "We should return to the chief.\"\n";

    //Create the actual quest item.
    Item necklace(
        "Ama's Necklace",
        "A small, mud-stained necklace discovered near the riverbank.",
        ItemType::KeyItem,
        0, 0, 0, 0
    );

    //Add the necklace to the party inventory.
    mInventory.AddItem(necklace);

    //Prevent the discovery from happening again.
    mHasFoundNecklace = true;

    std::cout << "\n[QUEST ITEM ACQUIRED: Ama's Necklace]\n";

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

//============================================================
//   v.03 Story Element for Ama's Necklace
//============================================================
void Game::ReturnNecklacetoChief() {
    if (!mHasFoundNecklace || mHasReturnedNecklace) {
        return; 
    }
    std::cout << "\n============================================================" << std::endl;
    std::cout << "                    The Chief's Sorrow                        " << std::endl;
    std::cout << "==============================================================" << std::endl;

    std::cout << "\nThe chief looks up as Ora'Kanu and M'Batha enter.\n"; 

    std::cout << "\nChief: \"You have returned. What have you discovered?\"\n"; 

    std::cout << "\nM'Batha places the small necklace upon the table.\n"; 

    std::cout << "\nM'Batha: \"We found this near the River Bank.\"\n"; 

    std::cout << "\nThe chief reaches for the necklace, but his hand\n"; 
    std::cout << "stops just short of touching it.\n"; 

    std::cout << "\nChief: \"This belonged to Ama...\n"; 

    std::cout << "\nOra'Kanu: \"You recognize it?\"\n"; 

    std::cout << "\nChief: \"Her mother gave it to her. She never took it off.\"\n"; 

    std::cout << "\nThe chief lowers his head in silence.\n"; 

    std::cout << "\nChief: \"There is a place beyond the river.\n"; 
    std::cout << "Our people have avoided it for generations.\n"; 
    std::cout << "We call it Bloodroot Hollow. It is dangerous, filled with\n";
    std::cout << "darkness. Creatures that live on blood...the Bonsam.\"\n"; 

    std::cout << "\nOra'Kanu: \"Leave it to us, we will investigate this Bloodroot Hollow.\"\n"; 

    std::cout << "\n[QUEST UPDATED: Investigate Bloodroot Hollow.]\n";

    //v.04 Locate Ama's necklace in the party inventory. 
    int necklaceIndex = mInventory.FindItemByName("Ama's Necklace"); 

    if (necklaceIndex == -1) {
        std::cout << "\nAma's Necklace is missing from the inventory.\n"; 
        return; 
    }

    //v.04 Remove the necklace after returning it to the chief.
    mInventory.RemoveItem(necklaceIndex); 

    std::cout << "\n[QUEST ITEM REMOVED: Ama's Necklace]\n"; 

    //v.04 Create the quest rewards. 
    ItemCatalog itemCatalog; 

    Item shamanBracers = itemCatalog.CreateShamanBracers(); 
    Item reinforcedWraps = itemCatalog.CreateReinforcedWraps(); 

    //v.04 Add both to the parties inventory. 
    mInventory.AddItem(shamanBracers); 
    mInventory.AddItem(reinforcedWraps); 

    std::cout << "\nThe chief opens a wooden chest beside his table.\n"; 
    std::cout << "Chief: \"These belonged to warriors who once protected our village.\n"; 
    std::cout << "Take them. You may need their strength in the days ahead.\"\n"; 

    std::cout << "\n[QUEST REWARD: Shaman Bracers]\n";
    std::cout << "[QUEST REWARD: Reinforced Wraps]\n";

    //v.04 Prevents the conversation from repeating. 
    mHasReturnedNecklace = true; 

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

//============================================================
// v.04        Story Element - The Chief's Confession
//============================================================

void Game::ChiefsConfession() {
    // Prevent the scene from repeating.
    if (mHasHeardChiefsConfession) {
        return;
    }

    std::cout << "\n============================================================\n";
    std::cout << "                    THE CHIEF'S CONFESSION\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe chief rises as Ora'Kanu and M'Batha enter his hut.\n";

    std::cout << "\nChief: \"You have returned from Bloodroot Hollow.\"\n";

    std::cout << "\nHis eyes search the doorway behind them.\n";

    std::cout << "\nChief: \"Did you find our people?\"\n";

    std::cout << "\nNeither warrior answers immediately.\n";

    std::cout << "\nM'Batha: \"We found evidence of what happened to them.\"\n";

    std::cout << "\nThe chief slowly lowers himself into his chair.\n";

    std::cout << "\nChief: \"Tell me.\"\n";

    std::cout << "\nOra'Kanu: \"Many of those who disappeared are dead.\"\n";

    std::cout << "\nThe chief closes his eyes.\n";

    std::cout << "\nOra'Kanu: \"Something beneath the forest has been\n";
    std::cout << "feeding upon their Ase.\"\n";

    std::cout << "\nM'Batha: \"We confronted the Bonsam Elder.\n";
    std::cout << "It spoke of an ancient agreement with your village.\"\n";

    std::cout << "\nThe chief's expression changes.\n";

    std::cout << "\nChief: \"Then you found the shrine.\"\n";

    std::cout << "\nOra'Kanu: \"You knew about it?\"\n";

    std::cout << "\nThe chief looks toward the markings carved into\n";
    std::cout << "the wooden table before him.\n";

    std::cout << "\nChief: \"My father told me the stories.\n";
    std::cout << "And his father told them to him.\"\n";

    std::cout << "\nChief: \"Long before this village stood beside the river,\n";
    std::cout << "our ancestors made a covenant with the Bonsam.\"\n";

    std::cout << "\nM'Batha: \"What kind of covenant?\"\n";

    std::cout << "\nChief: \"We would remain beyond the marked boundary.\n";
    std::cout << "The Bonsam would remain within the hollow.\"\n";

    std::cout << "\nChief: \"Each season, offerings were carried to the shrine.\n";
    std::cout << "They were a promise that neither side had forgotten.\"\n";

    std::cout << "\nOra'Kanu: \"And the offerings stopped.\"\n";

    std::cout << "\nThe chief lowers his head.\n";

    std::cout << "\nChief: \"Yes.\"\n";

    std::cout << "\nM'Batha: \"Why?\"\n";

    std::cout << "\nChief: \"The old traditions frightened our people.\n";
    std::cout << "They began to question why we honored creatures\n";
    std::cout << "they had never seen.\"\n";

    std::cout << "\nChief: \"I believed the danger had passed.\n";
    std::cout << "I allowed the offerings to end.\"\n";

    std::cout << "\nOra'Kanu: \"But someone destroyed the shrine.\"\n";

    std::cout << "\nThe chief looks up sharply.\n";

    std::cout << "\nChief: \"Destroyed?\"\n";

    std::cout << "\nM'Batha: \"The altar was shattered.\n";
    std::cout << "The markings broken.\"\n";

    std::cout << "\nChief: \"I ordered no such thing.\"\n";

    std::cout << "\nOra'Kanu: \"Then someone acted without your knowledge.\"\n";

    std::cout << "\nA long silence fills the hut.\n";

    std::cout << "\nChief: \"I thought abandoning the offerings\n";
    std::cout << "would free us from the old fears.\"\n";

    std::cout << "\nChief: \"Instead, I may have invited something worse.\"\n";

    std::cout << "\nM'Batha: \"The Elder believed your people\n";
    std::cout << "had broken the covenant.\"\n";

    std::cout << "\nChief: \"And perhaps we did.\"\n";

    std::cout << "\nOra'Kanu: \"There is something else.\"\n";

    std::cout << "\nThe chief raises his eyes.\n";

    std::cout << "\nOra'Kanu: \"The Elder said something beneath the roots\n";
    std::cout << "had awakened. Something even the Bonsam feared.\"\n";

    std::cout << "\nThe chief's face grows pale.\n";

    std::cout << "\nChief: \"Then you must speak with the shaman.\"\n";

    std::cout << "\nM'Batha: \"What does he know?\"\n";

    std::cout << "\nChief: \"There are stories older than our village.\n";
    std::cout << "Stories I was never permitted to hear.\"\n";

    std::cout << "\nChief: \"If anyone understands what sleeps beneath\n";
    std::cout << "that forest, it will be him.\"\n";

    std::cout << "\nOra'Kanu turns toward the doorway.\n";

    std::cout << "\nOra'Kanu: \"Then we have no time to waste.\"\n";

    std::cout << "\nAs the warriors prepare to leave,\n";
    std::cout << "the chief speaks once more.\n";

    std::cout << "\nChief: \"Ora'Kanu... M'Batha...\"\n";

    std::cout << "\nThey stop.\n";

    std::cout << "\nChief: \"When you learn what happened to the others...\n";
    std::cout << "please tell me.\"\n";

    std::cout << "\nHis gaze falls upon the empty place on the table\n";
    std::cout << "where Ama's necklace once rested.\n";

    std::cout << "\nNeither warrior makes a promise.\n";

    std::cout << "\n[QUEST UPDATED: SPEAK WITH THE SHAMAN]\n";

    // Record completion.
    mHasHeardChiefsConfession = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

//============================================================
// v.04 Story Element - The Shaman's Warning
// Prototype Finale
//============================================================

void Game::ShamansWarning() {
    // Prevent the finale from repeating.
    if (mHasHeardShamansWarning) {
        return;
    }

    std::cout << "\n============================================================\n";
    std::cout << "                    THE SHAMAN'S WARNING\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe shaman's hut is unusually cold.\n";

    std::cout << "\nThe fire at its center burns low,\n";
    std::cout << "casting long shadows across the wooden walls.\n";

    std::cout << "\nThe shaman sits beside the flames,\n";
    std::cout << "his eyes fixed upon the darkness beyond them.\n";

    std::cout << "\nShaman: \"You have returned.\"\n";

    std::cout << "\nOra'Kanu: \"We have seen what lies within\n";
    std::cout << "Bloodroot Hollow.\"\n";

    std::cout << "\nThe shaman closes his eyes.\n";

    std::cout << "\nShaman: \"Then you have seen the Bonsam.\"\n";

    std::cout << "\nM'Batha: \"We fought their Elder.\"\n";

    std::cout << "\nThe shaman's hands tighten around his staff.\n";

    std::cout << "\nShaman: \"And yet you stand before me.\"\n";

    std::cout << "\nOra'Kanu: \"The Elder was not our true enemy.\"\n";

    std::cout << "\nShe approaches the fire.\n";

    std::cout << "\nOra'Kanu: \"Something beneath the forest is feeding\n";
    std::cout << "upon the Ase of the living.\"\n";

    std::cout << "\nM'Batha: \"Many of the missing villagers are dead.\n";
    std::cout << "Their lives were taken to feed it.\"\n";

    std::cout << "\nFor a long moment, the shaman says nothing.\n";

    std::cout << "\nThen he reaches into a small wooden chest.\n";

    std::cout << "\nFrom within, he removes a bundle of cloth,\n";
    std::cout << "darkened with age and bound with a leather cord.\n";

    std::cout << "\nShaman: \"There are stories my teachers forbade\n";
    std::cout << "me from speaking aloud.\"\n";

    std::cout << "\nHe carefully unwraps the bundle.\n";

    std::cout << "\nInside lies a fragment of ancient parchment.\n";

    std::cout << "\nIts surface bears a faded drawing of a great tree.\n";

    std::cout << "\nBeneath its roots, something enormous has been\n";
    std::cout << "drawn in black ink.\n";

    std::cout << "\nM'Batha: \"What is that creature?\"\n";

    std::cout << "\nShaman: \"I do not know its name.\"\n";

    std::cout << "\nOra'Kanu studies the drawing.\n";

    std::cout << "\nThe shape beneath the tree resembles neither\n";
    std::cout << "man nor beast.\n";

    std::cout << "\nIts countless limbs stretch outward,\n";
    std::cout << "disappearing beyond the parchment's edges.\n";

    std::cout << "\nShaman: \"Long ago, our ancestors believed\n";
    std::cout << "that the world itself could become hungry.\"\n";

    std::cout << "\nM'Batha: \"The world?\"\n";

    std::cout << "\nShaman: \"Not the earth beneath our feet.\n";
    std::cout << "Something that dwells within it.\"\n";

    std::cout << "\nThe shaman points toward the ancient tree.\n";

    std::cout << "\nShaman: \"The old shrines were not built\n";
    std::cout << "merely to honor the spirits.\"\n";

    std::cout << "\nShaman: \"They were built to keep something sleeping.\"\n";

    std::cout << "\nOra'Kanu: \"Then the covenant was a protection.\"\n";

    std::cout << "\nShaman: \"For the village. For the Bonsam.\n";
    std::cout << "Perhaps for all who live upon this land.\"\n";

    std::cout << "\nM'Batha: \"Someone destroyed the shrine.\"\n";

    std::cout << "\nShaman: \"Then someone has broken the seal.\"\n";

    std::cout << "\nA sudden gust extinguishes the fire.\n";

    std::cout << "\nThe hut falls into darkness.\n";

    std::cout << "\nOutside, the village dogs begin to howl.\n";

    std::cout << "\nOra'Kanu raises her hand.\n";

    std::cout << "\nA faint current of Ase dances across her fingers,\n";
    std::cout << "illuminating the parchment.\"\n";

    std::cout << "\nSomething in the drawing has changed.\n";

    std::cout << "\nWhere the ancient tree once stood alone,\n";
    std::cout << "several smaller markings now surround it.\n";

    std::cout << "\nM'Batha: \"Were those there before?\"\n";

    std::cout << "\nThe shaman stares at the parchment.\n";

    std::cout << "\nShaman: \"No.\"\n";

    std::cout << "\nThe markings spread across the parchment,\n";
    std::cout << "branching outward like veins beneath skin.\n";

    std::cout << "\nOra'Kanu: \"These are other places.\"\n";

    std::cout << "\nThe shaman nods slowly.\n";

    std::cout << "\nShaman: \"Other seals.\"\n";

    std::cout << "\nM'Batha: \"How many?\"\n";

    std::cout << "\nThe shaman looks toward the doorway.\n";

    std::cout << "\nShaman: \"I fear we are about to discover that.\"\n";

    std::cout << "\nA distant rumble passes beneath the village.\n";

    std::cout << "\nThe wooden walls tremble.\n";

    std::cout << "\nFor a brief moment, something whispers\n";
    std::cout << "from beneath the floorboards.\n";

    std::cout << "\nThe voice is faint.\n";

    std::cout << "\nBut Ora'Kanu understands its meaning.\n";

    std::cout << "\nIt is not calling for help.\n";

    std::cout << "\nIt is calling for more.\n";

    std::cout << "\n============================================================\n";
    std::cout << "                    THE JOURNEY CONTINUES\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe darkness beneath Bloodroot Hollow has awakened.\n";

    std::cout << "\nAnd somewhere beyond the village,\n";
    std::cout << "other ancient protections are beginning to fail.\n";

    std::cout << "\nOra'Kanu and M'Batha have survived their first trial.\n";

    std::cout << "\nBut their journey across the Dark Continent\n";
    std::cout << "has only just begun.\n";

    std::cout << "\n============================================================\n";
    std::cout << "            FIRST FANTASY: THE DARK CONTINENT\n";
    std::cout << "============================================================\n";

    std::cout << "\n                    END OF PROTOTYPE\n";

    std::cout << "\n              Thank you for playing!\n";

    std::cout << "\n============================================================\n";

    // Record the finale as completed.
    mHasHeardShamansWarning = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

//Temporary game loop. This will be expanded as the game is developed.
void Game::GameLoop() {
    while (IsGameRunning) {
        std::string input;
        int choice = -1;

        std::cout << "\n============================================================" << std::endl;
        std::cout << "                         GAME                                 " << std::endl;
        std::cout << "==============================================================" << std::endl;

        std::cout << "1. Continue" << std::endl;
        std::cout << "2. Return to Main Menu" << std::endl;

        std::cout << "Enter your choice: ";

        if (!std::getline(std::cin, input)) {
            IsGameRunning = false;
            break;
        }

        // Validate the player's input.
        try {
            size_t position = 0;
            choice = std::stoi(input, &position);

            // Reject inputs such as "1abc" or "2.5".
            if (position != input.length()) {
                std::cout << "Invalid input. Please enter 1 or 2.\n";
                continue;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }
        catch (const std::out_of_range&) {
            std::cout << "Number is out of range. Please enter 1 or 2.\n";
            continue;
        }

        if (choice == 1) {
            if (mRoadProgress < 4) {
                AdvanceRoadJourney();
            }
            else {
                ExploreLocation();
            }
        }
        else if (choice == 2) {
            // Return to the main menu.
            IsGameRunning = false;
        }
        else {
            std::cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }
}

//================================================================================
//v.04             Story Elemtns -  Bloodroot Hollow           
//================================================================================
void Game::EnterBloodrootHollow() {
    //Prevent the scene from repeating. 
    if (mHasEnteredBloodrootHollow) {
        return; 
    }
    std::cout << "\n============================================================\n";
    std::cout << "                  BLOODROOT HOLLOW\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe forest grows unnaturally quiet as the heroes\n";
    std::cout << "leave the familiar wilderness behind.\n";

    std::cout << "\nThe trees stand close together, their branches\n";
    std::cout << "intertwining overhead and swallowing the afternoon light.\n";

    std::cout << "\nThick roots, stained a deep crimson, twist across\n";
    std::cout << "the ground like veins beneath the forest floor.\n";

    std::cout << "\nM'Batha: \"Something is wrong with this place.\"\n";

    std::cout << "\nOra'Kanu: \"The forest is old. Older than the village.\"\n";

    std::cout << "\nA faint rattling sound draws their attention.\n";

    std::cout << "\nSmall wooden charms hang from the surrounding trees,\n";
    std::cout << "swaying gently despite the absence of wind.\n";

    std::cout << "\nM'Batha approaches one of the trees.\n";

    std::cout << "\nM'Batha: \"These markings... I've seen some of them before.\"\n";

    std::cout << "\nOra'Kanu: \"Where?\"\n";

    std::cout << "\nM'Batha: \"Protective symbols. Used to mark sacred ground.\n";
    std::cout << "But these others... I don't recognize them.\"\n";

    std::cout << "\nBeyond the hanging charms, a weathered warning\n";
    std::cout << "has been carved deep into the bark of an ancient tree.\n";

    std::cout << "\nThe words have nearly disappeared beneath the moss.\n";

    std::cout << "\nOra'Kanu brushes the moss away.\n";

    std::cout << "\nOra'Kanu: \"A boundary.\"\n";

    std::cout << "\nM'Batha: \"A warning?\"\n";

    std::cout << "\nOra'Kanu: \"Perhaps. But warnings are meant to keep\n";
    std::cout << "something on one side of a line.\"\n";

    std::cout << "\nHe looks toward the darkness beyond the trees.\n";

    std::cout << "\nOra'Kanu: \"The question is which side they feared.\"\n";

    std::cout << "\nFor a moment, neither warrior speaks.\n";

    std::cout << "\nThen, somewhere deeper in the hollow,\n";
    std::cout << "something answers with a low, distant cry.\n";

    std::cout << "\n[LORE DISCOVERED: The Boundary of Bloodroot Hollow]\n";

    // Record that the scene has played.
    mHasEnteredBloodrootHollow = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

void Game::ExploreWitheredGrove() {
    //Prevent the scene from repeating. 
    if (mHasExploredWitheredGrove) {
        return; 
    }
    std::cout << "\n=======================================================================\n"; 
    std::cout << "                       The Withered Grove                                  "; 
    std::cout << "=========================================================================\n"; 


    std::cout << "\nThe deeper the heroes travel into Bloodroot Hollow,\n";
    std::cout << "the more the forest begins to change.\n";

    std::cout << "\nThe crimson roots that once twisted beneath their feet\n";
    std::cout << "have turned black and brittle.\n";

    std::cout << "\nLeaves hang lifeless from the branches overhead.\n";
    std::cout << "The earth is dry, cracked, and strangely warm.\n";

    std::cout << "\nM'Batha: \"These trees have been dead for some time.\"\n";

    std::cout << "\nOra'Kanu kneels beside a fallen branch.\n";

    std::cout << "\nShe presses her palm against the darkened wood.\n";

    std::cout << "\nFor a brief moment, a faint current of Ase moves\n";
    std::cout << "through her fingertips.\n";

    std::cout << "\nThen it vanishes.\n";

    std::cout << "\nOra'Kanu: \"No. They are still dying.\"\n";

    std::cout << "\nM'Batha: \"What do you mean?\"\n";

    std::cout << "\nOra'Kanu: \"There is life beneath the bark.\n";
    std::cout << "Something is draining it away.\"\n";

    std::cout << "\nA sudden gust moves through the grove.\n";

    std::cout << "\nThe branches tremble, but not a single leaf falls.\n";

    std::cout << "\nOra'Kanu closes her eyes.\n";

    std::cout << "\nShe reaches outward with her Ase, searching for\n";
    std::cout << "the familiar rhythm of the wind and approaching rain.\n";

    std::cout << "\nBut the air feels wrong.\n";

    std::cout << "\nHeavy. Restless.\n";

    std::cout << "\nLike a storm trapped beneath the earth.\n";

    std::cout << "\nOra'Kanu: \"There is something beneath this place.\n";
    std::cout << "I can feel it moving through the roots.\"\n";

    std::cout << "\nM'Batha: \"Toward us?\"\n";

    std::cout << "\nOra'Kanu slowly shakes her head.\n";

    std::cout << "\nOra'Kanu: \"Toward the village.\"\n";

    std::cout << "\nM'Batha looks back along the path they traveled.\n";

    std::cout << "\nM'Batha: \"Then whatever is happening here will not\n";
    std::cout << "remain hidden in these woods for much longer.\"\n";

    std::cout << "\nA sharp cracking sound echoes through the grove.\n";

    std::cout << "\nOne of the ancient trees splits down its center.\n";

    std::cout << "\nFrom within its hollow trunk, a thick black substance\n";
    std::cout << "slowly seeps into the surrounding soil.\n";

    std::cout << "\nOra'Kanu: \"We need to find where this began.\"\n";

    std::cout << "\n[LORE DISCOVERED: The Withering of Bloodroot Hollow]\n";

    // Record that the scene has played.
    mHasExploredWitheredGrove = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

void Game::ExploreBoneStrewnPath()
{
    // Prevent this scene from repeating.
    if (mHasExploredBoneStrewnPath) {
        return;
    }

    std::cout << "\n============================================================\n";
    std::cout << "                    THE BONE-STREWN PATH\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe narrow trail winds between ancient trees,\n";
    std::cout << "their exposed roots twisting through the dark soil.\n";

    std::cout << "\nWith each step, the ground becomes increasingly uneven.\n";

    std::cout << "\nA sharp cracking sound breaks the silence.\n";

    std::cout << "\nM'Batha stops walking.\n";

    std::cout << "\nBeneath his foot lies a small, weathered bone.\n";

    std::cout << "\nM'Batha: \"Ora'Kanu. Look at the ground.\"\n";

    std::cout << "\nOra'Kanu lowers her gaze.\n";

    std::cout << "\nScattered among the roots are dozens of bones,\n";
    std::cout << "some bleached white, others nearly swallowed by the earth.\n";

    std::cout << "\nThe remains of animals lie alongside fragments\n";
    std::cout << "that appear unmistakably human.\n";

    std::cout << "\nOra'Kanu: \"This place has claimed many lives.\"\n";

    std::cout << "\nM'Batha kneels beside a collection of broken remains.\n";

    std::cout << "\nM'Batha: \"Not all of them recently.\"\n";

    std::cout << "\nHe lifts an old bone from the soil.\n";

    std::cout << "\nM'Batha: \"Some have been here for years.\n";
    std::cout << "Perhaps longer.\"\n";

    std::cout << "\nA few steps farther along the path,\n";
    std::cout << "something catches Ora'Kanu's attention.\n";

    std::cout << "\nA torn fishing net hangs from a low branch,\n";
    std::cout << "its fibers tangled around the crimson roots.\n";

    std::cout << "\nOra'Kanu: \"This doesn't belong here.\"\n";

    std::cout << "\nM'Batha approaches the net.\n";

    std::cout << "\nM'Batha: \"One of the missing fishermen?\"\n";

    std::cout << "\nOra'Kanu: \"Possibly. But look at the fibers.\"\n";

    std::cout << "\nThe net has been torn apart with tremendous force.\n";

    std::cout << "\nNearby, the remains of a wooden fishing spear\n";
    std::cout << "lie partially buried beneath the roots.\n";

    std::cout << "\nM'Batha: \"Someone fought here.\"\n";

    std::cout << "\nOra'Kanu: \"And whatever happened was recent.\"\n";

    std::cout << "\nM'Batha looks toward the deeper forest.\n";

    std::cout << "\nM'Batha: \"Then the chief was right to fear this place.\"\n";

    std::cout << "\nOra'Kanu: \"Perhaps. But something troubles me.\"\n";

    std::cout << "\nM'Batha: \"What is it?\"\n";

    std::cout << "\nOra'Kanu: \"These older remains have been here for years.\n";
    std::cout << "Yet the village survived beside this forest for generations.\"\n";

    std::cout << "\nShe looks again at the torn fishing net.\n";

    std::cout << "\nOra'Kanu: \"Why has the danger suddenly reached beyond\n";
    std::cout << "the hollow?\"\n";

    std::cout << "\nBefore M'Batha can answer, a distant rustling\n";
    std::cout << "moves through the surrounding trees.\n";

    std::cout << "\nSomething shifts among the branches overhead.\n";

    std::cout << "\nThen the forest falls silent once more.\n";

    std::cout << "\nM'Batha: \"We are not alone.\"\n";

    std::cout << "\nOra'Kanu: \"No. And I suspect we have not been alone\n";
    std::cout << "since entering these woods.\"\n";

    std::cout << "\n[LORE DISCOVERED: The Bones of Bloodroot Hollow]\n";

    // Mark the story event as completed.
    mHasExploredBoneStrewnPath = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

void Game::ExploreDesecratedShrine()
{
    // Prevent this scene from repeating.
    if (mHasExploredDesecratedShrine) {
        return;
    }

    std::cout << "\n============================================================\n";
    std::cout << "                    THE DESECRATED SHRINE\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe twisted trees begin to thin as Ora'Kanu and\n";
    std::cout << "M'Batha approach a small clearing.\n";

    std::cout << "\nAt its center stands the remains of an ancient shrine.\n";

    std::cout << "\nWeathered stone pillars rise from the earth,\n";
    std::cout << "their surfaces covered in faded carvings.\n";

    std::cout << "\nA massive stone altar rests between them.\n";

    std::cout << "\nOr rather, what remains of one.\n";

    std::cout << "\nThe altar has been shattered into several pieces.\n";
    std::cout << "Broken offerings lie scattered across the ground.\n";

    std::cout << "\nM'Batha: \"Someone has destroyed this place.\"\n";

    std::cout << "\nOra'Kanu approaches one of the stone pillars.\n";

    std::cout << "\nShe runs her fingers across the ancient markings.\n";

    std::cout << "\nOra'Kanu: \"These symbols...\"\n";

    std::cout << "\nM'Batha: \"You've seen them before?\"\n";

    std::cout << "\nOra'Kanu: \"At the entrance to Bloodroot Hollow.\n";
    std::cout << "The markings carved into the trees.\"\n";

    std::cout << "\nM'Batha examines the base of the broken altar.\n";

    std::cout << "\nBeneath the rubble, he discovers several small\n";
    std::cout << "wooden bowls and fragments of woven cloth.\n";

    std::cout << "\nM'Batha: \"Offerings.\"\n";

    std::cout << "\nOra'Kanu: \"To whom?\"\n";

    std::cout << "\nM'Batha: \"Or to what?\"\n";

    std::cout << "\nThe two warriors examine the shrine more closely.\n";

    std::cout << "\nSeveral carvings depict figures standing on\n";
    std::cout << "opposite sides of a winding river.\n";

    std::cout << "\nBetween them stands a great tree,\n";
    std::cout << "its roots stretching beneath both shores.\n";

    std::cout << "\nOra'Kanu: \"Look at the figures.\"\n";

    std::cout << "\nOn one side, human forms carry baskets and bowls.\n";

    std::cout << "\nOn the other, strange elongated figures emerge\n";
    std::cout << "from the shadows beneath the trees.\n";

    std::cout << "\nM'Batha: \"These are not scenes of battle.\"\n";

    std::cout << "\nOra'Kanu: \"No. They are exchanging something.\"\n";

    std::cout << "\nM'Batha: \"An offering?\"\n";

    std::cout << "\nOra'Kanu: \"Perhaps an agreement.\"\n";

    std::cout << "\nA sudden breeze passes through the clearing.\n";

    std::cout << "\nLoose dust rises from the shattered altar.\n";

    std::cout << "\nOra'Kanu kneels beside the largest broken stone.\n";

    std::cout << "\nIts fractured edges are sharp and pale,\n";
    std::cout << "unlike the weathered surfaces surrounding them.\n";

    std::cout << "\nOra'Kanu: \"This destruction is recent.\"\n";

    std::cout << "\nM'Batha: \"Then someone wanted the shrine gone.\"\n";

    std::cout << "\nOra'Kanu: \"And whatever understanding existed here\n";
    std::cout << "may have been destroyed along with it.\"\n";

    std::cout << "\nM'Batha looks toward the deeper forest.\n";

    std::cout << "\nM'Batha: \"Could this explain the disappearances?\"\n";

    std::cout << "\nOra'Kanu: \"It may explain why they began.\n";
    std::cout << "But we still do not know who broke the agreement.\"\n";

    std::cout << "\nShe rises and looks toward the path ahead.\n";

    std::cout << "\nOra'Kanu: \"Someone knows what happened here.\n";
    std::cout << "We need to find them.\"\n";

    std::cout << "\nAs the heroes turn away from the altar,\n";
    std::cout << "a low whisper moves through the surrounding trees.\n";

    std::cout << "\nThe sound resembles a voice,\n";
    std::cout << "but its words cannot be understood.\n";

    std::cout << "\nM'Batha: \"Did you hear that?\"\n";

    std::cout << "\nOra'Kanu: \"Yes.\"\n";

    std::cout << "\nShe watches the darkness beyond the clearing.\n";

    std::cout << "\nOra'Kanu: \"And I believe it heard us.\"\n";

    std::cout << "\n[LORE DISCOVERED: The Broken Covenant]\n";

    // Record that the story event has played.
    mHasExploredDesecratedShrine = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}

void Game::ExploreHeartoftheHollow() {
    if (mHasExploredHeartoftheHollow) {
        return;
    }

    std::cout << "\n============================================================\n";
    std::cout << "                    HEART OF THE HOLLOW\n";
    std::cout << "============================================================\n";

    std::cout << "\nThe trees part to reveal an enormous clearing.\n";
    std::cout << "At its center stands a colossal, ancient tree.\n";

    std::cout << "\nIts roots rise from the ground like the bones\n";
    std::cout << "of some long-forgotten giant.\n";

    std::cout << "\nThe earth beneath it is black and lifeless.\n";
    std::cout << "Not a single blade of grass grows within the clearing.\n";

    std::cout << "\nM'Batha: \"This must be the heart of the forest.\"\n";

    std::cout << "\nOra'Kanu studies the enormous tree.\n";

    std::cout << "\nOra'Kanu: \"Whatever is draining the hollow...\n";
    std::cout << "I can feel it gathering here.\"\n";

    std::cout << "\nA deep vibration moves through the ground.\n";

    std::cout << "\nThe roots begin to tremble.\n";

    std::cout << "\nM'Batha: \"Ora'Kanu...\"\n";

    std::cout << "\nFrom the darkness beneath the ancient tree,\n";
    std::cout << "a towering figure slowly emerges.\n";

    std::cout << "\nIts limbs are unnaturally long, its body thin\n";
    std::cout << "and twisted beneath layers of darkened bark.\n";

    std::cout << "\nTwo pale eyes open within the shadows.\n";

    std::cout << "\nA voice rises from the creature,\n";
    std::cout << "deep and ancient, like wood splitting beneath pressure.\n";

    std::cout << "\nBonsam Elder: \"Children of the world beyond the roots...\"\n";

    std::cout << "\nBonsam Elder: \"Why have you entered my domain?\"\n";

    std::cout << "\nOra'Kanu: \"We seek those who have vanished from the village.\"\n";

    std::cout << "\nThe Elder's pale eyes narrow.\n";

    std::cout << "\nBonsam Elder: \"The village...\"\n";

    std::cout << "\nA low, bitter sound escapes its throat.\n";

    std::cout << "\nBonsam Elder: \"For generations, we kept our distance.\n";
    std::cout << "Your people remained beyond the boundary.\n";
    std::cout << "Mine remained beneath the roots.\"\n";

    std::cout << "\nM'Batha: \"Then you know of the agreement.\"\n";

    std::cout << "\nBonsam Elder: \"An agreement carved in stone.\n";
    std::cout << "An agreement your people shattered.\"\n";

    std::cout << "\nOra'Kanu: \"We found the shrine.\n";
    std::cout << "But we do not know who destroyed it.\"\n";

    std::cout << "\nBonsam Elder: \"And yet it lies broken.\n";
    std::cout << "The roots wither. The old protections fail.\"\n";

    std::cout << "\nThe ancient tree groans overhead.\n";

    std::cout << "\nM'Batha: \"The village is suffering as well.\n";
    std::cout << "Children have disappeared. Fishermen have not returned.\"\n";

    std::cout << "\nFor a moment, the Elder remains silent.\n";

    std::cout << "\nBonsam Elder: \"The hunger has awakened.\n";
    std::cout << "Even my own have begun to lose themselves to it.\"\n";

    std::cout << "\nOra'Kanu: \"Then help us stop it.\"\n";

    std::cout << "\nThe Elder steps forward.\n";

    std::cout << "\nBonsam Elder: \"You speak of stopping what you do not understand.\"\n";

    std::cout << "\nIts enormous claws dig into the blackened earth.\n";

    std::cout << "\nBonsam Elder: \"If you would challenge the darkness\n";
    std::cout << "beneath these roots, first prove you can survive it.\"\n";

    std::cout << "\nM'Batha raises his fists.\n";

    std::cout << "\nOra'Kanu calls upon the gathering storm.\n";

    std::cout << "\nThe Elder releases a terrible cry.\n";

    std::cout << "\n[ BOSS ENCOUNTER: BONSAM ELDER ]\n";

    mHasExploredHeartoftheHollow = true;

    std::cout << "\nPress ENTER to continue...";
    std::string pause;
    std::getline(std::cin, pause);
}


void Game::StartBonsamElderFight()
{
    // Prevent the boss from respawning after victory.
    if (mHasDefeatedBonsamElder) {
        return;
    }

    // Create the boss using our existing Bestiary.
    Bestiary bestiary;
    Enemy elder = bestiary.CreateBonsamElder();

    std::cout << "\n============================================================\n";
    std::cout << "                 BOSS: BONSAM ELDER\n";
    std::cout << "============================================================\n";

    // Start the scripted boss encounter.
    CombatResult result = mCombatSystem.StartCombat(OraKanu, Mbatha, elder);

    if (result == CombatResult::Victory) {
        mHasDefeatedBonsamElder = true;

        std::cout << "\nThe Bonsam Elder collapses beneath the ancient tree.\n";
        std::cout << "Its enormous claws scrape against the blackened earth.\n";

        std::cout << "\nM'Batha: \"It is finished.\"\n";

        std::cout << "\nOra'Kanu: \"No. Something is still moving beneath us.\"\n";

        std::cout << "\nA faint trembling passes through the roots.\n";

        std::cout << "\nBonsam Elder: \"You have defeated a guardian...\n";
        std::cout << "not the thing it guarded against.\"\n";

        std::cout << "\nOra'Kanu: \"The missing villagers. Where are they?\"\n";

        std::cout << "\nThe Elder's pale eyes turn toward the ancient tree.\n";

        std::cout << "\nBonsam Elder: \"Some were brought beneath the roots.\n";
        std::cout << "Others wandered here when the old protections failed.\"\n";

        std::cout << "\nM'Batha: \"Are they alive?\"\n";

        std::cout << "\nFor a long moment, the Elder says nothing.\n";

        std::cout << "\nBonsam Elder: \"Many are not.\"\n";

        std::cout << "\nThe clearing falls silent.\n";

        std::cout << "\nBonsam Elder: \"Their bodies fed the earth.\n";
        std::cout << "Their Ase fed something far beneath it.\"\n";

        std::cout << "\nOra'Kanu kneels and places her palm against a root.\n";

        std::cout << "\nA cold pulse answers her touch.\n";

        std::cout << "\nFor an instant, she senses dozens of faint echoes.\n";
        std::cout << "Voices without words. Lives without warmth.\n";

        std::cout << "\nThen something vast stirs beneath them.\n";

        std::cout << "\nOra'Kanu recoils.\n";

        std::cout << "\nM'Batha: \"What did you feel?\"\n";

        std::cout << "\nOra'Kanu: \"Something that knows we're here.\"\n";

        std::cout << "\nThe Elder struggles to raise its head.\n";

        std::cout << "\nBonsam Elder: \"The covenant kept it sleeping.\n";
        std::cout << "The shrine was broken. The hunger returned.\"\n";

        std::cout << "\nM'Batha: \"Who destroyed the shrine?\"\n";

        std::cout << "\nBonsam Elder: \"I do not know.\"\n";

        std::cout << "\nIts voice weakens.\n";

        std::cout << "\nBonsam Elder: \"But someone wished for the hunger\n";
        std::cout << "to awaken.\"\n";

        std::cout << "\nA final shudder passes through the Elder's body.\n";

        std::cout << "\nIts pale eyes close.\n";

        std::cout << "\nThe ancient tree stands silent above the fallen guardian.\n";

        std::cout << "\nM'Batha: \"We came here to save those people.\"\n";

        std::cout << "\nOra'Kanu: \"And now we must tell their families\n";
        std::cout << "what we've discovered.\"\n";

        std::cout << "\n[QUEST UPDATED: RETURN TO THE VILLAGE]\n";

        std::cout << "\nPress ENTER to continue...";
        std::string pause;
        std::getline(std::cin, pause);
    }
    else if (result == CombatResult::Defeat) {
        std::cout << "\nThe heroes fall beneath the ancient tree.\n";
        std::cout << "The darkness of Bloodroot Hollow claims another victory.\n";

        IsGameRunning = false;
    }
}

//=========================================
//    v.02 DisplayTravelOptions
//=========================================

//Displays all connected locations the player can travel to. 
void Game::DisplayTravelOptions(const Location& currentLocation) {
    //Retrieve the current locations connections. 
    const std::vector<int>& connections = currentLocation.GetConnections(); 

    int menuNumber = 1; 

    std::cout << "\nWhere would you like to travel?\n"; 

    //Loop through all connected locations. 
    for (int destinationId : connections) {
        //Retrieve the destination location. 
        Location destination = mLocationCatalog.GetLocationByID(destinationId); 

        //v.02 Display the destination number and name.
        std::cout << menuNumber << ". "
            << destination.GetName() << std::endl;

        menuNumber++; 
    }
    std::cout << "9. View Inventory" << std::endl;
    std::cout << "0. Exit Exploration" << std::endl;
}

//=========================================
//    v.02 Explore Location
//=========================================
//v.02 - Handles player-controlled exploration.
void Game::ExploreLocation() {
    while (IsGameRunning) {
        //Retrieve the player's current location.
        Location currentLocation = mLocationCatalog.GetLocationByID(mCurrentLocationId);

        //Display the current location's name and description.
        currentLocation.DisplayLocation();

        //Display available travel destinations.
        DisplayTravelOptions(currentLocation);

        //Retrieve connected destination IDs.
        const std::vector<int>& connections = currentLocation.GetConnections();

        std::string input;
        int choice = -1;

        std::cout << "\nEnter your choice: ";

        //Read the entire line of user input.
        if (!std::getline(std::cin, input)) {
            //Handle closed or failed input.
            IsGameRunning = false;
            break;
        }

        //Convert input into an integer.
        try {
            size_t position = 0;

            choice = std::stoi(input, &position);

            //Reject input containing extra characters.
            if (position != input.length()) {
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        catch (const std::out_of_range&) {
            std::cout << "Number is too large. Please try again.\n";
            continue;
        }

        //v.03 View the party inventory. 
        if (choice == 9) {
            mInventory.DisplayInventory(); 

            std::cout << "\nPress ENTER to return to exploration..."; 
            std::string pause; 
            std::getline(std::cin, pause); 

            continue; 
        }

        //Exit exploration.
      // Exit exploration and return to the main menu.
        if (choice == 0) {
            std::cout << "\nReturning to Main Menu...\n";

            IsGameRunning = false;
            break;
        }

        //Validate the selected destination.
        if (choice >= 1 && choice <= static_cast<int>(connections.size())) {
            //Convert menu selection to vector index.
            int index = choice - 1;

            //Retrieve the selected destination ID.
            int destinationID = connections[index];

            //v.03 The chief will only recieve visitors sent by the shaman. 
            if (destinationID == 11 && !mHasMetShaman) {
                std::cout << "\nTwo village guards stand outside the chief's hut.\n"; 
                std::cout << "\nGuard: \"The chief is not recieving visitors.\"\n"; 
                std::cout << "\nGuard: \"If you seek an audience, speak with the shaman first.\"\n"; 

                continue; 
            }

            //Update the player's current location.
            mCurrentLocationId = destinationID;

            //v.03 Trigger the shaman's introduction when entering his hut. 
            if (mCurrentLocationId == 12) {
                MeetShaman(); 
            }
            //v.03 Trigger the chief's introduction when entering his hut.
            if (mCurrentLocationId == 11) {
                MeetChief();
            }

            //v.03 Discover the necklace after accepting the chief's request. 
            if (mCurrentLocationId == 15 && mHasMetChief && !mHasFoundNecklace) {
                DiscoverNecklace(); 
            }

            //v.04 Trigger Bloodroot Hollow's introduction.
            if (mCurrentLocationId == 7 && !mHasEnteredBloodrootHollow) {
                EnterBloodrootHollow();
            }

            //v.04 Trigger the withered grove story scene. 
            if (mCurrentLocationId == 16 && !mHasExploredWitheredGrove) {
                ExploreWitheredGrove(); 
            }

            // v.04 Trigger the Bone-Strewn Path story scene.
            if (mCurrentLocationId == 17 && !mHasExploredBoneStrewnPath) {
                ExploreBoneStrewnPath();
            }

            //v.04 Trigger the Desecrated Shrine story scene. 
            if (mCurrentLocationId == 18 && !mHasExploredDesecratedShrine) {
                ExploreDesecratedShrine();
            }

            //v.04 Trigger the Heart of the Hollow story scene.
            if (mCurrentLocationId == 19 && !mHasExploredHeartoftheHollow) {
                ExploreHeartoftheHollow();
            }

            //v.04 Trigger the end game boss fight.
            if (mCurrentLocationId == 19 && mHasExploredHeartoftheHollow && !mHasDefeatedBonsamElder) {
                StartBonsamElderFight();
            }
            //Checks for random encounters.
            CheckRandomEncounter(); 
        }
        else
        {
            std::cout << "Invalid destination. Please try again.\n";
        }
    }
 }
//=====================================
//      v.03 Advance Road Journey
//=====================================
//Handles scripted progression along the 
//road before normal exploration begins. 

void Game::AdvanceRoadJourney() {
    switch (mRoadProgress) {
    case 0:
        std::cout << "\nOra'Kanu and M'Batha travel along the western road.\n"; 
        std::cout << "\nTheir destination is a remote fishing village beyond the wilderness.\n"; 
        std::cout << "\nThe afternoon sun hangs above the trees.\n"; 
        mRoadProgress++; 
        break; 

    case 1: {
        std::cout << "\nThe road narrows as thick vegetation crosses the path.\n";
        std::cout << "Something stirs in the bushes nearby.\n";

        //v.03. Scripted first encounter. 
        Bestiary bestiary;

        Enemy snake = bestiary.CreateVenomousSnake();

        std::cout << "\nA Venomous Snake emerges from the bushes!\n";

        CombatResult result = mCombatSystem.StartCombat(
            OraKanu,
            Mbatha,
            snake
        );

        if (result == CombatResult::Victory)
        {
            std::cout << "\nThe snake collapses to the ground.\n";
            std::cout << "The heroes have survived their first encounter.\n";

            mRoadProgress++;
        }
        else if (result == CombatResult::Defeat)
        {
            std::cout << "\nThe heroes fall along the roadside...\n";
            std::cout << "Their journey ends before it can truly begin.\n";

            IsGameRunning = false;
        }
    }
        break;

    case 2: 
        std::cout << "\nThe road grows quiet once more.\n"; 
        std::cout << "\nOra'Kanu and M'Batha continue toward the distant village.\n"; 

        mRoadProgress++; 
        break; 

    case 3: 
        std::cout << "\nThe road opens beneath an ancient tree.\n"; 
        std::cout << "\nPaths branch off in a couple of directions.\n"; 
        std::cout << "\nThe heroes have reached the Crossroads.\n"; 

        mCurrentLocationId = 2; 
        mRoadProgress++; 
        break; 

    default:
        break;
    }
}

//=====================================
//   v.03 Random Encounter System 
//=====================================

void Game::CheckRandomEncounter() {
    //Retrieve players current location. 
    Location currentLocation = mLocationCatalog.GetLocationByID(mCurrentLocationId);

    //Retrieve the encounter settings. 
    int encounterChance = currentLocation.GetEncounterChance();

    const std::vector<Enemy>& enemies = currentLocation.GetEnemies();

    //Safe locations or emtpy rooms cannot trigger combat. 
    if (encounterChance <= 0 || enemies.empty()) {
        return; 
    }
    //Create  a random number generator. 
    static std::mt19937 generator(std::random_device{}()); 

    //Roll a number between 1 and 100. 
    std::uniform_int_distribution<int> encounterRoll(1, 100);

    int roll = encounterRoll(generator); 

    //No encounter occured. 
    if (roll > encounterChance) {
        return; 
    }
    //Randomly select an enemy from this locations pool. 
    std::uniform_int_distribution<int> enemyRoll(0, static_cast<int>(enemies.size()) - 1); 

    int enemyIndex = enemyRoll(generator); 

    //Create a fresh copy so combat does not modify the encounter pool. 
    Enemy selectedEnemy = enemies[enemyIndex]; 

    std::cout << "\nAn enemy approaches1\n"; 

    //Start combat using the existing combat system. 
    CombatResult result = mCombatSystem.StartCombat(OraKanu, Mbatha, selectedEnemy); 

    //Handle defeat. 
    if (result == CombatResult::Defeat) {
        std::cout << "\nYour journey has come to an end.\n"; 
        IsGameRunning = false; 
    }
}
