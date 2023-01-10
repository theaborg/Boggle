// Jessica Kjellin jeskj559, Thea Borg thebo 717
// this file contains the main game loop and functionality
// to find words in the game board

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include <unordered_set>
#include <fstream>
#include "vector.h"
#include "shuffle.h"

using namespace std;

void draw(Boggle& boggle) {
    for (int i = 0; i < boggle.BOARD_SIZE; i++) {
        for (int j = 0; j < boggle.BOARD_SIZE; j++) {
            if (boggle.getBoard().inBounds(i, j)) {
                std::cout<<" [";
                std::cout<< boggle.getCube(i, j)->getLetter();
                std::cout<<"] ";
            }
        }
        std::cout<<endl;
    }
}

/*
 * The main game loop
 * */
void playOneGame(Boggle& boggle) {
    unordered_set<string> foundWords;
    unordered_set<string> foundWordsAI;
    string guess;
    boggle.shuffleBoard();
    Lexicon* words = boggle.getWords();
    int score = 0;
    int scoreAI = 0;
    if (!yesOrNo("Do you want to generate a random board? ")){
        string combo;
        bool correctInput = false;
        while (!correctInput) {
            cout<<"Please enter a string of exactly 16 letters."<<endl;
            getline(cin, combo);
            correctInput = boggle.confirmFormat(combo, boggle.alphabet);
        }
        combo = toUpperCase(combo);
        Boggle other(combo);
        boggle = other;
    }
    bool gameOn = true;
    while (gameOn) {
        clearConsole();
        cout << "It's your turn!" << endl;
        draw(boggle);
        cout << "Your words (" << foundWords.size() << "): ";
        for(auto const &w: foundWords) {
            cout << w << " ";
        }
        cout << "Your score: " << score << endl;
        cout << "Enter a word (or press enter to end your turn): " << endl;
        getline(cin, guess);
        guess = toUpperCase(guess);
        if(boggle.controlWord(guess, words, foundWords) && boggle.findWord(guess)){
            int increase = guess.size() - 3;
            score+=increase;
            foundWords.insert(guess);
        }
        else if(guess == "") {
            gameOn = false;
        }
    }
    cout<<"My words: ";
    for(string wordAI: boggle.findAllWords(words)){
        if(foundWords.find(wordAI) == foundWords.end()){
            int increase = wordAI.size()-3;
            scoreAI += increase;
            cout<<wordAI << ", ";
        }
    }
    cout<<endl;
    cout<<"My score: " << scoreAI << endl;
    cout<<"Your score: " << score <<endl;
    foundWords.clear();
    foundWordsAI.clear();
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
