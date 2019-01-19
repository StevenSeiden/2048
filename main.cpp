#include <stdio.h>
#include <MacTypes.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

std::string reset = "\033[0m";
std::string blue = "\u001b[44;5;1m";

int board[4][4];
int score = 1;
bool reachedGoal;

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
    }
}

void combineTiles(int vert, int horiz, int moveVert, int moveHoriz) {
    if (board[vert][horiz] == board[vert + moveVert][horiz + moveHoriz] && board[vert][horiz] != 0) {
        board[vert][horiz] = (board[vert][horiz] * 2);
        //The vert and horiz values are meant to be swapped here.
        board[vert + moveVert][horiz + moveHoriz] = 0;
        printf("Adding (%d,%d) to (%d,%d).\n", (vert + moveVert), (horiz + moveHoriz), vert, horiz);
        score = score + board[vert][horiz];
        if(board[vert][horiz] == 8){
            reachedGoal = true;
        }
    }
}

void adjust(char userInput) {
    for (int i = 0; i < 4; i++) { //Running for the maximum amount of times necessary to adjust everything
        if (userInput == 's') {
            for (int vert = 3; vert > 0; vert--) {
                for (int horiz = 0; horiz < 3; horiz++) {
                    moveTiles(vert, horiz, -1, 0);
                    combineTiles(vert, horiz, -1, 0);
                }
            }
        } else {
            for (int vert = 0; vert < 3; vert++) {
                if (userInput == 'w') {
                    for (int horiz = 0; horiz < 4; horiz++) {
                        moveTiles(vert, horiz, 1, 0);
                        combineTiles(vert, horiz, 1, 0);
                    }
                }else if (userInput == 'd') {
                    for (int horiz = 3; horiz > 0; horiz--) {
                        moveTiles(vert, horiz, 0, -1);
                        combineTiles(vert, horiz, 0, -1);
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

void PrintBoard() {
    int n;
    for (n = 0; n < 10; n++)
        printf("\n");

    if(reachedGoal){
        cout<<blue<<("_______________________________________")<<reset<<endl;
        cout<<blue<<("|  Congrats!  You created a 16 tile!  |")<<reset<<endl;
        cout<<blue<<("---------------------------------------")<<reset<<endl;
        reachedGoal = false;
    }

    cout << ("Score: ") << score - 1 << endl;
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
    srand(time(NULL));

    int array[3][3] = {0};

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

    PrintBoard();
    char userInput;
    while (playing) {

        scanf(" %c", &userInput);
        if (userInput == 'x') {
            return 0;
        } else if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd') {
            adjust(userInput);
            tileGen();
            PrintBoard();
        }
    }

    return 0;
}