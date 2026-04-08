#include "TreasureHunt.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;

// Helper function for case-insensitive answer checking
static string toLowerCopy(const string& s) {
    string out = s;
    for (char& ch : out) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return out;
}

// Constructor
TreasureHunt::TreasureHunt() {
    playerRow = 0;
    playerCol = 0;
    totalScore = 0;
    gameOver = false;
}

// Load map from file
void TreasureHunt::loadMap(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cout << "Error: Could not open map file: " << filename << endl;
        gameOver = true;
        return;
    }

    mapGrid.clear();
    string line;
    bool foundPlayer = false;

    while (getline(file, line)) {
        vector<char> row;

        for (int i = 0; i < line.length(); i++) {
            char tile = line[i];

            if (tile == '@') {
                if (foundPlayer) {
                    cout << "Error: Multiple player start positions found!" << endl;
                    gameOver = true;
                    return;
                }
                foundPlayer = true;
                playerRow = mapGrid.size();
                playerCol = i;
            }

            row.push_back(tile);
        }

        mapGrid.push_back(row);
    }

    if (!foundPlayer) {
        cout << "Error: No player start position '@' found in map!" << endl;
        gameOver = true;
    }
}

// Load clues from file
void TreasureHunt::loadClues(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cout << "Error: Could not open clues file: " << filename << endl;
        gameOver = true;
        return;
    }

    clues.clear();
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            clues.push_back(line);
        }
    }
}

// Optional manual player initialization
void TreasureHunt::initializePlayer(int startRow, int startCol) {
    if (startRow >= 0 && startRow < mapGrid.size() &&
        startCol >= 0 && startCol < mapGrid[0].size()) {
        playerRow = startRow;
        playerCol = startCol;
    }
}

// Display map
void TreasureHunt::displayMap() const {
    cout << "\n===== UT CAMPUS TREASURE HUNT =====" << endl;
    cout << "Score: " << totalScore << endl;
    cout << "Controls: W = Up, A = Left, S = Down, D = Right, Q = Quit\n" << endl;

    for (int r = 0; r < mapGrid.size(); r++) {
        for (int c = 0; c < mapGrid[r].size(); c++) {
            if (r == playerRow && c == playerCol) {
                cout << '@';
            } else {
                cout << mapGrid[r][c];
            }
        }
        cout << endl;
    }

    cout << endl;
}

// Move player
void TreasureHunt::movePlayer(char direction) {
    direction = toupper(direction);

    int newRow = playerRow;
    int newCol = playerCol;

    if (direction == 'W') {
        newRow--;
    } else if (direction == 'S') {
        newRow++;
    } else if (direction == 'A') {
        newCol--;
    } else if (direction == 'D') {
        newCol++;
    } else {
        cout << "Invalid move! Use W, A, S, or D." << endl;
        return;
    }

    // Prevent out-of-bounds movement
    if (newRow < 0 || newRow >= mapGrid.size() ||
        newCol < 0 || newCol >= mapGrid[0].size()) {
        cout << "You can't move outside the map!" << endl;
        return;
    }

    // Prevent walking through walls
    if (mapGrid[newRow][newCol] == '#') {
        cout << "You hit a wall! Try another direction." << endl;
        return;
    }

    // Move player
    playerRow = newRow;
    playerCol = newCol;

    // Check if player landed on a landmark
    checkForClue();
}

// Update score
void TreasureHunt::updateScore(int points) {
    totalScore += points;
}

