#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

#include "Clue.h"
using namespace std;

string toLowerCopy(const string& s) {
    string out = s;
    for (char& ch : out) {
        // Fill: Convert each character to lowercase
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return out;
}

int triggerClue(char symbol, vector<Clue>& clues) {
    //logic to trigger the clue based on the symbol

    string userAnswer;
    int score = 0;
    int clueIndex = -1;
    int attemptCount = 0;

    for (int i = 0; i < clues.size(); i++) {
        if (clues[i].getSymbol() == symbol) {
            //trigger the clue
            cout << "Clue: " << clues[i].getQuestion() << endl;
            break;
            clueIndex = i;
        }
    }

    while(attemptCount != clues[clueIndex].getMaxAttempts()){
        cin >> userAnswer;
        if(toLowerCopy(userAnswer) == toLowerCopy(clues[clueIndex].getCorrectAnswer())){
            cout << "Correct! You earn " << clues[clueIndex].getPoints() << " points!" << endl;
            score += clues[clueIndex].getPoints();
            break;
        } else {
            cout << "Incorrect! Try again:" << endl;
            score -= clues[clueIndex].getPoints()/clues[clueIndex].getMaxAttempts();
        }
        attemptCount++;
    }
    
    return score;  
}

int main() {

    vector<Clue> clues;
    ifstream file("clues.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    while (!file.eof()) {
        file >> symbol >> question >> correctAnswer >> maxAttempts >> points;
        Clue clue(symbol, question, correctAnswer, maxAttempts, points);
        clues.push_back(clue);
    }

    file.close();

    

    return 0;
}



