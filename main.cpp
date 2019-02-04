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
std::string flashBlue = "\u001b[34;5;1m";
std::string red = "\u001b[31;1m";
std::string blue = "\u001b[34;1m";
std::string green = "\u001b[32;1m";
std::string yellow = "\u001b[33;1m";

int boardSize = 4;
int board[9][9];
int score = 0;
int highScore;
bool reachedGoal;
bool changesMade;
bool playing;
int tilePlacedX;
int tilePlacedY;
bool coloring = true;
bool logging = true;

void clearSpace(int lines);
void tileGen();
int randomNum();
int help();
int settings();

void newGame();
int game();
void adjust(char userInput);
void moveTiles(int vert, int horiz, int moveVert, int moveHoriz);
void combineTiles(int vert, int horiz, int moveVert, int moveHoriz);
Boolean checkFull();
int gameOver();
void printBoard();
string coloredNum(int value);

int main() {
    clearSpace(20);
    srand(time(NULL));
    std::fstream scoresheet("scoresheet.txt", std::ios_base::in);
    scoresheet >> highScore;
    scoresheet.close();

    clearSpace(10);

    char userInput;
    while (true) {

        cout << red << " .d8888b.   " << green << ".d8888b.      " << yellow << "d8888   " << blue << ".d8888b.  \n"
             << red << "d88P  Y88b " << green << "d88P  Y88b    " << yellow << "d8P888  " << blue << "d88P  Y88b \n"
             << red << "       888 " << green << "888    888   " << yellow << "d8P 888  " << blue << "Y88b. d88P \n"
             << red << "     .d88P " << green << "888    888  " << yellow << "d8P  888   " << blue << "\"Y88888\"  \n"
             << red << " .od888P\"  " << green << "888    888 " << yellow << "d88   888  " << blue << ".d8P\"\"Y8b. \n"
             << red << "d88P\"      " << green << "888    888 " << yellow << "8888888888 " << blue << "888    888 \n"
             << red << "888\"       " << green << "Y88b  d88P       " << yellow << "888  " << blue << "Y88b  d88P \n"
             << red << "888888888   " << green << "\"Y8888P\"        " << yellow << "888   " << blue << "\"Y8888P\" \n"
             << reset << endl;

        cout << "Welcome to 2048!" << endl;

        cout << " \n\n\u001b[7mN" << reset << "ew game" << endl;
        if(playing){
            cout << "\u001b[7mC" << reset <<"ontinue game" << endl;
        }
        cout << "\nView " << "\u001b[7mh" << reset << "elp" << endl;
        cout << "E" << "\u001b[7mx" << reset << "it game" << endl;
        cout <<  "\u001b[7mS" << reset << "ettings" << endl;

        cout << "\n\n" << "\u001b[7m Highscore: " << highScore <<
             "    Create by Steven Seiden   © Steven Seiden 2019" << reset << endl;


        scanf(" %c", &userInput);
        if (userInput == 'n') {
            newGame();
            game();
        } else if (userInput == 'c') {
            game();
        } else if (userInput == 'h') {
            help();
        } else if (userInput == 'x') {
            return 0;
        } else if (userInput == 's'){
            settings();
        }
    }
}

void clearSpace(int lines) {
    int n;
    for (n = 0; n < lines; n++)
        printf("\n");
}

void tileGen() {
    int pos2x = (rand() % 10) % boardSize;
    int pos2y = (rand() % 10) % boardSize;
    while (board[pos2x][pos2y] != 0) {
        pos2x = (rand() % 10) % boardSize;
        pos2y = (rand() % 10) % boardSize;
    }
    int newTile = randomNum();
    if (newTile >= 9) {
        board[pos2x][pos2y] = 4;
        if(logging) {
            cout << ("Adding a tile of ") << 4 << (" at position ") << pos2x << (", ") << pos2y << endl;
        }

    } else {
        board[pos2x][pos2y] = 2;
        if(logging){
            cout << ("Adding a tile of ") << 2 << (" at position ") << pos2x << (", ") << pos2y << endl;
        }
    }
    tilePlacedX = pos2x;
    tilePlacedY = pos2y;
}

