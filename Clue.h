#ifndef CLUE_H
#define CLUE_H
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Clue {
  private:
    char symbol;
    string question, correctAnswer;
    int points, maxAttempts;
    bool isCompleted = false;

  public:
//constructor
    Clue(char s, string q, string ans, int attempts, int pts) {
        symbol = s;
        question = q;
        correctAnswer = ans;
        maxAttempts = attempts;
        points = pts;
        isCompleted = false;
    }

//getter methods
    char getSymbol() {
        return symbol;
    }

    string getQuestion(){
        return question;
    }

    string getCorrectAnswer(){
        return correctAnswer;
    }

    int getPoints(){
        return points;
    }

    bool isSolved(){
        return isCompleted;
    }

//logic functions
    bool checkAnswer(string& playerGuess);
    static string toLowerCopy(const string& s)

};
