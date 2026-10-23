#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>
#define NOMINMAX
#include <windows.h>

#include "Menu.h"

namespace
{
    constexpr WORD FF_GOLD = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    constexpr WORD FF_GREEN = FOREGROUND_GREEN;
    constexpr WORD FF_IVORY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    constexpr WORD FF_RED = FOREGROUND_RED | FOREGROUND_INTENSITY;

    void SetTextColor(WORD color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
}
// Public color helper for use throughout the game.
void Menu::SetTextColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        static_cast<WORD>(color)
    );
}

//Pause for enter to support ClearScreen during combat. 

void Menu::PauseForEnter()
{
    SetTextColor(FF_GOLD);

    std::cout << "\n====================================================\n";
    std::cout << "              PRESS ENTER TO CONTINUE               \n";
    std::cout << "====================================================\n";

    SetTextColor(FF_IVORY);

    std::string input;
    std::getline(std::cin, input);
}

//v.05 Method to clear screen
void Menu::ClearScreen()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    DWORD cellsWritten;

    if (!GetConsoleScreenBufferInfo(console, &screenInfo)) {
        return;
    }

    DWORD consoleSize =
        screenInfo.dwSize.X * screenInfo.dwSize.Y;

    COORD topLeft = { 0, 0 };

    FillConsoleOutputCharacterA(console, ' ', consoleSize, topLeft, &cellsWritten);

    FillConsoleOutputAttribute(console, screenInfo.wAttributes, consoleSize, topLeft, &cellsWritten);

    SetConsoleCursorPosition(console, topLeft);
}
int Menu::DisplayMainMenu()
{
    Menu::ClearScreen();
    //v.05 - Polished main menu presentation.
    std::cout << "\n";
    
    SetTextColor(FF_GREEN); 
    std::cout << "====================================================\n";

    SetTextColor(FF_GOLD);
    std::cout << "                                                    \n";
    std::cout << "                 F I R S T                          \n";
    std::cout << "               F A N T A S Y                        \n";
    std::cout << "                                                    \n";
    std::cout << "          T H E  D A R K  C O N T I N E N T         \n";
    std::cout << "                                                    \n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n";

    SetTextColor(FF_IVORY);
    std::cout << "                                                    \n";
    std::cout << "    1.  NEW GAME                                    \n";
    std::cout << "    2.  LOAD GAME                                   \n";
    std::cout << "    3.  HOW TO PLAY                                 \n";
    std::cout << "    4.  LORE                                        \n";
    std::cout << "    5.  CREDITS                                     \n";
    std::cout << "    6.  EXIT                                        \n";
    std::cout << "                                                    \n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n";

    SetTextColor(FF_GOLD);
    std::cout << "             A JOURNEY INTO AKANTHA                 \n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n\n";
    SetTextColor(FF_IVORY);


    int choice = GetValidMenuChoice(1, 6);

    return choice;
}

int Menu::GetValidMenuChoice(int minChoice, int maxChoice)
{
    std::string input;

    while (true)
    {
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);
    try
    {
        // Tracks how many characters stoi successfully converts.
        std::size_t processedCharacters;

        // Attempts to convert the user's string input into an integer.
        int choice = std::stoi(input, &processedCharacters);

        // Checks whether the entire input was converted.
        // Prevents something like "2banana" from being accepted as 2.
        if (processedCharacters != input.length())
        {
            throw std::invalid_argument("Input contains non-numeric characters.");
        }

        // Checks if the integer is outside the allowed menu range.
        if (choice < minChoice || choice > maxChoice)
        {
            std::cout << "Invalid choice. Please enter a number between "
                << minChoice << " and " << maxChoice << "." << std::endl;
        }
        else
        {
            // Input is an integer AND within the allowed range.
            return choice;
        }
    }
    catch (const std::invalid_argument&)
    {
        // stoi could not convert the input into a valid integer.
        std::cout << "Invalid input. Please enter an integer between "
            << minChoice << " and " << maxChoice << "." << std::endl;
    }
    catch (const std::out_of_range&)
    {
        // The number was too large or too small for an int.
        std::cout << "Invalid input. Please enter an integer between "
            << minChoice << " and " << maxChoice << "." << std::endl;
    }
}
}

