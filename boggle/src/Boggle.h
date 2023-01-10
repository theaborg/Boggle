// Jessica Kjellin jeskj559, Thea Borg thebo 717
// The header file for the Boggle class.
// Declares the functions used by the Boggle class,
// such as finding neighbours to a letter and shuffling the board

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "cube.h"
#include <unordered_set>
#include <set>
#include "grid.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    unordered_set<char> alphabet = {'a','b','c','d','e','f','g','h','i',
                                    'j','k','l','m','n','o','p','q','r',
                                    's','t','u','v','w','x','y','z'};
    /*
     * Boggle constructor, one of which takes in a string as input
     * */
    Boggle();
    Boggle(string s);

    /*
     * Boggle destructor
     * */
    ~Boggle();

    /*
     * Boggle copy constructor
     * */
    Boggle(const Boggle& other);

    /*
     * Boggle assignment operator
     * */
    Boggle& operator=(const Boggle& other);

    /*
     * vi använder inte denna
     * */
    //string forceRightFormat(string letters, unordered_set<char> alphabet);

    /*
     * Board getter
     * */
    Grid<cube*> getBoard();

    /*
     * Cube getter, get the cube at the position
     * */
    cube* getCube(int x, int y);

    /*
     * Returns the position of a letter in the board
     * */
    vector<pair<int, int>> findLetter(char letter);

    /*
     * Returns a set of the neighbouring letters
     * */
    unordered_set<char> findLettersNearby(set<int> position);

    /*
     * Get the words from the lexicon
     * */
    Lexicon* getWords();

    /*
     * Shuffles the board with new sides of the cubes
     * */
    void shuffleBoard();

    bool confirmFormat(string letters, unordered_set<char> alphabet);

    bool controlWord(string word, Lexicon* words,
                     unordered_set<string> foundWords);

    bool findLetters(pair<int, int> position, string word);

    bool findWord(string word);

    unordered_set<string> findAllLetters(int x, int y, string& word, Lexicon* dict);

    unordered_set<string> findAllWords(Lexicon* dict);



private:
    Grid<cube*> board;
    const string DICTIONARY_FILE = "EnglishWords.dat";
    Lexicon* words = new Lexicon(DICTIONARY_FILE);

};

#endif