int help() {
    clearSpace(10);
    cout << "\u001b[7m" << "Help" << reset << endl;
    cout << "\u001b[1mWelcome to 2048!\n" << reset <<
         "\n"
         "2048 is a simple game in which\n"
         "the goal is to combine like\n"
         "tiles to reach the 2048 tile.\n"
         "\n"
         "\u001b[1mKeys:\n" << reset <<
         "w = Move tiles up\n"
         "s = Move tiles down\n"
         "a = Move tiles left\n"
         "d = Move tiles right\n"
         "x = Main menu" << endl;

    cout << "\nPress \u001b[7mc" << reset << " to \u001b[7mc" << reset << "ontinue." << endl;
    char userInput;
    scanf(" %c", &userInput);
    if (userInput == 'c') {
        return 0;
    }
}

int settings(){
    char userInput;
    while (true) {
        clearSpace(20);
        cout << "\u001b[7m" << "Settings" << reset << "\n\n" << endl;
        if(coloring){
            cout <<  "C\u001b[7mo" << reset << "loring is enabled (good for 256 colored terminals)" << endl;
        }else{
            cout << "C\u001b[7mo" << reset << "loring is disabled (good for terminals lacking 256 colors)" << endl;
        }
        cout << "\u001b[38;5;34mIf this doesn't appear in color than you should disable coloring." << reset << endl;

        if(logging){
            cout <<  "\u001b[7mL" << reset << "ogging is enabled" << endl;
        }else{
            cout << "\u001b[7mL" << reset << "ogging is disabled" << endl;
        }

        cout <<  "\u001b[7mB" << reset << "oard size: " << boardSize << endl;

        cout << "\nPress \u001b[7mc" << reset << " to \u001b[7mc" << reset << "ontinue." << endl;

        scanf(" %c", &userInput);
        if (userInput == 'o') {
            coloring = !coloring;
        } else if (userInput == 'c'){
            return 0;
        } else if (userInput == 'l'){
            logging = !logging;
        }else if (userInput == 'b'){
            bool userInputting = true;
            int userNum;
            while (userInputting) {
                cout << "Note that setting a custom board size will disable \n"
                        "saving your high score until set back to 4.\n"
                        "This will also end your current game.\n" <<
                     "Please enter a new board size (2-9): ";
                std::cin >> userNum;
                if(!cin.fail()){
                    boardSize = userNum;
                    userInputting = false;
                    playing = false;
                }
            }
        }
    }
}

int randomNum() {
    int randomNumber;
    randomNumber = rand() % 10;
    if (randomNumber == 10) {
        return randomNum();
    } else {
        return randomNumber;
    }
}

void newGame(){
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            board[i][j] = {0};
        }
    }
    score = 0;
}

int game() {
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

    playing = true;

    clearSpace(20);
    printBoard();
    char userInput;
    while (playing) {

        scanf(" %c", &userInput);
        if (userInput == 'x') {
            return 0;
        } else if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd') {
            adjust(userInput);
            if (changesMade) {
                tileGen();
                changesMade = false;
            }
            clearSpace(20);
            printBoard();
            if (checkFull()) {
                gameOver();
            }
        } else if(userInput == 'k'){
            coloring = false;
        }
    }
    return 0;
}

void adjust(char userInput) {
    changesMade = false;
    for (int i = 0; i < boardSize; i++) { //Running for the maximum amount of times necessary to adjust everything
        if (userInput == 's' || userInput == 'w') {
            for (int horiz = 0; horiz < boardSize; horiz++) {
                if (userInput == 's') {
                    for (int vert = (boardSize-1); vert > 0; vert--) {
                        moveTiles(vert, horiz, -1, 0);
                        combineTiles(vert, horiz, -1, 0);
                    }
                } else {
                    for (int vert = 0; vert < (boardSize-1); vert++) {
                        moveTiles(vert, horiz, 1, 0);
                        combineTiles(vert, horiz, 1, 0);
                    }
                }
            }
        } else if (userInput == 'd') {
            for (int horiz = (boardSize-1); horiz > 0; horiz--) {
                for (int vert = (boardSize-1); vert >= 0; vert--) {
                    moveTiles(vert, horiz, 0, -1);
                    combineTiles(vert, horiz, 0, -1);
                }
            }
        } else {
            for (int horiz = 0; horiz < (boardSize-1); horiz++) {
                for (int vert = 0; vert < boardSize; vert++) {
                    moveTiles(vert, horiz, 0, 1);
                    combineTiles(vert, horiz, 0, 1);
                }
            }
        }
    }
}