void Menu::HowToPlay() {
    Menu::ClearScreen();
    //Overall self explanitory. Created a how to play menu with instructions on basic gameplay.
    SetTextColor(FF_GREEN);
    std::cout << "======================================================================================================================" << std::endl;
   
    SetTextColor(FF_GOLD);
    std::cout << "                                                     How to Play                                                      " << std::endl;

    SetTextColor(FF_GREEN);
    std::cout << "======================================================================================================================" << std::endl;

    SetTextColor(FF_GOLD);
    std::cout << "  EXPLORATION\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Choose numbered options to explore locations,\n";
    std::cout << "  investigate surroundings, speak with NPCs,\n";
    std::cout << "  and progress through the story.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  COMBAT\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Battles are turn-based. Choose attacks,\n";
    std::cout << "  special abilities, or items to defeat enemies.\n";
    std::cout << "  Each character has unique combat strengths.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  HEALTH (HP)\n";
    SetTextColor(FF_IVORY);
    std::cout << "  HP represents a character's health.\n";
    std::cout << "  If the entire party reaches 0 HP, you lose.\n";
    std::cout << "  Use healing items or abilities to recover.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  ASE\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Ase is the spiritual energy used to perform\n";
    std::cout << "  special abilities. Powerful abilities consume\n";
    std::cout << "  more Ase, so manage it carefully.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  STATUS EFFECTS\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Certain attacks and abilities apply effects:\n\n";

    std::cout << "    WET    - Enhances lightning-based attacks.\n";
    std::cout << "    POISON - Causes damage over time.\n";
    std::cout << "    BLEED  - Causes damage over time.\n";
    std::cout << "    STUN   - Prevents an enemy from acting.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  ABILITY COMBINATIONS\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Some abilities become more effective when\n";
    std::cout << "  combined with status effects.\n\n";

    std::cout << "  Example: Ora'Kanu can use Raincall to apply\n";
    std::cout << "  WET to an enemy. Following up with Lightning\n";
    std::cout << "  Strike deals increased damage to WET targets.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  INVENTORY\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Collect and use healing items, weapons, armor,\n";
    std::cout << "  and important story items throughout the game.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  COWRIES\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Cowries are the currency of Akantha.\n";
    std::cout << "  Earn them by defeating enemies and spend\n";
    std::cout << "  them at merchants for useful equipment.\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  SAVING\n";
    SetTextColor(FF_IVORY);
    std::cout << "  Save your progress during exploration or\n";
    std::cout << "  from the gameplay menu. Load your adventure\n";
    std::cout << "  from the main menu.\n\n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n";

    SetTextColor(FF_GOLD);
    std::cout << "          PRESS ENTER TO RETURN                     \n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n\n";

    SetTextColor(FF_IVORY);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cin.get(); 
    }

