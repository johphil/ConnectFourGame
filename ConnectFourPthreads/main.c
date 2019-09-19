#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void drawBoard();
           //x-coord    y-coord
void gotoxy(int column, int row);

int main()
{
    drawBoard();
    gotoxy(1,1);
    printf("x");
    gotoxy(1,3);
    printf("o");
    return 0;
}

void drawBoard()
{
    puts(" 1 2 3 4 5 6 7");
    puts("|_|_|_|_|_|_|_|");
    puts("|_|_|_|_|_|_|_|");
    puts("|_|_|_|_|_|_|_|");
    puts("|_|_|_|_|_|_|_|");
    puts("|_|_|_|_|_|_|_|");
    puts("|_|_|_|_|_|_|_|");
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
