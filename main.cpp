#include <stdio.h>
#include <MacTypes.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int board[4][4];

int randomNum(){
    int randomNumber;
    randomNumber = rand() % 10;
    if(randomNumber == 10){
        return randomNum();
    }else{
        return randomNumber;
    }
}

void adjust(char userInput){
    int moveHoriz;
    int moveVert;
    int startPointH = 0; //The point on the board at which points are looked at
    int startPointV = 0;
    if(userInput == 'w'){
        moveHoriz = 1;
        moveVert = 0;
    }else if(userInput == 's'){
        moveHoriz = -1;
        moveVert = 0;
        startPointH = 1;
    }else if(userInput == 'a'){
        moveHoriz = 0;
        moveVert = 1;
    }else if(userInput == 'd'){
        moveHoriz = 0;
        moveVert = -1;
        startPointH = 1;
    }
    else{
        moveHoriz = 0;
        moveVert = 0;
    } for (int i = 0; i < 4; i++) { //Running for the maximum amount of times necessary to adjust everything
                for(int vert = startPointH; vert < 4; vert++) {
                    for (int horiz = startPointV; horiz < 4; horiz++) {
                        if(board[vert][horiz] == 0 && board[vert+moveHoriz][horiz+moveVert] != 0){
                            board[vert][horiz] = board[vert+moveHoriz][horiz+moveVert];
                            board[vert+moveHoriz][horiz+moveVert] = 0;
                            printf("Moving (%d,%d) to (%d,%d).\n",(vert+moveHoriz),(horiz+moveVert),vert,horiz);
                        }

                        if(board[vert][horiz] == board[vert+moveHoriz][horiz+moveVert] && board[vert][horiz]!=0){
                            board[vert][horiz] = (board[vert][horiz]*2);
                            board[vert+moveHoriz][horiz] = 0;
                            printf("Adding (%d,%d) to (%d,%d).\n",(vert+1),(horiz+moveVert),vert,horiz);
                        }
                    }

                }
        }

}

void PrintBoard()
{
    int n;
    for (n = 0; n < 10; n++)
        printf( "\n" );

    printf("%d  %d  %d  %d \n%d  %d  %d  %d \n%d  %d  %d  %d \n%d  %d  %d  %d \n",
           board[0][0],board[0][1],board[0][2],board[0][3],
           board[1][0],board[1][1],board[1][2],board[1][3],
           board[2][0],board[2][1],board[2][2],board[2][3],
           board[3][0],board[3][1],board[3][2],board[3][3]
    );
}

int tileGen(){
    int newTile = randomNum();
    if(newTile >= 7){
        return 4;
    }else{
        return 2;
    }
}

int main() {
    srand(time(NULL));

    int array [3][3] = {0};


    /*board[(rand() % 3 + 0)][(rand() % 3 + 0)] = tileGen();
    int pos2x = (rand() % 3 + 0);
    int pos2y = (rand() % 3 + 0);
    while(board[pos2x][pos2y] != 0){
        pos2x = (rand() % 3 + 0);
        pos2y = (rand() % 3 + 0);
    }

    board[pos2x][pos2y] = tileGen();*/


    board[2][0] = 2;
    board[0][1] = 2;
    board[0][2] = 2;
    board[1][2] = 2;
    board[2][3] = 2;


    Boolean playing = true;

    int userInput;
    while (playing) {
        PrintBoard();
        scanf(" %c", &userInput);
            adjust(userInput);

        PrintBoard();
    }

    return 0;
}