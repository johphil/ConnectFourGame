#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>

void drawBoard();
           //x-coord    y-coord
void gotoxy(int column, int row);
int chooseColumn(int player);
void startGame();
const static int rounds = 3;

int main()
{
    startGame();
    return 0;
}

void drawBoard()
{
    gotoxy(1,1);
    puts(" 1 2 3 4 5 6 7");
    gotoxy(1,2);
    puts("|_|_|_|_|_|_|_|");
    gotoxy(1,3);
    puts("|_|_|_|_|_|_|_|");
    gotoxy(1,4);
    puts("|_|_|_|_|_|_|_|");
    gotoxy(1,5);
    puts("|_|_|_|_|_|_|_|");
    gotoxy(1,6);
    puts("|_|_|_|_|_|_|_|");
    gotoxy(1,7);
    puts("|_|_|_|_|_|_|_|");
}

void startGame()
{
    while (rounds > 0)
    {
        drawBoard();
        printf("%d",chooseColumn(1));
    }
}

int chooseColumn(int player)
{
    int col = 0;

wrongInput:
    gotoxy(1,10);
    printf("Player %d choose column:       ", player);
    gotoxy(25,10);

    if (scanf("%d", &col) != 1)
        goto wrongInput;
    else
        return col;
}

void gotoxy(int column, int row)
{
    COORD coord;
    coord.X = column;
    coord.Y = row;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!SetConsoleCursorPosition(hConsole, coord))
    {
        printf("Error!");
    }
}
