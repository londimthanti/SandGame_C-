#ifndef LIBSPACE_H_INCLUDED
#define LIBSPACE_H_INCLUDED

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

namespace SandSpace{
    //The game World dimensions
    const int TOTAL_ROWS = 20;
    const int TOTAL_COLS = 20;

    //Error Constants
    const int ERR_ARGS = -1;
    const int ERR_RANGE = -2;
    const int ERR_CONVERSION = -3;

    //Store Features
    const int PLAYER = 0;
    const int NORMAL_SOIL = 1;
    const int WELL = 2;
    const int DESERT = 3;

    //Feature Characters
    const char FEATURES[] = {'P', '.', 'W', 'D'};

    typedef int game_Matrix[TOTAL_ROWS][TOTAL_COLS];

    //Functions
    int ArgToInt(string strArgument);   //To convert string to Integer
    int genRandomNum(int intLowerBound, int intUpperBound); //Generate Random Numbers within Range
    void initGameWorld(game_Matrix gameWorld);  //Initialize the Game World
    void printWorld(const game_Matrix gameWorld);   //Print the Game World
    void movePlayer(game_Matrix gameWorld, char chInput);   //Move the Player
    void placeWell(game_Matrix gameWorld, int &noWells);     //Place Well
    void findPlayer(int &intPlayerRow, int &intPlayerCol, game_Matrix gameWorld);   //Find the Player
    bool validMove(int intDRow, int intDCol); //Is Move Valid
    void simulateGame(game_Matrix gameWorld);   //Simulate Game
    void generateDeserts(game_Matrix gameWorld);    //Generate Deserts during simulation
    void checkDeserts(int intRow, int intCol, game_Matrix gameWorld, int &intChanceToBeDesert);    //Check deserts round a cell
    bool validDistanceFromWell(int intRow, int intCol, game_Matrix gameWorld);   //Checking if position is a valid distance from the well
    int calcDistance(int gridRow, int gridCol, int intCellRow, int intCellCol);
}

#endif // LIBSPACE_H_INCLUDED