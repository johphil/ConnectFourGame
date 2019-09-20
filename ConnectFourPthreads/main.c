#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BOARD_ROWS 6
#define BOARD_COLS 7

void printBoard(char *board);
void clearScreen();
int takeTurn(char *board, int player, const char*);
int checkWin(char *board);
int checkFour(char *board, int, int, int, int);
void *horizontalCheck(void *board);
void *verticalCheck(void *board);
void *diagonalCheck(void *board);

const char *CHIPS = "XO";

int main(int argc, char *argv[])
{
    char board[BOARD_ROWS * BOARD_COLS]; //board size = 6*7 = 42
    memset(board, ' ', BOARD_ROWS * BOARD_COLS); //fill in board with spaces 42 times

    int turn, done = 0;

    for(turn = 0; turn < BOARD_ROWS * BOARD_COLS && !done; turn++)
    {
        printBoard(board);
        while(!takeTurn(board, turn % 2, CHIPS))
        {
            printBoard(board);
            puts("**Column full!**\n");
        }
        done = checkWin(board);
    }
    printBoard(board);

    if(turn == BOARD_ROWS * BOARD_COLS && !done)
    {
        puts("It's a tie!");
    }
    else
    {
        turn--;
        printf("Player %d (%c) wins!\n", turn % 2 + 1, CHIPS[turn % 2]);
    }

    return 0;

}
void printBoard(char *board)
{
    int col;

    clearScreen();
    puts("\n    ****Connect Four****\n");
    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(col = 0; col < BOARD_COLS; col++)
        {
            printf("| %c ",  board[BOARD_COLS * row + col]);
        }
        puts("|");
        puts("-----------------------------");
    }
    puts("  1   2   3   4   5   6   7\n");
}

int takeTurn(char *board, int player, const char *CHIPS)
{
    int col = 0;
    printf("Player %d (%c):\nEnter column number: ", player + 1, CHIPS[player]);

    while(1)
    {
        if(1 != scanf("%d", &col) || col < 1 || col > 7 )
        {
            while(getchar() != '\n');
            puts("Number out of bounds! Try again.");
            printf("Enter column number: ");
        }
        else
        {
            break;
        }
    }
    col--;

    int NextRow, CurrentRow;

    for (int row = 0; row < BOARD_ROWS; row++)
    {
        NextRow = BOARD_COLS * (row+1) + col;
        CurrentRow = BOARD_COLS * row + col;

        if (board[NextRow] == ' ')
        {
            board[CurrentRow] = CHIPS[player];
            printBoard(board);
            board[CurrentRow] = ' ';

            if (NextRow >= 35)
            {
                Sleep(100);
                board[NextRow] = CHIPS[player];
                return 1;
            }
        }
        else if (board[NextRow] != ' ')
        {
                board[CurrentRow] = CHIPS[player];
                return 1;
        }

        Sleep(100);
    }

    return 0;
}
int checkWin(char *board)
{
    pthread_t tid1, tid2, tid3;
    void *iret1, *iret2, *iret3 = (int)0;

    pthread_create(&tid1,NULL,horizontalCheck, (void*)board);
    pthread_create(&tid2,NULL,verticalCheck, (void*)board);
    pthread_create(&tid3,NULL,diagonalCheck, (void*)board);

    pthread_join(tid1,&iret1);
    pthread_join(tid2,&iret2);
    pthread_join(tid3,&iret3);

    return ((int*)iret1 || (int*)iret2 || (int*)iret3);
}
int checkFour(char *board, int a, int b, int c, int d)
{
    return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' ');

}
void *horizontalCheck(void *board)
{
    int col, idx;
    const int WIDTH = 1;

    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(col = 0; col < BOARD_COLS - 3; col++)
        {
            idx = BOARD_COLS * row + col;
            if(checkFour((char*)board, idx, idx + WIDTH, idx + WIDTH * 2, idx + WIDTH * 3))
            {
                return (void *)1;
            }
        }
    }
    return (void *)0;
}
void *verticalCheck(void *board)
{
    int col, idx;
    const int HEIGHT = 7;

    for(int row = 0; row < BOARD_ROWS - 3; row++)
    {
        for(col = 0; col < BOARD_COLS; col++)
        {
            idx = BOARD_COLS * row + col;
            if(checkFour((char*)board, idx, idx + HEIGHT, idx + HEIGHT * 2, idx + HEIGHT * 3))
            {
                return (void *)1;
            }
        }
    }
    return (void *)0;

}
void *diagonalCheck(void *board)
{
    int col, idx, count = 0;
    const int DIAG_RGT = 6, DIAG_LFT = 8;

    for(int row = 0; row < BOARD_ROWS - 3; row++)
    {
        for(col = 0; col < BOARD_COLS; col++)
        {
            idx = BOARD_COLS * row + col;
            if((count <= 3 && checkFour((char*)board, idx, idx + DIAG_LFT, idx + DIAG_LFT * 2, idx + DIAG_LFT * 3)) || (count >= 3 && checkFour((char*)board, idx, idx + DIAG_RGT, idx + DIAG_RGT * 2, idx + DIAG_RGT * 3)))
            {
                return (void *)1;
            }
            count++;
        }
        count = 0;
    }
    return (void *)0;

}
void clearScreen()
{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif // WIN32
}
