#include "libSpace.h"

namespace SandSpace{

    //To convert string to Integer
    int ArgToInt(string strArgument){
        int intNum = 0;
        stringstream ss {strArgument};
        ss >> intNum;
        //if fail
        if(ss.fail()){
            cerr << "Could not convert to integer" << endl;
            exit(ERR_CONVERSION);
        }
        return intNum;
    }

    //Generate Random Numbers within Range
    int genRandomNum(int intLowerBound, int intUpperBound){
        int intRange = intUpperBound - intLowerBound  + 1;
        return rand() % intRange + intLowerBound;
    }

    //Initialize the Game World
    void initGameWorld(game_Matrix gameWorld){
        //Only Contains Normal Soil
        for(int r = 0; r < TOTAL_ROWS; r++){
            for(int c = 0; c < TOTAL_COLS; c++){
                gameWorld[r][c] = NORMAL_SOIL;
            }
        }

        //Randomly place Player in Game World
        int intNoRows = TOTAL_ROWS;
        int intNoCols = TOTAL_COLS;
        int intPlayerRow = genRandomNum(0, intNoRows - 1);
        int intPlayerCol = genRandomNum(0, intNoCols - 1);
        gameWorld[intPlayerRow][intPlayerCol] = PLAYER;
    }

    //Print the Game World
    void printWorld(const game_Matrix gameWorld){
        for(int r = 0; r < TOTAL_ROWS; r++){
            for(int c = 0; c < TOTAL_COLS; c++){
                cout << FEATURES[gameWorld[r][c]] << "";
            }
            cout << endl;
        }
    }

    //Move the Player
    void movePlayer(game_Matrix gameWorld, char chInput){
        //Find the player's current position
        int intPlayerRow = -1;
        int intPlayerCol = -1;
        findPlayer(intPlayerRow, intPlayerCol, gameWorld);

        //Destination Row and Col
        int intPlayerDRow = intPlayerRow;
        int intPlayerDCol = intPlayerCol;

        //Change / Define Destination
        switch(tolower(chInput)){
        case 'w':   //Move Up
            intPlayerDRow--;
            break;
        case 's':   //Move Down
            intPlayerDRow++;
            break;
        case 'a':   //Move Left
            intPlayerDCol--;
            break;
        case 'd':   //Move Right
            intPlayerDCol++;
            break;
        }

        //Actual Movement of the Player
        if(validMove(intPlayerDRow, intPlayerDCol)){
            gameWorld[intPlayerDRow][intPlayerDCol] = PLAYER;
            gameWorld[intPlayerRow][intPlayerCol] = NORMAL_SOIL;
        }
    }

    //Place Well
    void placeWell(game_Matrix gameWorld, int &noWells){
        if(noWells > 0){
            //Find out where the player is
            int intPlayerRow = -1;
            int intPlayerCol = -1;
            findPlayer(intPlayerRow, intPlayerCol, gameWorld);

            //Place Player in Random position round well
            int randomPosition = genRandomNum(0, 3);
            switch(randomPosition){
            case 0:
                movePlayer(gameWorld, 'w');
                break;
            case 1:
                movePlayer(gameWorld, 's');
                break;
            case 2:
                movePlayer(gameWorld, 'a');
                break;
            case 3:
                movePlayer(gameWorld, 'd');
                break;
            }

            //Place Well
            gameWorld[intPlayerRow][intPlayerCol] = WELL;
            //Decrement Well Count
            noWells--;
        }
    }

    //Find the Player
    void findPlayer(int &intPlayerRow, int &intPlayerCol, game_Matrix gameWorld){
        for(int r = 0; r < TOTAL_ROWS; r++){
            for(int c = 0; c < TOTAL_COLS; c++){
                if(gameWorld[r][c] == PLAYER){
                    intPlayerRow = r;
                    intPlayerCol = c;
                    return;
                }
            }
        }
    }

    //Is Move Valid
    bool validMove(int intDRow, int intDCol){
        if(intDRow >= 0 && intDRow < TOTAL_ROWS && intDCol >= 0 && intDCol < TOTAL_COLS){
            return true;
        }
        return false;
    }

    //Simulate Game
    void simulateGame(game_Matrix gameWorld){
        //Generate Deserts
        generateDeserts(gameWorld);
    }

    //Generate Deserts during simulation
    void generateDeserts(game_Matrix gameWorld){
        //Create a duplicate of game World
        int tempGameWorld[TOTAL_ROWS][TOTAL_COLS];
        for(int r = 0; r < TOTAL_ROWS; r++){
            for(int c = 0; c < TOTAL_COLS; c++){
                tempGameWorld[r][c] = gameWorld[r][c];
            }
        }

        //Loop thru Temp Game World, make changes and update on old gameworld
        for(int r = 0; r < TOTAL_ROWS; r++){
            for(int c = 0; c < TOTAL_COLS; c++){
                if(tempGameWorld[r][c] == NORMAL_SOIL){
                    //Chance Variable
                    int intChanceToBeDesert = 0;

                    //Check deserts around me
                    checkDeserts(r, c, tempGameWorld, intChanceToBeDesert);

                    //
                    int intRandomNum = genRandomNum(0, 100);
                    if(intRandomNum <= intChanceToBeDesert){
                        //Check distance of place from a well
                        if(validDistanceFromWell(r, c, tempGameWorld)){
                            gameWorld[r][c] = DESERT;
                        }
                    }
                }
            }
        }
    }

     //Check deserts round a cell
    void checkDeserts(int intRow, int intCol, game_Matrix gameWorld, int &intChanceToBeDesert){
        for(int i = (intRow - 1); i < (intRow + 1); i++){
            for(int j = (intCol - 1); j < (intCol + 1); j++){
                //Check if within bounds
                if(validMove(i, j) && i != intRow && j != intCol){
                    //Check if desert
                    if(gameWorld[i][j] == DESERT){
                        intChanceToBeDesert += 4;
                    }
                }
            }
        }
    }

    //Checking if position is a valid distance from the well
    bool validDistanceFromWell(int intRow, int intCol, game_Matrix gameWorld){
        for(int r = 0; r < TOTAL_ROWS; r++){
            for(int c = 0; c < TOTAL_COLS; c++){
                if(gameWorld[r][c] == WELL){
                    if(calcDistance(r, c, intRow, intCol) == 5){
                        return false;
                    }
                }
            }
        }
        return true;
    }

    //Calculate Distance (using Euclidean / Pythagorean distance formula)
    int calcDistance(int gridRow, int gridCol, int intCellRow, int intCellCol){
        int intResult = 0;
        int XDiff = intCellCol - gridCol;
        int YDiff = intCellRow - gridRow;
        int XResult = XDiff * XDiff;
        int YResult = pow(YDiff, 2);
        intResult = sqrt(XResult + YResult);
        return intResult;
    }
}
