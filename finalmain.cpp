#include <iostream>
#include "TreasureHunt.h"
using namespace std;

int main(){
    cout << "Welcome to the UT Campus Treasure Hunt!" << endl;

    TreasureHunt game;
    game.loadMap("map.txt");
    game.loadClues("clues.txt");
    game.playGame();

    return 0;
}
