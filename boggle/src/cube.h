// Jessica Kjellin jeskj559, Thea Borg thebo 717
// The header file for the cube class.
// Declares the functions used by the cube class,
// such as getting and setting a letter in a cube

#ifndef CUBE_H
#define CUBE_H
#include <vector>
#include <string>
using namespace std;


class cube
{
private:
    char letter;
    bool visited;
    string combination;

public:
    /*
     * Cube constructors, one where the cube only gets a combination of letters
     * and one where we decide the letter of one of the sides of the cube
     * */
    cube(string com);
    cube(char l, string com);

    /*
     * clone function
     * */
    cube* clone() const;

    /*
     * Letter getter
     * */
    char getLetter();

    /*
     * Letter setter
     * */
    void setLetter(char l);

    /*
     * Combination setter
     * */
    void setCombination(string combo);

    /*
     * Visited getter
     * */
    bool getVisited();

    /*
     * Visited setter
     * */
    void setVisited(bool val);

    /*
     * changes the shown letter of the cube
     * */
    void changeLetter();
};

#endif // CUBE_H
