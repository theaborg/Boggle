// Jessica Kjellin jeskj559, Thea Borg thebo 717
// this file contains the functionality of the boggle class

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <unordered_set>
#include <set>
#include <iostream>

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle()
{
    board.resize(BOARD_SIZE, BOARD_SIZE);
    unordered_set<string> usedCombos;
    int k =0;
    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            cube* tempCube = new cube(CUBES[k]);
            this->board.set(i,j,tempCube);
            k++;
        }
    }
    shuffle(board);
}

Boggle::Boggle(string letters){
    board.resize(BOARD_SIZE, BOARD_SIZE);
    int k = 0;
    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            char c = letters.at(k);
            cube* tempCube = new cube(c, CUBES[k]);
            this->board.set(i, j, tempCube);
            k++;
        }
    }
}

Boggle::Boggle(const Boggle& other){
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++) {
            this->board.set(i, j, other.board.get(i, j));
        }
    }
}

Boggle::~Boggle(){
    for(cube* cube: this->board){
        delete cube;
    }
    delete this->words;
}

Boggle&Boggle::operator=(const Boggle& other) {
    for(cube* cube: this->board){
        delete cube;
    }
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++) {
            this->board.set(i, j, other.board.get(i,j)->clone());
        }
    }
    return *this;
}

cube* Boggle::getCube(int x, int y) {
    return board.get(x, y);
}

Lexicon* Boggle::getWords(){
    return words;
}

Grid<cube*> Boggle::getBoard(){
    return board;
}

void Boggle::shuffleBoard(){
    for(cube* cube: this->board){
        cube->changeLetter();
    }
    shuffle(this->board);
}

unordered_set<char> Boggle::findLettersNearby(set<int> position){
    unordered_set<char> letters;
    int x = *position.begin();
    int y = *position.end();
    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j<= y+1; j++) {
            if (this->getBoard().inBounds(x, y)) {
                if(!(i == x && j == y)){
                    letters.insert(board.get(i,j)->getLetter());
                }
            }
        }
    }
    return letters;
}

vector<pair<int, int>> Boggle::findLetter(char letter){
    pair<int, int> coords;
    vector<pair<int, int>> placings;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(board.get(i,j)->getLetter() == letter){
                coords.first = i;
                coords.second = j;
                placings.insert(placings.end(), coords);
            }
        }
    }
    return placings;
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
bool Boggle::confirmFormat(string letters, unordered_set<char> alphabet){
   if(letters.size() != 16){
       return false;
   }
   bool correctForm = true;
   for(unsigned i = 0; i < letters.size(); i++){
       char letter = letters.at(i);
       if(alphabet.find(letter) == alphabet.end()){
           correctForm = false;
       }
   }
   return correctForm;
}

/*
 * Checks that a string is a valid word
 */
bool Boggle::controlWord(string word, Lexicon* words,
                 unordered_set<string> foundWords){
    if(word.size() < 4){
        return false;
    }
    word = toUpperCase(word);
    auto finder = foundWords.find(word);
    if(finder != foundWords.end()){
        return false;
    }
    return  words->contains(word);
}


/*
 * goes through the board to find letters in a guessed word (according to Boggle rules),
 * returns true if all the letters are found
 */
bool Boggle::findLetters(pair<int, int> position, string word){
    int x = position.first;
    int y = position.second;
    this->getCube(x,y)->setVisited(true);
    if(word.size() == 0){
        this->getCube(x,y)->setVisited(false);
        return true;
    }
    for (int i = x-1; i < x+2; i++) {
        for (int j = y-1; j < y+2; j++) {
            if(this->getBoard().inBounds(i,j)){
                if(this->getCube(i, j)->getLetter() == word.at(0) && !this->getCube(i, j)->getVisited()){
                    pair<int, int> newPos = {i, j};
                    string newWord = word.substr(1);
                    bool found = findLetters(newPos, newWord);
                    if(found){
                        this->getCube(i, j)->setVisited(false);
                        return found;
                    }
                }

                this->getCube(i, j)->setVisited(false);
            }
        }
    }
    this->getCube(x, y)->setVisited(false);
    return false;
}

/*
 * finds a word in the Boggle board with the help of findLetters
 * returns true if the word can be formed on the Boggle board
 * (according to the Boggle rules)
 * */
bool Boggle::findWord(string word){
    vector<pair<int, int>> positions = findLetter(*word.begin());
    if(positions.empty()){
        return false;
    }
    string newWord = word.substr(1);
    for(auto position:positions) {
        if(this->findLetters(position, newWord)){
            return true;
        }
    }
    return false;
}

/*
 * Finds the letters around the starting cube and checks if it makes a valid word
 * */
unordered_set<string> Boggle::findAllLetters(int x, int y, string& word, Lexicon* dict){
    string newWord;
    unordered_set<string> foundWords;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            newWord = word;
            if (this->getBoard().inBounds(x+i, y+j) && !this->getCube(x+i, y+j)->getVisited()){
                newWord.push_back(this->getCube(x+i, y+j)->getLetter());
                this->getCube(x+i, y+j)->setVisited(true);
                if(controlWord(newWord, dict, foundWords)){
                    foundWords.insert(newWord);
                }
                if(dict->containsPrefix(newWord)) {
                    for(string foundWord: findAllLetters(x+i, y+j, newWord, dict)){
                        foundWords.insert(foundWord);
                    }
                }
                this->getCube(x+i, y+j)->setVisited(false);
            }
        }
    }
    return foundWords;
}

/*
 * Finds all the words that can be formed in the Boggle board with the help of findAllLetters by
 * starting at one cube and visiting all the letters around it
 * */
unordered_set<string> Boggle::findAllWords(Lexicon* dict){
    unordered_set<string> words;
    string word;
    for(int i = 0; i < this->BOARD_SIZE; i++){
        for(int j= 0; j < this->BOARD_SIZE; j++){
            word.clear();
            char c = this->getCube(i,j)->getLetter();
            word.push_back(c);
            this->getCube(i,j)->setVisited(true);
            for(string foundWord: findAllLetters(i, j, word, dict)){
                words.insert(foundWord);
            }
            this->getCube(i, j)->setVisited(false);
        }
    }
    return words;
}
