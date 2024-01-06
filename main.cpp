#include <iostream>
#include "libSpace.h"

using namespace std;
using namespace SandSpace;

int main(int argc, char* argv[])
{
    //Seed the random number generator
    srand(time(0));

    //No Wells
    int intNoWells = 0;

    //Check the argument count
    if(argc != 2){
        cerr << "Wrong number of arguments, please enter <No of Wells>" << endl;
        exit(ERR_ARGS);
    }

    intNoWells = ArgToInt(argv[1]);

    //cout << "No Wells: " << intNoWells << endl;

    int GameMatrix[TOTAL_ROWS][TOTAL_COLS];

    //Initialize Game World
    initGameWorld(GameMatrix);

    //The main Loop
    bool blnContinue = true;
    char chInput = '\0';

    do{
        //Clear the screen
        system("cls");
        //Print Game World
        printWorld(GameMatrix);
        //Menu
        cout << "No of Wells left: " << intNoWells << endl;
        cout << "PLEASE CHOOSE AN OPTION" << endl;
        cout << "W - Move Up" << endl;
        cout << "S - Move Down" << endl;
        cout << "A - Move Left" << endl;
        cout << "D - Move Right" << endl;
        cout << "P - Place Well" << endl;
        cout << "X - Exit the Game" << endl;

        cin >> chInput;

        switch(tolower(chInput)){
        case 'w':
        case 's':
        case 'a':
        case 'd':
            if(intNoWells > 0){
                movePlayer(GameMatrix, chInput);
            }else{
                simulateGame(GameMatrix);
            }
            break;
        case 'p':
            if(intNoWells > 0){
                placeWell(GameMatrix, intNoWells);
            }else{
                simulateGame(GameMatrix);
            }
            break;
        case 'x':
            cout << "Thanks for playing the Game" << endl;
            blnContinue = false;
            break;
        default:
            cerr << "Incorrect Entry, Please Retry" << endl;
            cin.ignore(100, '\n');
        }

    }while(blnContinue);

    return 0;
}
