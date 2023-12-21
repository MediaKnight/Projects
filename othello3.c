// preprocessors
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//prototype
void welcomeScreen();

void displayExplicitBoard();

void clearScreen();

void playGame();

void initializeBoard();

void displayBoard();

void makeMove();



// main function
int main()
{
    welcomeScreen();

    clearScreen();

   // displayExplicitBoard();
    playGame();

    return 0;

}
// welcomeScreen function
void welcomeScreen()

{
    printf("\t\t OOOO  TTTTTT HH  HH EEEEEE LL     LL      OOOO\n");
    printf("\t\tOO  OO   TT   HH  HH EE     LL     LL     OO  OO\n");
    printf("\t\tOO  OO   TT   HHHHHH EEEEEE LL     LL     OO  OO\n");
    printf("\t\tOO  OO   TT   HH  HH EE     LL     LL     OO  OO\n");
    printf("\t\t OOOO    TT   HH  HH EEEEEE LLLLLL LLLLLL  OOOO\n\n\n");


    printf("OTHELLO GAME RULES\n");
    printf("1. A square 8 x 8 board\n");
    printf("2. 64 discs colored black (X) on one side and white (O) on the opposite side.\n");
    printf("3. The board will start with 2 black discs (X) and 2 white discs (O) at the center of the board.\n");
    printf("4. They are arranged with black (X) forming a North-East to South-West direction. White (O) is forming a North-West to South-East direction.\n");
    printf("5. The goal is to get most color discs on the board at the end of the game.\n");
    printf("6. Each player gets 32 discs and black (X) always starts the game.\n");
    printf("7. The game alternates between white (O) and black (X) until one player cannot make a valid move to outflank the opponent or both players have no valid moves.\n");
    printf("8. When a player has no valid moves, they pass their turn and the opponent continues.\n");
    printf("9. A player cannot voluntarily forfeit their turn.\n");
    printf("10.When both players cannot make a valid move the game ends.\n");

}
//clearScreen function

void clearScreen()
{


    printf("Hit <ENTER> to continue!");
    char enter;
    scanf("%c", &enter);
    system("cls");
    //system("clear")

}
// displayBoard function
void displayExplicitBoard()
{


    printf("|------------------------------------------------------\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");
    printf("|------------------------------------------------------\n");
    printf("|  1  |     |     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------------------\n");
    printf("|  2  |     |     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------------------\n");
    printf("|  3  |     |     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------------------\n");
    printf("|  4  |     |     |     |  O  |  X  |     |     |     |\n");
    printf("|------------------------------------------------------\n");
    printf("|  5  |     |     |     |  X  |  O  |     |     |     |\n");
    printf("|------------------------------------------------------\n");
    printf("|  6  |     |     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------------------\n");
    printf("|  7  |     |     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------------------\n");
    printf("|  8  |     |     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------------------\n");

}

//declaring macros
#define THREE 3
#define TRUE 1
#define FALSE 0
#define NAME 20
#define ROW 8
#define COL 8
#define SPACE ' '
#define PLAYER_X 1
#define PLAYER_O 2
#define ZERO 0
#define ONE 1
#define TWO 2
#define FOUR 4
#define INVALID -1
// function playGame
void playGame()
{
    char board[ROW][COL];

    // player names
    char playerX[NAME];

    char playerO[NAME];




    // start with player X
    int currentPlayer = PLAYER_X;

    int loop = ZERO;
    // player name prompts
    printf("Player X enter your name.\n");

    scanf("%s", playerX);

    printf("Player O enter your name.\n");

    scanf("%s", playerO);

    printf("%s and %s Let's play othello!\n", playerX, playerO);

    initializeBoard(board);

    displayBoard(board);


    // while loop within playGame
    while (loop < FOUR){

        //display the board
        //displayExplicitBoard();
        // swap turns between players
        if (currentPlayer == PLAYER_X) {
            //printf("%s" " it is your turn\n", playerX);
            makeMove(playerX, PLAYER_X, board);
            currentPlayer = PLAYER_O;
            }

        else if (currentPlayer == PLAYER_O) {
            makeMove(playerO, PLAYER_O, board);
            //printf("%s" " it is your turn\n", playerO);
            currentPlayer = PLAYER_X;
            }

            //system("pause");
            // add increments
            loop++;}


}


void initializeBoard(char board[ROW][COL]){
    int i;
    int j;
    for(i=0;i<=ROW;++i){
       for(j=0;j<=COL;++j){
       if((i == 3 && j == 3) || ( i == 4 && j == 4)){board[i][j] = 'O';
       }
       else if ((i == 3 && j == 4) || (i==4 && j ==3)) {board[i][j] = 'X';
       }
       else {board[i][j] = SPACE;}

       }
    }
}

void displayBoard(char board[ROW][COL]){
    int i;
    int j;

    printf("|------------------------------------------------------\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |");



     for(i=1;i<=ROW;++i){
        printf("\n|------------------------------------------------------\n");
        printf("|  %d  |", i);


    for(j=1;j<=COL;++j){
        printf("  %c  |", board[i][j]);






     }

     }
}

void makeMove(int playerName[NAME], int playerNum,  char board[ROW][COL]){
    char move[THREE];

    int valid = FALSE;

    while(!valid){
        printf("%s make your move\n", playerName);
        scanf("c%", &move);
        printf("You entered c%", move);

        int length;
        length = strlen( move);

        if (length == TWO){
            valid = TRUE;}


            else{ valid = FALSE;
            printf("Your move was not valid\n");
        }
            }
}