void Menu::DisplayLore() {
    Menu::ClearScreen();
    //Created a lore menu to detial some of the information about the games world.
    bool LoreMenuRunning = true; 

    while (LoreMenuRunning) {
        SetTextColor(FF_GREEN);
        std::cout << "==============================================================================================" << std::endl;

        SetTextColor(FF_GOLD);
        std::cout << "                                             Lore                                             " << std::endl;

        SetTextColor(FF_GREEN);
        std::cout << "==============================================================================================" << std::endl;

        SetTextColor(FF_IVORY);
        std::cout << "1. THE WORLD" << std::endl;
        std::cout << "2. CHARACTERS" << std::endl;
        std::cout << "3. LOCATIONS" << std::endl;
        std::cout << "4. BESTIARY" << std::endl;
        std::cout << "5. RETURN TO MAIN MENU" << std::endl;

        int choice = GetValidMenuChoice(1, 5);
        
        switch (choice) {
        case 1:
            Menu::ClearScreen();
            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;

            SetTextColor(FF_GOLD);
            std::cout << "                                       World Lore                                             " << std::endl;

            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;            

            SetTextColor(FF_GOLD);
            std::cout << "THE WORLD OF AKANTHA\n";

            SetTextColor(FF_IVORY);
            std::cout << "Akantha is an isolated and largely unexplored continent.\n";
            std::cout << "At its heart stands an enormous mountain, visible from\n";
            std::cout << "much of the surrounding land. For generations, its\n";
            std::cout << "inhabitants have been worshipped as gods.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "THE CREATOR\n";

            SetTextColor(FF_IVORY);
            std::cout << "Before the peoples of Akantha, before its kingdoms,\n";
            std::cout << "and before the beings mortals would call gods, there\n";
            std::cout << "was the Creator.\n\n";

            std::cout << "The Creator alone possesses the power to bring forth\n";
            std::cout << "true life. Every living thing carries the Creator's\n";
            std::cout << "breath, the divine essence of its existence.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "ASE\n";

            SetTextColor(FF_IVORY);
            std::cout << "Ase is the spiritual force flowing through all life.\n";
            std::cout << "Those capable of wielding Ase can influence the\n";
            std::cout << "world around them.\n\n";

            std::cout << "Ase can heal, strengthen, transform, and shape\n";
            std::cout << "creation. Yet even its greatest wielders cannot\n";
            std::cout << "create true life from nothing.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "THE ASEKI\n";

            SetTextColor(FF_IVORY);
            std::cout << "The Aseki were the celestial servants of the Creator.\n";
            std::cout << "They possessed tremendous power and could reshape\n";
            std::cout << "the Creator's work, but could not create true life.\n\n";

            std::cout << "For some, this limitation became a source of resentment.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "THE FIRST REBELLION\n";

            SetTextColor(FF_IVORY);
            std::cout << "Some among the Aseki attempted to create life.\n";
            std::cout << "Their efforts succeeded, but only in part.\n\n";

            std::cout << "Their creations lived, yet lacked the Creator's\n";
            std::cout << "breath. What emerged was distorted, unnatural,\n";
            std::cout << "and monstrous.\n\n";

            std::cout << "Rather than accept their limitations, the rebellious\n";
            std::cout << "Aseki turned against the Creator.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "THE FALL\n";

            SetTextColor(FF_IVORY);
            std::cout << "The rebellious Aseki were cast from the heavens\n";
            std::cout << "down to Akantha. There, they established themselves\n";
            std::cout << "upon the great mountain at the continent's center.\n\n";

            std::cout << "In time, the mortals living beneath them came to\n";
            std::cout << "worship these powerful beings as gods.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "ORISHA AND ABOSOM\n";

            SetTextColor(FF_IVORY);
            std::cout << "Even among the fallen Aseki, distrust began to grow.\n";
            std::cout << "A great division emerged, giving rise to two\n";
            std::cout << "powerful factions: the Orisha and the Abosom.\n\n";

            std::cout << "The Orisha accepted that they could not create true\n";
            std::cout << "life. Though angered by their exile, they chose to\n";
            std::cout << "protect, guide, and shape existing creation.\n\n";

            std::cout << "The Abosom could not accept this limitation.\n";
            std::cout << "Their resentment drove them toward destruction\n";
            std::cout << "and attempts to remake creation in their image.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "THE DIVINE CONFLICT\n";

            SetTextColor(FF_IVORY);
            std::cout << "The conflict between the Orisha and Abosom is not\n";
            std::cout << "simply a war between good and evil.\n\n";

            std::cout << "Both possess immense power. Both can influence the\n";
            std::cout << "lives of mortals. Yet they disagree over what beings\n";
            std::cout << "with such power are meant to do with it.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "AKANTHA TODAY\n";

            SetTextColor(FF_IVORY);
            std::cout << "The consequences of this ancient conflict can still\n";
            std::cout << "be felt throughout Akantha.\n\n";

            std::cout << "Monsters roam the wilderness. Ancient powers continue\n";
            std::cout << "to influence the land. Mortals worship beings whose\n";
            std::cout << "true origins have been obscured by generations of\n";
            std::cout << "myth and tradition.\n\n";

            std::cout << "In a small fishing village, desperate prayers call\n";
            std::cout << "upon powers far greater than those who offer them.\n";
            std::cout << "And beyond the village, something unnatural stirs\n";
            std::cout << "within the depths of Bloodroot Hollow.\n\n";

            SetTextColor(FF_IVORY);
            std::cout << "\n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n";

            SetTextColor(FF_GOLD);
            std::cout << "          PRESS ENTER TO RETURN                     \n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n\n";

            SetTextColor(FF_IVORY);

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            break; 

        case 2:
            Menu::ClearScreen();
            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;

            SetTextColor(FF_GOLD);
            std::cout << "                                   Character Lore                                             " << std::endl;

            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;              

            SetTextColor(FF_GOLD);
            std::cout << "ORA'KANU - VOICE OF THE STORM\n";

            SetTextColor(FF_IVORY);
            std::cout << "Ora'Kanu is one of the younger Orisha who walk the\n";
            std::cout << "lands of Akantha. Unlike many of the older powers,\n";
            std::cout << "she accepts that the Orisha were never meant to\n";
            std::cout << "create life.\n\n";

            std::cout << "Instead, she believes their power exists to shape,\n";
            std::cout << "protect, and preserve the creation entrusted to them.\n\n";

            std::cout << "Ora'Kanu possesses a powerful connection to the\n";
            std::cout << "weather and the natural world. By channeling Ase,\n";
            std::cout << "she can summon the winds, call upon the rains,\n";
            std::cout << "and unleash the fury of the storm.\n\n";

            std::cout << "Her enchanted bracers help focus this power,\n";
            std::cout << "allowing her to direct the forces of nature\n";
            std::cout << "against those who threaten Akantha.\n\n";

            std::cout << "In battle, Ora'Kanu can summon rain to drench\n";
            std::cout << "her enemies before striking them with lightning.\n";
            std::cout << "Her command of the storm makes her formidable,\n";
            std::cout << "but her abilities demand careful management of Ase.\n\n";

            std::cout << "Where others see destruction in the storm,\n";
            std::cout << "Ora'Kanu sees the power to protect life.\n\n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "M'BATHA - FATHER OF DHAMBE\n";

            SetTextColor(FF_IVORY);
            std::cout << "M'Batha is a powerful warrior whose mastery of\n";
            std::cout << "combat helped establish the traditions of Dhambe.\n";
            std::cout << "His body is his weapon, and his discipline is\n";
            std::cout << "the foundation of his strength.\n\n";

            std::cout << "One hand, wrapped and prepared for striking,\n";
            std::cout << "delivers his most devastating blows. His other\n";
            std::cout << "hand serves as his shield, allowing him to\n";
            std::cout << "withstand attacks and answer with brutal counters.\n\n";

            std::cout << "M'Batha channels Ase through his martial techniques,\n";
            std::cout << "but he does not depend upon it as heavily as\n";
            std::cout << "Ora'Kanu. His greatest strengths come from\n";
            std::cout << "discipline, endurance, and physical power.\n\n";

            std::cout << "His mastery of Dhambe allows him to deliver\n";
            std::cout << "powerful strikes and combinations, overwhelming\n";
            std::cout << "enemies through strength and relentless pressure.\n\n";

            std::cout << "He can withstand punishment that would overwhelm\n";
            std::cout << "an ordinary mortal, standing firm when others fall.\n\n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "TWO HEROES, ONE PURPOSE\n";

            SetTextColor(FF_IVORY);
            std::cout << "Where Ora'Kanu commands the battlefield through\n";
            std::cout << "supernatural power, M'Batha meets danger face to face.\n\n";

            std::cout << "One commands the fury of the storm.\n";
            std::cout << "The other embodies the strength of the warrior.\n\n";

            std::cout << "Together, they balance spiritual power with\n";
            std::cout << "physical might, each protecting the other\n";
            std::cout << "where their individual strengths fall short.\n\n";

            SetTextColor(FF_IVORY);

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n";

            SetTextColor(FF_GOLD);
            std::cout << "          PRESS ENTER TO RETURN                     \n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n\n";

            SetTextColor(FF_IVORY);

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            break; 

        case 3:
            Menu::ClearScreen();
            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;

            SetTextColor(FF_GOLD);
            std::cout << "                                    Location Lore                                             " << std::endl;

            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;  

            SetTextColor(FF_GOLD);
            std::cout << "THE FISHING VILLAGE\n";

            SetTextColor(FF_IVORY);
            std::cout << "A modest settlement rests at the edge of Akantha's\n";
            std::cout << "wilderness. Its people survive through fishing,\n";
            std::cout << "trade, and the guidance of their elders.\n\n";

            std::cout << "The village center connects the homes and gathering\n";
            std::cout << "places of its inhabitants. At the wharf, fishermen\n";
            std::cout << "prepare their boats and tend to their daily catch.\n\n";

            std::cout << "The local merchant offers supplies to travelers,\n";
            std::cout << "while the chief oversees the village's affairs.\n";
            std::cout << "Within a secluded hut, the shaman tends to matters\n";
            std::cout << "of the spiritual world.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "THE ROADS OF AKANTHA\n";

            SetTextColor(FF_IVORY);
            std::cout << "Worn roads wind through the wilderness, connecting\n";
            std::cout << "isolated settlements and forgotten pathways.\n\n";

            std::cout << "An ancient crossroads divides the routes toward\n";
            std::cout << "the forest and river. Beyond the safety of the\n";
            std::cout << "village, dangerous predators roam freely.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "THE WILDERNESS\n";

            SetTextColor(FF_IVORY);
            std::cout << "Dense vegetation and towering trees surround the\n";
            std::cout << "village. Beneath their canopy, predators stalk\n";
            std::cout << "the overgrown trails.\n\n";

            std::cout << "Abandoned campsites hint at travelers who may never\n";
            std::cout << "have returned. Along the riverbanks, the wilderness\n";
            std::cout << "conceals both danger and forgotten discoveries.\n\n";

            SetTextColor(FF_GOLD);
            std::cout << "BLOODROOT HOLLOW\n";

            SetTextColor(FF_IVORY);
            std::cout << "Deep within the wilderness lies Bloodroot Hollow,\n";
            std::cout << "a place where something unnatural has taken hold.\n\n";

            std::cout << "Twisted roots and dark stone mark its entrance.\n";
            std::cout << "Beyond them stands the Withered Grove, where dying\n";
            std::cout << "trees bleed crimson sap into the corrupted earth.\n\n";

            std::cout << "Deeper still, a bone-strewn path winds between\n";
            std::cout << "ancient trees marked with mysterious symbols.\n";
            std::cout << "Few would willingly venture into such a place.\n\n";

            SetTextColor(FF_IVORY);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n";

            SetTextColor(FF_GOLD);
            std::cout << "          PRESS ENTER TO RETURN                     \n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n\n";


            break; 

        case 4:
            Menu::ClearScreen();
            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;

            SetTextColor(FF_GOLD);
            std::cout << "                                       Beastiary                                              " << std::endl;

            SetTextColor(FF_GREEN);
            std::cout << "==============================================================================================" << std::endl;              
            
            SetTextColor(FF_GOLD);
            std::cout << "Venomous Snake" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Common throughout the wilds of Akantha, venomous snakes rely on speed and dangerous bites to bring down prey." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Hyena" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Aggresive pack hunters that roam the wilderness. A loan hyena is dangerous, a pack is far worse." << std::endl; 
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Bat" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Common across Akantha, especially in caves and dense forests. Large gatherings signal danger nearby." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Leopard" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Powerful and patient predators that stalk prey from concealment." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Crocodile" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Massive reptiles found along river's and wetlands that strike with brutal bite force." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Vampire Bat" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "An unnatrual relative of the common bat with a voracious hunger for blood." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Bat Swarm" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "A mass of bats capable of overwhelming prey through sheer numbers." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Bonsam Thrall" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Servants bound to the will of the bonsam, whatever lives they once possessed have been abandoned." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Bonsam" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Ancient vampiric beings feared across the plains. Their true nature is surrounded by myth and legend." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GOLD);
            std::cout << "Elder Bonsam" << std::endl;
            SetTextColor(FF_IVORY);
            std::cout << "Those that rule the Bonsam." << std::endl;
            std::cout << "\n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n";

            SetTextColor(FF_GOLD);
            std::cout << "          PRESS ENTER TO RETURN                     \n";

            SetTextColor(FF_GREEN);
            std::cout << "====================================================\n\n";

            SetTextColor(FF_IVORY);            

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            break; 

        case 5:
            LoreMenuRunning = false; 
            break;

        }
    }
 }
void Menu::DisplayCredits()
{
    Menu::ClearScreen();

    SetTextColor(FF_GREEN);
    std::cout << "\n====================================================\n";

    SetTextColor(FF_GOLD);
    std::cout << "                      CREDITS                       \n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n\n";

    SetTextColor(FF_IVORY);
    std::cout << "  FIRST FANTASY: THE DARK CONTINENT\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  CREATED AND DEVELOPED BY\n";

    SetTextColor(FF_IVORY);
    std::cout << "  Brad Watson\n\n";

    SetTextColor(FF_GOLD);
    std::cout << "  Programming, Design, Writing, and Everything Else\n";

    SetTextColor(FF_IVORY);
    std::cout << "  One developer. One vision. One adventure.\n\n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n";

    SetTextColor(FF_GOLD);
    std::cout << "              PRESS ENTER TO RETURN                 \n";

    SetTextColor(FF_GREEN);
    std::cout << "====================================================\n\n";

    SetTextColor(FF_IVORY);

    std::cin.get();
}

bool Menu::ConfirmExit(){
    //Exit game function. 
    SetTextColor(FF_IVORY);
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