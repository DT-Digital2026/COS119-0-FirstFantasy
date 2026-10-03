#include <iostream>
#include <limits>

#include "Menu.h"

int Menu::DisplayMainMenu()
{
    //Game main menu. This is the first pass, will make the menu more detailed once we have the code working. Greybox first. Then polish.
    std::cout << "====================================================================" << std::endl;
    std::cout << "                First Fantasy: The Dark Continent                   " << std::endl;
    std::cout << "====================================================================" << std::endl;

    std::cout << "1. New Game" << std::endl; //Allows new game start. 
    std::cout << "2. Load Game" << std::endl; //Loads previously saved game. 
    std::cout << "3. How to Play" << std::endl; //Dictates instructions on how to play. 
    std::cout << "4. Lore" << std::endl; //Displays character information, location information, and beastiary.
    std::cout << "5. Credits" << std::endl; //Shows credits.
    std::cout << "6. Exit" << std::endl; //Exits the game. 

    int choice = GetValidMenuChoice(1, 6);

    return choice;
}

int Menu::GetValidMenuChoice(int minChoice, int maxChoice)
{
    int choice;

    while (true)
    {
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Checks if the user entered something other than an integer.
        if (std::cin.fail())
        {
            std::cout << "Invalid input. Please enter an integer between "
                << minChoice << " and " << maxChoice << "." << std::endl;

            // Clears the error state caused by invalid input.
            std::cin.clear();

            // Removes the invalid input remaining in the input buffer.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Checks if the integer is outside the allowed menu range.
        else if (choice < minChoice || choice > maxChoice)
        {
            std::cout << "Invalid choice. Please enter a number between "
                << minChoice << " and " << maxChoice << "." << std::endl;
        }

        // Input is an integer AND within the allowed range.
        else
        {
            return choice;
        }
    }
}

void Menu::HowToPlay() {
    std::cout << "======================================================================================================================" << std::endl;
    std::cout << "                                                     How to Play                                                      " << std::endl;
    std::cout << "======================================================================================================================" << std::endl;

    std::cout << "Exploration: " << std::endl;
    std::cout << "Choose numbered options to explore locations, investigate your surroundings, speak with NPC's, and progress the story." << std::endl;

    std::cout << "Combat: " << std::endl;
    std::cout << "Enjoy turn based combat.Choose attacks, abilities, defensive actions, or items during your turn." << std::endl;

    std::cout << "Enemy Attacks:" << std::endl;
    std::cout << "Enemies may telegraph their attacks.Pay attention to their behavior and choose how to react." << std::endl;

    std::cout << "Dodge: " << std::endl;
    std::cout << "Attempt to avoid an incoming attack." << std::endl;

    std::cout << "Guard: " << std::endl;
    std::cout << "Reduce damage from an incoming attack." << std::endl; 

    std::cout << "Parry: " << std::endl;
    std::cout << "A riskier defensive option that may interrupt and enemy attack and create an opportunity to counter." << std::endl;

    std::cout << "Health: " << std::endl;
    std::cout << "HP Represents a players health.If the entire party reaches 0, the party is defeated." << std::endl;

    std::cout << "Ase: " << std::endl;
    std::cout << "In Yoruban cosmology, Ase is the divine life force that flows through all.In First Fantasy, Ase replaces mana as the resource to spend on abilities." << std::endl;

    std::cout << "Inventory: " << std::endl;
    std::cout << "Collect and use consumables, weapons, armor, and important story items throughout the adventure." << std::endl;

    std::cout << "Saving: " << std::endl;
    std::cout << "Save your progress during exploration and load your saved adventure from the main menu." << std::endl;

    std::cout << "Press enter to return to the main menu..."; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cin.get(); 
    }

void Menu::DisplayLore() {
    bool LoreMenuRunning = true; 

    while (LoreMenuRunning) {
        std::cout << "==============================================================================================" << std::endl;
        std::cout << "                                             Lore                                             " << std::endl;
        std::cout << "==============================================================================================" << std::endl;

        std::cout << "1. The World" << std::endl;
        std::cout << "2. Characters" << std::endl;
        std::cout << "3. Locations" << std::endl;
        std::cout << "4. Bestiary" << std::endl;
        std::cout << "5. Return to Main Menu" << std::endl;

        int choice = GetValidMenuChoice(1, 5);
        
        switch (choice) {
        case 1:
            std::cout << "==============================================================================================" << std::endl;
            std::cout << "                                       World Lore                                             " << std::endl;
            std::cout << "==============================================================================================" << std::endl;            break;

            std::cout << "The World of Akantha " << std::endl;
            std::cout << "Akantha is an isolated and largely unexplored continent." << std::endl;
            std::cout << "At its heart is an enormous mountain, that dominates the " << std::endl;
            std::cout << "landscape and can be seen from much of the continent. " << std::endl;
            std::cout << "This great mountain is known to be the home of the gods. " << std::endl;

            std::cout << "\n";

            std::cout << "The Creator:" << std::endl;
            std::cout << "Before the peoples of Akantha, before its kingdoms, and before " << std::endl;
            std::cout << "the beings mortals would come to call gods, there was the creator." << std::endl;

            std::cout << "The Creator alone posses the power to truly create life." << std::endl;

            std::cout << "Life in Akantha carries the breath of the Creator, the divine " << std::endl;
            std::cout << "essence from which living things draw their existence." << std::endl;

            std::cout << "\n";

            std::cout << "Ase" << std::endl;
            std::cout << "Ase is the spiritual force that flows through all life. " << std::endl;
            std::cout << "Those capable of of weidling Ase can use it to influence the world around them. " << std::endl;
            std::cout << "Ase can heal, strengthen, transform and shape reality." << std::endl;
            std::cout << "But those that weild Ase cannot create true life. " << std::endl;

            std::cout << "\n";

            std::cout << "The Aseki" << std::endl;
            std::cout << "The Aseki were the celestial servants of the Creator." << std::endl;
            std::cout << "They possessed tremendous power and could shape the work of the Creator, " << std::endl;
            std::cout << "but they did not possess the power to create life from nothing." << std::endl;

            std::cout << "For some, this limitation became a source of resentment." << std::endl;

            std::cout << "\n";

            std::cout << "The First Rebellion" << std::endl;
            std::cout << "Some of the Aseki attemtped to create. They were successful...somewhat." << std::endl;
            std::cout << "Their creations lived, but not as intended." << std::endl;
            std::cout << "Without the Creators breath, their attempts became distorted and monstrous." << std::endl;
            std::cout << "Rather than accept their limitations, the rebellious Aseki turned against the Creator." << std::endl;

            std::cout << "\n";

            std::cout << "The Fall" << std::endl;
            std::cout << "the rebellious Aseki were cast out of the Heavens down to Akantha. They made their home" << std::endl;
            std::cout << "upon the great mountain at the center of the continent. In time, the people livnig beneath them" << std::endl;
            std::cout << "came to regard these powerful beings as gods." << std::endl;

            std::cout << "\n";

            std::cout << "Orisha and Abosom" << std::endl;
            std::cout << "Distrust stirred even among the Aseki that were cast down to Akantha. The first rift caused two great factions" << std::endl;
            std::cout << "The Orisha and the Abosom. Angered at being cast out, the Orisha accepted the fact that they could not create." << std::endl;
            std::cout << "The Orisha chose to use their power to protect, guide, and shape the creation that already exists." << std::endl;

            std::cout << "The Abosom struggled with this limitation. Their resentment toward their inability to create has driven" << std::endl;
            std::cout << "them towards destruction and attempts to reshape creation in their image." << std::endl;

            std::cout << "\n";

            std::cout << "The Divine Conflict" << std::endl;
            std::cout << "The conflict between the Orisha and the Abosom is not simply a war between good and evil." << std::endl;
            std::cout << "Both possess immense power, both can alter the lives of mortals, but they disagree over what" << std::endl;
            std::cout << "beings with such power are meant to do with it." << std::endl;

            std::cout << "\n";

            std::cout << "Akantha Today" << std::endl;
            std::cout << "The consequences of this ancient conflict can still be found throughout Akantha." << std::endl;
            std::cout << "Monsters roam the wilderness, ancient powers still influence the land. Mortals" << std::endl;
            std::cout << "worship beings whose true origins have been obscured by generations of myth and tradition." << std::endl;

            std::cout << "And above it all stands the great mountain at the center of Akantha, home to those the mortals call gods." << std::endl;
            std::cout << "And as our story begins, a new god is born...not Orisha nor Abosom..." << std::endl;

            std::cout << "\n";

            std::cout << "Press Enter to return to Lore." << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            break; 

        case 2:
            std::cout << "==============================================================================================" << std::endl;
            std::cout << "                                   Character Lore                                             " << std::endl;
            std::cout << "==============================================================================================" << std::endl;              break;

            std::cout << "Ora'Kanu - Voice of the Storm" << std::endl;

            std::cout << "Ora is one of the younger Orisha's that walk the lands of Akantha." << std::endl;

            std::cout << "Unlike the older powers of the continent, Ora accepts that the Orisha were not" << std::endl;
            std::cout << "intended to create life. " << std::endl;

            std::cout << "Instead, she believed their power exists to shape, protect, and maintain" << std::endl;
            std::cout << "the creation that was entrusted to them." << std::endl;

            std::cout << "\n";

            std::cout << "Ora'Kanu posses a powerful connection to the forces of weather and the natural world. " << std::endl;
            std::cout << "Usigng Ase, the lifeforce of the world, she can call upon the winds, the rains," << std::endl;
            std::cout << "and the fury of the storm." << std::endl;

            std::cout << "Her bracers help her focus this power, allowing her to direct the forces of the storm against her enemies." << std::endl;

            std::cout << "\n";

            std::cout << "Her command of Ase makes Ora'Kanu extremely powerful, her reliance upon it, also requires her to carfully" << std::endl;
            std::cout << "her strength during prolonged battles." << std::endl;

            std::cout << "\n";

            std::cout << "M'Batha - Father of Dhambe" << std::endl;

            std::cout << "M'Batha is a powerful warrior whose fighting style taught others the traditions of Dhambe." << std::endl;
            std::cout << "His body is his weapon." << std::endl;

            std::cout << "\n"; 

            std::cout << "One hand, wrapped and prepared for striking delivers his most powerful attacks." << std::endl;
            std::cout << "His other hand serves as his shield, protecting him while allowing for devasting counters on his enemies." << std::endl;

            std::cout << "M'Batha can channel his Ase through his martial techniques, but he does not depend on it to the extent" << std::endl;
            std::cout << "that Ora does. His strength comes more from discipline, endurance, timing, and the ability to withstand" << std::endl;
            std::cout << "punishment that would overwhelm a mortal fighter." << std::endl;

            std::cout << "\n"; 

            std::cout << "Where Ora'Kanu commands the battlefield through supernatural power, M'batha meets danger face to face." << std::endl;
            std::cout << "Together, the two balance supernatural power with physical strength, each capable of protecting" << std::endl;
            std::cout << "the other with their own abilities are weakest." << std::endl;

            std::cout << "\n"; 

            std::cout << "Press Enter to return to the Lore Menu." << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            break; 

        case 3:
            std::cout << "==============================================================================================" << std::endl;
            std::cout << "                                    Location Lore                                             " << std::endl;
            std::cout << "==============================================================================================" << std::endl;              break;

            std::cout << "The Continent of Akantha" << std::endl;

            std::cout << "Akantha is a vast and ancient continent shaped by both the natural world and the powers that have" << std::endl;
            std::cout << "walked upon it. Dense forests, sprawling wilderness, rivers, mountains, and isolated settlements" << std::endl;
            std::cout << "stretch across its land. Much of Akantha remains wild, and traveling beyond the safety of" << std::endl; 
            std::cout << "its settlements is rarely without danger." << std::endl;

            std::cout << "\n"; 

            std::cout << "The Coastal Village" << std::endl;

            std::cout << "Along the coast of Akantha stands a small village whose people have survived through cooperation," << std::endl;
            std::cout << "tradition, and respect for the dangers beyond their homes. Though distant from the larger settlements" << std::endl;
            std::cout << "of Akantha, the village has endured through fishing, hunting, trade, and the guidance of its elders." << std::endl;

            std::cout << "Recently however, an uneasy fear has settled over the village." << std::endl;

            std::cout << "Children have begun to disappear, old agreements have been broke and whispers of something lurking beyond the" << std::endl;
            std::cout << "village have begun to spread." << std::endl;

            std::cout << "\n"; 

            std::cout << "The Wilderness" << std::endl;

            std::cout << "Beyond the village stretches an untamed wilderness where the paths of covolization quickly disappear. Snakes" << std::endl;
            std::cout << "hide beneath the undergrowth, hyenas hunt in packs, and powerful predators stalk those who wander too far from " << std::endl;
            std::cout << "the safety of the road. River's crossing the wilderness bring dangers of their own, with crocodiles waiting beneath" << std::endl;
            std::cout << "otherwise peaceful waters." << std::endl;

            std::cout << "\n"; 

            std::cout << "Bloodroot Hollow" << std::endl;

            std::cout << "Deep within the wilderness lies a place the people of the surrounding settlements rarely speak of openly." << std::endl;
            std::cout << "Bloodroot hollow is an ancient region of twisted roots, darkened earth, and dense forest where sunlight struggles" << std::endl;
            std::cout << "to reach the ground. Bats gather in unnatural numbers and travelers are warned against entering the hollow after" << std::endl;
            std::cout << "sunset. Stories claim that something ancient dwells beneath the canopy." << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            break; 

        case 4:
            std::cout << "==============================================================================================" << std::endl;
            std::cout << "                                       Beastiary                                              " << std::endl;
            std::cout << "==============================================================================================" << std::endl;              break;

            std::cout << "Venomous Snake" << std::endl;
            std::cout << "Common throughout the wilds of Akantha, venomous snakes rely on speed and dangerous bites to bring down prey." << std::endl;

            std::cout << "Hyena" << std::endl;
            std::cout << "Aggresive pack hunters that roam the wilderness. A loan hyena is dangerous, a pack is far worse." << std::endl; 

            std::cout << "Bat" << std::endl;
            std::cout << "Common across Akantha, especially in caves and dense forests. Large gatherings signal danger nearby." << std::endl;

            std::cout << "Leopard" << std::endl;
            std::cout << "Powerful and patient predators that stalk prey from concealment." << std::endl;

            std::cout << "Crocodile" << std::endl;
            std::cout << "Massive reptiles found along river's and wetlands that strike with brutal bite force." << std::endl;

            std::cout << "Vampire Bat" << std::endl;
            std::cout << "An unnatrual relative of the common bat with a voracious hunger for blood." << std::endl;

            std::cout << "Bat Swarm" << std::endl;
            std::cout << "A mass of bats capable of overwhelming prey through sheer numbers." << std::endl;

            std::cout << "Bonsam Thrall" << std::endl;
            std::cout << "Servants bound to the will of the bonsam, whatever lives they once possessed have been abandoned." << std::endl;

            std::cout << "Bonsam" << std::endl;
            std::cout << "Ancient vampiric beings feared across the plains. Their true nature is surrounded by myth and legend." << std::endl;

            std::cout << "Elder Bonsam" << std::endl;
            std::cout << "Those that rule the Bonsam." << std::endl;
            
            std::cout << "Press Enter to return to the Lore Menu." << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            break; 

        case 5:
            LoreMenuRunning = false; 
            break;

        }
    }
 }
void Menu::DisplayCredits() {
    std::cout << "==============================================================================================" << std::endl;
    std::cout << "                                    Credits                                                   " << std::endl;
    std::cout << "==============================================================================================" << std::endl;              

    std::cout << "First Fantasy: The Dark Continent." << std::endl;

    std::cout << "Created and Developed by....and literally everything else: Brad Watson" << std::endl;
}

bool Menu::ConfirmExit()
{
    std::cout << "Are you sure you want to exit?" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. No" << std::endl;

    int choice = GetValidMenuChoice(1, 2);

    if (choice == 1)
    {
        std::cout << "Thank you for playing." << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}