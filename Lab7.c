#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

bool positionInBounds(int n, char row, char col);
bool checkLegalInDirection(char board[][26], int n, char row, char col,char colour, int deltaRow, int deltaCol);
void printBoard(char board[][26], int n);
void changeBoard(char board[26][26] , char input[3]);
bool checkMove(char board[26][26] , int n , char row , char col , char colour);
void printMoves(char board[26][26] , int n , char colour);

int main()
{
    // Main Variable Declarations
    char board[26][26];
    int n;
    // Starting Input
    printf("Enter the board dimension: ");
    scanf("%d" , &n);
    // Fill starting Pos
    for(int i = 0 ; i < n; i++)
    {
        for(int j = 0 ; j < n; j++)
        {
            board[i][j] = 'U';
            if(i == n/2 - 1)
            {
                if(j == n/2 - 1)
                    board[i][j] = 'W';
                if(j == n/2)
                    board[i][j] = 'B';
            }
            else if(i == n/2)
            {
                if(j == n/2 - 1)
                    board[i][j] = 'B';
                if(j == n/2)
                    board[i][j] = 'W';
            }
        }
    }
    // Beginning of Game loop
    printBoard(board , n);
    printf("Enter board configuration:\n");
    
    char input[3] = "";
    do
    {
        scanf("%s" , input);
        if(!strcmp(input , "!!!"))
            break;
        changeBoard(board , input);
    }
    while(true);
    printBoard(board , n);
    bool result = false;
    printMoves(board , n , 'W');
    printMoves(board , n , 'B');
    printf("Enter a move:\n");
    scanf("%s" , input);
    char colour = input[0];
    char row = input[1];
    char col = input[2];
    if(checkMove(board , n , row ,col ,colour))
    {
        printf("Valid move.\n");
        changeBoard(board , input);
    }
    else
    {
        printf("Invalid move.\n");
    }
    printBoard(board , n);
    return 0;
}

bool positionInBounds(int n, char row, char col)
{
    int rowNum = row - 'a' + 1;
    int colNum = col - 'a' + 1;
    if(rowNum <= n && colNum <= n)
        return true;
    return false;
}
bool checkLegalInDirection(char board[26][26], int n, char row, char col,char colour, int deltaRow, int deltaCol)
{
    int rowNum = row - 'a';
    int colNum = col - 'a';
    char oppColour = 'W';
    bool okay = false;
    if(colour == 'W')
        oppColour = 'B';
    if(board[rowNum][colNum] != 'U')
        return false;
    
    for(int i = rowNum + deltaRow , j = colNum + deltaCol ; i < n && j < n && i >= 0 && j >= 0; i+= deltaRow)
    {
        if(board[i][j] == colour && !okay)
        {
            return false;
        }
        if(board[i][j] == oppColour)
            okay = true;
        else if(board[i][j] == colour && okay)
        {
            return true;
        }
        else if(board[i][j] == 'U')
            return false;
        // Equivalent to two update statements
        j+= deltaCol;
    }
    return false;
}
void printBoard(char board[][26], int n)
{
    printf("  ");
    for(int i = 0 ; i < n; i++)
        printf("%c" , 'a' + i);
    printf("\n");
    for(int i = 0 ; i < n; i++)
    {
        printf("%c " , 'a' + i);
        for(int j = 0 ; j < n; j++)
        {
            printf("%c" , board[i][j]);
        }
        printf("\n");
    }
}
void changeBoard(char board[26][26] , char input[3])
{
    int rowI , colI;
    rowI = (char)input[1] - 'a';
    colI = (char)input[2] - 'a';
    board[rowI][colI] = (char)input[0];
}
bool checkMove(char board[26][26] , int n , char row , char col , char colour)
{
    bool result = false;
    bool temp;
    for(int i=-1;i < 2;i++)
        for(int j=-1;j < 2;j++)
            if(i != 0 || j != 0)
                {
                    temp = checkLegalInDirection(board , n , row , col , colour , i , j);
                    result += temp;
                    //if(temp)
                    //    printf("%c%c Result: %d Direction = (%d , %d) \n"  , row , col , temp , i , j);
                }
    return result;
}
void printMoves(char board[26][26] , int n , char colour)
{
    printf("Available moves for %c:\n" , colour);
    char row , col;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n; j++)
        {
            row = 'a' + i;
            col = 'a' + j;
            if(checkMove(board , n , row , col , colour))
            {
                printf("%c%c\n" , row , col);
            }
        }
}