void moveTiles(int vert, int horiz, int moveVert, int moveHoriz) {
    if (board[vert][horiz] == 0 && board[vert + moveVert][horiz + moveHoriz] != 0) {
        board[vert][horiz] = board[vert + moveVert][horiz + moveHoriz];
        board[vert + moveVert][horiz + moveHoriz] = 0;
        if(logging){
            printf("Moving (%d,%d) to (%d,%d).\n", (vert + moveVert), (horiz + moveHoriz), vert, horiz);
        }
        changesMade = true;
    }
}

void combineTiles(int vert, int horiz, int moveVert, int moveHoriz) {
    if (board[vert][horiz] == board[vert + moveVert][horiz + moveHoriz] && board[vert][horiz] != 0) {
        board[vert][horiz] = (board[vert][horiz] * 2);
        //The vert and horiz values are meant to be swapped here.
        board[vert + moveVert][horiz + moveHoriz] = 0;
        if(logging){
            printf("Adding (%d,%d) to (%d,%d).\n", (vert + moveVert), (horiz + moveHoriz), vert, horiz);
        }
        score = score + board[vert][horiz];
        if (board[vert][horiz] == 16) {
            reachedGoal = true;
        }
        changesMade = true;
    }
}

//This checks to see if the board is full, and returns true if full
Boolean checkFull() {
    for (int i = 0; i <= (boardSize - 1); i++) {
        for (int j = 0; j <= (boardSize - 1); j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    for (int i = 0; i <= (boardSize - 1); i++) {
        for (int j = 0; j <= (boardSize - 1); j++) {
            if (i >= (boardSize - 2) || j >= (boardSize - 2)) {
                if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1]) {
                    return false;
                }
            } else if (i >= (boardSize - 2)) {
                if (board[i][j] == board[i][j + 1]) {
                    return false;
                }
            } else {
                if (board[i][j] == board[i + 1][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int gameOver() {
    clearSpace(10);
    cout << red << " _____                        _____                \n"
                   "|  __ \\                      |  _  |               \n"
                   "| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __ \n"
                   "| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|\n"
                   "| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |   \n"
                   " \\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   \n" << reset << endl;
    printBoard();

    cout << "\nPress " << "\u001b[7mc" << reset << " to " << "\u001b[7mc" << reset << "ontinue." << endl;
    char userInput;
    scanf(" %c", &userInput);
    if (userInput == 'c') {
        playing = false;
        return 0;
    }
}

void printBoard() {
    if (reachedGoal) {
        cout << flashBlue << ("***************************************") << reset << endl;
        cout << flashBlue << ("*  Congrats!  You created a 16 tile!  *") << reset << endl;
        cout << flashBlue << ("***************************************") << reset << endl;
        reachedGoal = false;
    }

    cout << "\u001b[7m" << ("Score: ") << score;
    if (score >= highScore) {
        cout << " - High Score!" << endl << reset;
        highScore = score;
        if(boardSize == 4){
            ofstream scoresheet("scoresheet.txt");
            scoresheet << highScore << endl;
            scoresheet.close();
        }
    } else {
        cout << endl << reset;
    }
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (tilePlacedX == i && tilePlacedY == j) {
                cout << coloredNum(board[i][j]) << "\033[5m" << setfill(' ') << setw(8) << board[i][j] << reset;
            } else {
                cout << coloredNum(board[i][j]) << setfill(' ') << setw(8) << board[i][j];
            }
        }
        cout << endl;
    }
}

string coloredNum(int value) {
    if(coloring){
        switch (value) {
            case 0 :
                return "\033[0m";
            case 2 :
                return "\u001b[38;5;141m";
            case 4 :
                return "\u001b[38;5;212m";
            case 8 :
                return "\u001b[38;5;208m";
            case 16 :
                return "\u001b[38;5;196m";
            case 32 :
                return "\u001b[38;5;93m";
            case 64 :
                return "\u001b[38;5;27m";
            case 128 :
                return "\u001b[38;5;31m";
            case 256 :
                return "\u001b[38;8;36m";
            case 512 :
                return "\u001b[38;5;34m";
            case 1024 :
                return "\u001b[38;5;214m";
            case 2048 :
                return "\u001b[38;5;222m";
            case 4096 :
                return "\u001b[38;5;189m";
            case 8192 :
                return "\u001b[38;5;117m";
            default:
                return "\u001b[31;1m";
        }
    } else {
        return reset;
    }
}