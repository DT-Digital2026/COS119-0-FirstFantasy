# Milestone 4 — Final Project Documentation

**Project:** First Fantasy: The Dark Continent  
**Language:** C++  
**Development Environment:** Visual Studio  
**Project Type:** Console-Based Role-Playing Game

## 1. Final Features Added

During the final development milestone, I focused on connecting the different systems in First Fantasy and preparing the project for submission.

The game uses a menu-driven interface that allows players to interact with the game world and access its available features.

The project includes work on the following systems:

- **Character Management:** Player characters have attributes such as health, attack, defense, level, and Ase (the game's magic resource).
- **Enemy Management:** Enemy classes provide the foundation for encounters and combat interactions.
- **Menu Navigation:** The main menu connects the player to the game's available systems, with options for starting a game, loading a game, viewing instructions, reading lore, viewing credits, and exiting.
- **Game Structure:** Separate classes manage game initialization, character information, enemies, and menu functionality.

**Final features to confirm before submission:**

- [ ] Character leveling and experience progression -- Cut to save time.
- [x] Save and load functionality
- [x] Inventory and equipment management
- [x] Combat encounters and victory/defeat handling
- [x] Exploration and location navigation

## 2. Refactoring Improvements

Throughout development, I worked on organizing the project into separate header (`.h`) and source (`.cpp`) files.

This helped separate class declarations from method implementations and made the project easier to navigate and maintain.

I also focused on keeping responsibilities separated between the Menu, Game, Character, and Enemy classes rather than placing all game logic inside `main.cpp`.

As the project grew, I reviewed how the classes interacted and worked toward keeping the overall structure organized and easier to expand.

## 3. Bug Fixes

A major focus during development was identifying and resolving issues that prevented the program from compiling or behaving correctly.

Areas addressed included:

- Improving menu input validation to reject invalid selections.
- Handling input errors so incorrect entries do not immediately terminate the program.
- Reviewing menu navigation to ensure selections call the intended methods.
- Reviewing character attribute setters to keep values within valid ranges.
- Testing class connections and program flow as additional systems were introduced.

These changes helped improve the program's reliability and overall stability.

## 4. Usability Updates

I focused on making the console interface easier for players to understand and navigate.

Improvements included:

- Organizing menu options into a clear, numbered format.
- Providing instructions for available player actions.
- Improving the presentation of character information and attributes.
- Adding ways for players to return from informational menus.
- Improving handling of invalid menu input.

The goal was to create an interface that players could navigate without needing to understand how the underlying code works.

## 5. Final Testing and Validation

Before submission, the project should be tested to confirm that its completed features work as intended.

Final verification includes:

- [x] The project builds successfully in Visual Studio.
- [x] The program launches and displays the main menu.
- [x] Menu selections call the correct functions.
- [x] Invalid input is handled correctly.
- [x] Completed gameplay features function as expected.
- [x] The application can exit normally.
- [x] Final screenshots are saved in `/images`.
- [x] Final changes are committed and pushed to GitHub.

## 6. Final Reflection

Developing First Fantasy has helped me improve my understanding of object-oriented programming and how multiple classes work together within a larger application.

One of the biggest challenges was learning how to connect individual systems into a functioning game. Building a class or writing a method is one thing, but making everything communicate correctly requires additional planning, testing, and debugging.

I also gained experience using GitHub to manage changes and track project development.

Moving forward, I want to continue improving the game's architecture and expanding its gameplay systems while applying the programming and project management skills I've developed throughout this course.