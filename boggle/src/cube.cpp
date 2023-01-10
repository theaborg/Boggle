#include "cube.h"
#include "Boggle.cpp"
#include "iostream"

cube::cube(string c)
{
    int random = rand() % 5 + 1;
    letter = c.at(random);
    this->combination = c;
    setVisited(false);
}

cube::cube(char l, string c) {
    letter = l;
    combination = c;
    setVisited(false);
}

cube* cube::clone()const{
    cube* other = new cube(this->letter, this->combination);
    return other;
}

char cube::getLetter() {
    return letter;
}

void cube::setLetter(char l){
    this->letter = l;
}

void cube::setCombination(string combo){
    this->combination = combo;
}

void cube::setVisited(bool val){
    this->visited = val;
}

bool cube::getVisited(){
    return visited;
}

void cube::changeLetter(){
    int random = rand() % 5 + 1;
    letter = combination.at(random);
}

