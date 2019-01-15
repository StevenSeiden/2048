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
    int endPointV = 4;
    if(userInput == 'w'){
        moveHoriz = 0;
        moveVert = 1;
    }else if(userInput == 's'){
        moveHoriz = 0;
        moveVert = -1;
        startPointH = 1;
    }else if(userInput == 'a'){
        moveHoriz = 1;
        moveVert = 0;
        endPointV = 3;
    }else if(userInput == 'd'){
        moveHoriz = -1;
        moveVert = 0;
        startPointV = 1;
    }
    else{
        moveHoriz = 0;
        moveVert = 0;
    } for (int i = 0; i < 4; i++) { //Running for the maximum amount of times necessary to adjust everything
                for(int vert = startPointH; vert < 4; vert++) {
                    for (int horiz = startPointV; horiz < endPointV; horiz++) {
                        if(board[vert][horiz] == 0 && board[vert+moveVert][horiz+moveHoriz] != 0){
                            board[vert][horiz] = board[vert+moveVert][horiz+moveHoriz];
                            board[vert+moveVert][horiz+moveHoriz] = 0;
                            printf("Moving (%d,%d) to (%d,%d).\n",(vert+moveVert),(horiz+moveHoriz),vert,horiz);
                        }

                        if(board[vert][horiz] == board[vert+moveVert][horiz+moveHoriz] && board[vert][horiz]!=0){
                            board[vert][horiz] = (board[vert][horiz]*2);
                            //The vert and horiz values are meant to be swapped here.
                            board[vert+moveVert][horiz+moveHoriz] = 0;
                            printf("Adding (%d,%d) to (%d,%d).\n",(vert+moveVert),(horiz+moveHoriz),vert,horiz);
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

void tileGen(){
    int pos2x = (rand() % 3 + 0);
    int pos2y = (rand() % 3 + 0);
    while(board[pos2x][pos2y] != 0){
        pos2x = (rand() % 3 + 0);
        pos2y = (rand() % 3 + 0);
    }
    int newTile = randomNum();
    if(newTile >= 9){
        board[pos2x][pos2y] = 4;
    }else{
        board[pos2x][pos2y] =  2;
    }
}

int main() {
    srand(time(NULL));

    int array [3][3] = {0};

    tileGen();
    tileGen();

    Boolean playing = true;

    PrintBoard();
    char userInput;
    while (playing) {
        scanf(" %c", &userInput);
        if(userInput=='x') {
            return 0;
        }else if(userInput=='w' || userInput=='a' || userInput=='s' || userInput=='d'){
            adjust(userInput);
        }
        tileGen();
        PrintBoard();
    }

    return 0;
}