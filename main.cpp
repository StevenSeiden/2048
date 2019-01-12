#include <stdio.h>
#include <MacTypes.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int randomNum(){
    int randomNumber;
    randomNumber = rand() % 10;
    if(randomNumber == 10){
        return randomNum();
    }else{
        return randomNumber;
    }
}

void ClearScreen()
{
    int n;
    for (n = 0; n < 10; n++)
        printf( "\n\n\n\n\n\n\n\n\n\n" );
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
    int board[4][4];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            board[i][j] = 0;
        }
    }


    board[(rand() % 3 + 0)][(rand() % 3 + 0)] = tileGen();
    board[(rand() % 3 + 0)][(rand() % 3 + 0)] = tileGen();

    //(rand() % 4 + 1)

    Boolean playing = true;

    while (playing) {
        ClearScreen();
        printf("%d  %d  %d  %d \n%d  %d  %d  %d \n%d  %d  %d  %d \n%d  %d  %d  %d \n",
               board[0][0],board[0][1],board[0][2],board[0][3],
               board[1][0],board[1][1],board[1][2],board[1][3],
               board[2][0],board[2][1],board[2][2],board[2][3],
               board[3][0],board[3][1],board[3][2],board[3][3]
        );
        playing = false;
    }

    return 0;
}