// Trigger clue if standing on landmark
void TreasureHunt::checkForClue() {
    char tile = mapGrid[playerRow][playerCol];

    // Only trigger on landmark tiles
    if (tile != 'T' && tile != 'P' && tile != 'H' &&
        tile != 'U' && tile != 'G' && tile != 'F') {
        return;
    }

    string* matchedClue = nullptr; // pointer requirement

    for (int i = 0; i < clues.size(); i++) {
        if (!clues[i].empty() && clues[i][0] == tile) {
            matchedClue = &clues[i];
            break;
        }
    }

    if (matchedClue == nullptr) {
        cout << "No clue found for this landmark!" << endl;
        return;
    }

    // Parse clue line
    stringstream ss(*matchedClue);
    string symbol, question, correctAnswer, attemptsStr, pointsStr;

    getline(ss, symbol, '|');
    getline(ss, question, '|');
    getline(ss, correctAnswer, '|');
    getline(ss, attemptsStr, '|');
    getline(ss, pointsStr, '|');

    int maxAttempts = stoi(attemptsStr);
    int points = stoi(pointsStr);

    cout << "\n=== LANDMARK CHALLENGE ===" << endl;
    cout << question << endl;

    bool solved = false;
    string userAnswer;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        cout << "Attempt " << attempt << "/" << maxAttempts << ": ";
        getline(cin, userAnswer);

        if (toLowerCopy(userAnswer) == toLowerCopy(correctAnswer)) {
            cout << "Correct! +" << points << " points!" << endl;
            updateScore(points);
            solved = true;
            break;
        } else {
            cout << "Incorrect!" << endl;
            updateScore(-2); // lose 2 points per wrong attempt
            cout << "-2 points" << endl;
        }
    }

    if (!solved) {
        cout << "Out of attempts! The correct answer was: " << correctAnswer << endl;
    }

    // Mark landmark as completed so it can't be used twice
    mapGrid[playerRow][playerCol] = '.';

    // Lose condition
    if (totalScore < -10) {
        gameOver = true;
        cout << "\nYour score dropped too low. Game over!" << endl;
    }
}

// Check if game ended
bool TreasureHunt::isGameOver() const {
    return gameOver;
}

// Get score
int TreasureHunt::getScore() const {
    return totalScore;
}

// Main game loop
void TreasureHunt::playGame() {
    if (gameOver) return;

    int totalLandmarks = 0;

    // Count total landmarks at start
    for (int r = 0; r < mapGrid.size(); r++) {
        for (int c = 0; c < mapGrid[r].size(); c++) {
            char tile = mapGrid[r][c];
            if (tile == 'T' || tile == 'P' || tile == 'H' ||
                tile == 'U' || tile == 'G' || tile == 'F') {
                totalLandmarks++;
            }
        }
    }

    char move;

    while (!gameOver) {
        displayMap();

        int remainingLandmarks = 0;
        for (int r = 0; r < mapGrid.size(); r++) {
            for (int c = 0; c < mapGrid[r].size(); c++) {
                char tile = mapGrid[r][c];
                if (tile == 'T' || tile == 'P' || tile == 'H' ||
                    tile == 'U' || tile == 'G' || tile == 'F') {
                    remainingLandmarks++;
                }
            }
        }

        if (remainingLandmarks == 0) {
            gameOver = true;
            break;
        }

        cout << "Enter move: ";
        cin >> move;

        if (toupper(move) == 'Q') {
            gameOver = true;
            break;
        }

        movePlayer(move);
    }

    // Final stats
    int remainingLandmarks = 0;
    for (int r = 0; r < mapGrid.size(); r++) {
        for (int c = 0; c < mapGrid[r].size(); c++) {
            char tile = mapGrid[r][c];
            if (tile == 'T' || tile == 'P' || tile == 'H' ||
                tile == 'U' || tile == 'G' || tile == 'F') {
                remainingLandmarks++;
            }
        }
    }

    int completedLandmarks = totalLandmarks - remainingLandmarks;
    double percentComplete = 0.0;

    if (totalLandmarks > 0) {
        percentComplete = (static_cast<double>(completedLandmarks) / totalLandmarks) * 100.0;
    }

    cout << "\n===== GAME OVER =====" << endl;
    cout << "Final Score: " << totalScore << endl;
    cout << "Landmarks Completed: " << completedLandmarks << "/" << totalLandmarks << endl;
    cout << "Completion: " << percentComplete << "%" << endl;

    if (completedLandmarks == totalLandmarks && totalScore >= 0) {
        cout << "You Win! You completed the UT Campus Treasure Hunt!" << endl;
    } else {
        cout << "You Lose! Better luck next time." << endl;
    }
}

int main() {
    TreasureHunt game;
    game.loadMap("map.txt");
    game.loadClues("clues.txt");
    game.playGame();
    return 0;
}