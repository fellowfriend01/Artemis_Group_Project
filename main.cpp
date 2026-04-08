#include <iostream>
// Include the header file for the TreasureHunt class to access its methods
#include "TreasureHunt.h"

int main()
{
    std::cout << "Welcome to the UT Campus Treasure Hunt!\n"
              << std::endl;

    // Instantiate the game object using the required TreasureHunt class
    TreasureHunt game;

    // Start the main game loop.
    // It is highly recommended that game.startGame() handles calling game.loadMap()
    // and game.loadClues() before dropping the user into the movement loop.
    game.startGame();

    // Once the game loop finishes (either by completing landmarks or losing points),
    // display the final score and win/lose message.
    game.displayFinalResult();

    return 0;
}