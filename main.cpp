#include <stdio.h>
#include <MacTypes.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

std::string reset = "\033[0m";
std::string blue = "\u001b[34;5;1m";

int boardSize = 4;
int board[4][4];
int score = 0;
string highScore;
bool reachedGoal;
bool changesMade;

int randomNum() {
    int randomNumber;
    randomNumber = rand() % 10;
    if (randomNumber == 10) {
        return randomNum();
    } else {
        return randomNumber;
    }
}

void moveTiles(int vert, int horiz, int moveVert, int moveHoriz) {
    if (board[vert][horiz] == 0 && board[vert + moveVert][horiz + moveHoriz] != 0) {
        board[vert][horiz] = board[vert + moveVert][horiz + moveHoriz];
        board[vert + moveVert][horiz + moveHoriz] = 0;
        printf("Moving (%d,%d) to (%d,%d).\n", (vert + moveVert), (horiz + moveHoriz), vert, horiz);
        changesMade = true;
    }
}

void combineTiles(int vert, int horiz, int moveVert, int moveHoriz) {
    if (board[vert][horiz] == board[vert + moveVert][horiz + moveHoriz] && board[vert][horiz] != 0) {
        board[vert][horiz] = (board[vert][horiz] * 2);
        //The vert and horiz values are meant to be swapped here.
        board[vert + moveVert][horiz + moveHoriz] = 0;
        printf("Adding (%d,%d) to (%d,%d).\n", (vert + moveVert), (horiz + moveHoriz), vert, horiz);
        score = score + board[vert][horiz];
        if(board[vert][horiz] == 16){
            reachedGoal = true;
        }
        changesMade = true;
    }
}

//This checks to see if the board is full, and returns true if full
Boolean checkFull(){
    Boolean isFull = false;
    for(int i = 0; i<(boardSize-1); i = i + 2){
        for(int j = 0; i<(boardSize-1); i = i + 2){
            if(board[i][j] != 0 && board[i][j] != board[i+1][j] &&
            board[i][j] != board[i][j+1] && board[i+1][j] != 0 &&
            board[i][j+1] != 0){
                isFull = true;
            }else{
                return false; //At least one location is open
            }
        }
    }
    return isFull;
}

void adjust(char userInput) {
    changesMade = false;
    for (int i = 0; i < 4; i++) { //Running for the maximum amount of times necessary to adjust everything
        if (userInput == 's' || userInput == 'd') {
                for (int vert = 3; vert > 0; vert--) {
                    if (userInput == 's') {
                        for (int horiz = 0; horiz < 4; horiz++) {
                            moveTiles(vert, horiz, -1, 0);
                            combineTiles(vert, horiz, -1, 0);
                        }
                    } else {
                        for (int horiz = 3; horiz > 0; horiz--) {
                            moveTiles(vert, horiz, 0, -1);
                            combineTiles(vert, horiz, 0, -1);
                        }
                    }
                }
        } else {
            for (int vert = 0; vert < 3; vert++) {
                if (userInput == 'w') {
                    for (int horiz = 0; horiz < 4; horiz++) {
                        moveTiles(vert, horiz, 1, 0);
                        combineTiles(vert, horiz, 1, 0);
                    }
                } else {
                    for (int horiz = 0; horiz < 3; horiz++) {
                        moveTiles(vert, horiz, 0, 1);
                        combineTiles(vert, horiz, 0, 1);
                    }
                }
            }
        }
    }
}

void printBoard() {
    int n;
    for (n = 0; n < 10; n++)
        printf("\n");

    if(reachedGoal){
        cout<<blue<<("***************************************")<<reset<<endl;
        cout<<blue<<("*  Congrats!  You created a 16 tile!  *")<<reset<<endl;
        cout<<blue<<("***************************************")<<reset<<endl;
        reachedGoal = false;
    }

    cout << "\u001b[7m" << ("Score: ") << score;
    if(to_string(score)>=highScore){
        cout << " - High Score!" << endl << reset;
        highScore = to_string(score);
        ofstream file;
        file.open ("scoresheet.txt");
        file << highScore;
        file.close();
    }else{
        cout  << endl << reset;
    }
    cout << setfill(' ') << setw(4) << board[0][0] << setfill(' ') << setw(4) << board[0][1]
         << setfill(' ') << setw(4) << board[0][2] << setfill(' ') << setw(4) << board[0][3] << endl;

    cout << setfill(' ') << setw(4) << board[1][0] << setfill(' ') << setw(4) << board[1][1]
         << setfill(' ') << setw(4) << board[1][2] << setfill(' ') << setw(4) << board[1][3] << endl;

    cout << setfill(' ') << setw(4) << board[2][0] << setfill(' ') << setw(4) << board[2][1]
         << setfill(' ') << setw(4) << board[2][2] << setfill(' ') << setw(4) << board[2][3] << endl;

    cout << setfill(' ') << setw(4) << board[3][0] << setfill(' ') << setw(4) << board[3][1]
         << setfill(' ') << setw(4) << board[3][2] << setfill(' ') << setw(4) << board[3][3] << endl;
}

void tileGen() {
    int pos2x = (rand() % 3 + 0);
    int pos2y = (rand() % 3 + 0);
    while (board[pos2x][pos2y] != 0) {
        pos2x = (rand() % 3 + 0);
        pos2y = (rand() % 3 + 0);
    }
    int newTile = randomNum();
    if (newTile >= 9) {
        board[pos2x][pos2y] = 4;
        cout << ("Adding a tile of ") << 4 << (" at position ") << pos2x << (", ") << pos2y << endl;
    } else {
        board[pos2x][pos2y] = 2;
        cout << ("Adding a tile of ") << 2 << (" at position ") << pos2x << (", ") << pos2y << endl;
    }
}

int main() {
    ifstream scoreSheet ("scoresheet.txt");
    if (scoreSheet.is_open())
    {
        while ( getline(scoreSheet,highScore))
        {
            cout << "High Score: " << highScore << '\n';
        }
        scoreSheet.close();
    }

    srand(time(NULL));

    tileGen();
    tileGen();

    /*board[0][0] = 2;  <- A good test board
    board[0][1] = 2;
    board[0][2] = 2;
    board[1][2] = 2;
    board[2][2] = 2;*/

    /*board[0][0] = 4;  <- Another test board
    board[1][0] = 4;
    board[1][1] = 2;
    board[1][2] = 2;*/

    Boolean playing = true;

    printBoard();
    char userInput;
    while (playing) {

        scanf(" %c", &userInput);
        if (userInput == 'x') {
            return 0;
        } else if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd') {
            adjust(userInput);
            if(changesMade){
                tileGen();
                changesMade = false;
            }
            printBoard();
            if(checkFull()){
                cout << "Game Over" << endl;
            }
        }
    }

    return 0;
}