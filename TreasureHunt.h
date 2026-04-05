
#include <vector>
#include <string>
using namespace std;

class TreasureHunt {
private:
    // 🔹 Data Members
    vector<vector<char>> mapGrid;   // 2D map
    int playerRow;
    int playerCol;
    vector<string> clues;           
    int totalScore;
    bool gameOver;

public:
    // Constructor
    TreasureHunt();

    //  Game Setup
    void loadMap(const string& filename);
    void loadClues(const string& filename);
    void initializePlayer(int startRow, int startCol);

    // Game Actions
    void displayMap() const;
    void movePlayer(char direction);   // 'W', 'A', 'S', 'D'
    void checkForClue();
    void updateScore(int points);

    //  Game State
    bool isGameOver() const;
    int getScore() const;

    // Main Game Loop
    void playGame();
};

#endif
