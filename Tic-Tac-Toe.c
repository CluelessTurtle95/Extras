#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

#define GameSize 3
#define A GameSize*GameSize + 1
#define B GameSize*GameSize + 2

int singlePlayer();
int twoPlayer(); 

void printBoard(int board[]);
void requestValidInput(int board[], int player);
int checkForWinner(int board[]);
int autoInput(int board[] , int player);
double winProbability(int board[GameSize*GameSize] , int player  , bool turn);

int main()
{
    int numPlayers = 2;
    bool flag = false;
    
    do
    {
        //printf("Enter Player Mode (1 or 2): ");
        //scanf("%d" , &numPlayers);
        if(numPlayers == 1)
        {
            singlePlayer();
        }
        else if(numPlayers == 2)
        {
            twoPlayer();
        }
        else 
        {
            flag = true;
            printf("Invalid Input! Try Again!\n");
        }
    }while(flag);
}

int singlePlayer()
{
    if(GameSize > 3)
    {
        printf("sorry AUTO-INPUT not available for GameSize %d"  , GameSize);
        return -1;
    }
    int board[GameSize*GameSize];
    for(int i=0 ;i < GameSize*GameSize; i++)
        board[i] = i+1;
    int winner = 0;
    printf("You Are Player A!\n");
    int i = 0;
    while(i < GameSize*GameSize)
    {
	    printf("The current state of the Tic-tac-toe Board:\n");
        printBoard(board);
        if(GameSize < 4)
        {
            printf("Win Probability of A : %lf\n" , winProbability(board , A , true));
            printf("Win Probability of B : %lf\n" , winProbability(board , B , false));
        }
        requestValidInput(board , A);
        if(checkForWinner(board) == A)
        {
            winner = A;
            break;
        }
        i++;
	    if(i >= GameSize*GameSize)
		    break;
        if(GameSize < 4)
        {
            printf("Win Probability of A : %lf\n" , winProbability(board , A , false));
            printf("Win Probability of B : %lf\n" , winProbability(board , B , true));
        }
	    printf("The current state of the Tic-tac-toe Board(After Computer turn)\n");
        board[autoInput(board , B)] = B;
        printBoard(board);
        if(checkForWinner(board) == B)
        {
            winner = B;
            break;
        }
	    i++;
    }
    if(winner == A)
        printf("You win!\n");
    else if(winner == B)
        printf("Computer Wins !\n");
    else
    {
        printf("It's a draw!\n");
    }
    printBoard(board);
    printf("\n");
    return 0;
    
}
int twoPlayer()
{
    int board[GameSize*GameSize];
    for(int i=0 ;i < GameSize*GameSize; i++)
        board[i] = i+1;
    int winner = 0;
    int i = 0;
    while(i < GameSize*GameSize)
    {
	    printf("The current state of the Tic-tac-toe Board:\n");
        printBoard(board);
        //if(GameSize < 4)
        //{
        //printf("Win Probability of A : %lf\n" , winProbability(board , A , true));
        //printf("Win Probability of B : %lf\n" , winProbability(board , B , false));
        //}
        requestValidInput(board , A);
        if(checkForWinner(board) == A)
        {
            winner = A;
            break;
        }
        i++;
	    if(i >= GameSize*GameSize)
		    break;
	    printf("The current state of the Tic-tac-toe Board:\n");
        printBoard(board);
        //if(GameSize < 4)
        //{
        //    printf("Win Probability of A : %lf\n" , winProbability(board , A , false));
        //    printf("Win Probability of B : %lf\n" , winProbability(board , B , true));
        //}
        requestValidInput(board , B);
        if(checkForWinner(board) == B)
        {
            winner = B;
            break;
        }
	i++;
    }
    if(winner == A)
        printf("Player A wins!\n");
    else if(winner == B)
        printf("Player B wins!\n");
    else
    {
        printf("It's a draw!\n");
    }
    printBoard(board);
    printf("\n");
    return 0;
}
void requestValidInput(int board[GameSize*GameSize] , int player)
{
    char turn[10];
    int input;
    bool flag = false;

    if(player == A)
        strcpy(turn , "A");
    if(player == B)
        strcpy(turn , "B");
    
    printf("It is Player %s's turn.\n" , turn);
    printf("Please enter a valid position to play.\n");
    
    do
    {
        flag = false;
        char temp[10] = "";
        // size_t bufSize = 30;
        // getline(&temp , &bufSize, stdin);
        // input = strtol(temp , NULL  , 0);
        // if(input == 0)
        // {
        //    input = autoInput(board);
        // }

        //scanf("%d" , &input);
        scanf("%s" , temp);
        input = strtol(temp , NULL  , 0);
        if(input == 0)
        {
            printf("Invalid Input Entered , AutoInput Initiated!\n");
            input = autoInput(board , player)+1;
        }

        if(input < A && input > 0)
        {
            if(board[input-1] != A && board[input-1] != B)
            {
	      board[input-1] = player;
            }
            else
            {
                flag = true;    
                printf("That position has already been played, please try again.\n");
            }
        }
        else
        {
            flag = true;    
            printf("Invalid input, please try again.\n");
        }
    
    }while(flag);
    
}
void printBoard(int board[])
{
    int digitNum;
    int maxNumSize;
    for(maxNumSize = 0 ; (GameSize*GameSize) % (int)pow(10 , maxNumSize) < (GameSize*GameSize) ; maxNumSize++);
    printf("\n");
    int item;
    for(int i=0 ;i < GameSize; i++)
    {
        for(int j=0; j < GameSize;j++)
        {
            item = board[j + GameSize*i];
            //printf(" ");
            if(item == A)
            {
                for(int k = 0 ;k < maxNumSize ; k++)
                    printf(" ");
                printf("A");
            }
            else if(item == B)
            {
                for(int k = 0 ;k < maxNumSize ; k++)
                    printf(" ");
                printf("B");
            }
            else
    	    {
                for(digitNum = 0 ; item % (int)pow(10 , digitNum) < item; digitNum++);
                for(int k=0 ;k < maxNumSize - digitNum+1; k++)
                    printf(" ");
                printf("%d" ,  item);
            }
	}
        printf("\n");
    }
    printf("\n");
}
int checkForWinner(int board[])
{
    int temp;
    bool flag;
    int winner = -1;
    // Horizontal
    for(int  i = 0; i < GameSize; i++)
    {
        flag = true;
        temp = board[GameSize*i];
        for(int j = 0; j < GameSize; j++)
        {
            if(board[GameSize*i + j] != temp)
            {
                flag = false;
                winner = -1;
                break;
            }
            winner = temp;
        }
        if(flag)
            return winner;
    }

    // Vertical
    winner = -1;
    for(int  i = 0; i < GameSize; i++)
    {
        flag = true;
        temp = board[i];
        for(int j = 0; j < GameSize; j++)
        {
            if(board[GameSize*j + i] != temp)
            {
                flag = false;
                winner = -1;
                break;
            }
            winner = temp;
        }
        if(flag)
            return winner;    
    }
    
    // Diag 1
    temp = board[0];
    flag = true;
    for(int i = 0 ; i < GameSize*GameSize; i += GameSize +1 )
    {
        if(board[i] != temp)
        {
            flag = false;
            winner = -1;
            break;
        }
        winner = temp;
    }
    if(flag)
        return winner;

    // Diag 2
    temp = board[GameSize -1];
    flag = true;
    for(int i = GameSize - 1 ; i < GameSize*GameSize -1; i += GameSize -1)
    {
        if(board[i] != temp)
        {
            flag = false;
            winner = -1;
            break;
        }
        winner = temp;
    }
    if(flag)
        return winner;

    return winner;
}
int autoInput(int board[] , int player)
{
    int state[GameSize*GameSize];  
    for(int i = 0 ; i < GameSize*GameSize; i++)
        state[i] = board[i];
    
    if(player != A && player != B)
    {
        return -1;
    }
    int resultPos = -1;
    double prob = -100 , temp;
    int oppPlayer = (player == B) ? A:B;
    for(int i = 0 ; i < GameSize*GameSize ; i++)
    {
        if(state[i] != A && state[i] != B)
        {
            state[i] = player;
            temp = 1 - winProbability(state , oppPlayer , true) + winProbability(state , player , false);
            state[i] = board[i];
            //printf("Position %d , Maximizer : %lf\n" , i+1 , temp);
            if(prob  < temp)
            {
                prob = temp;
                resultPos = i;
            }
        }
    }
    return resultPos;
}
double winProbability(int board[GameSize*GameSize] , int player  , bool turn)
{
    double prob = 0 , temp;
    int counter  = 0; 
    bool isfull = true;
    int originalPlayer = player;
    int state[GameSize*GameSize];
    double chooser[GameSize*GameSize];
    int oppPlayer = (originalPlayer==A) ? B:A;
    // Copy array into state
    for(int i = 0 ; i < GameSize*GameSize; i++)
    {
        state[i] = board[i];
        if(board[i] == i + 1)
            isfull = false;
    }
    if(checkForWinner(board) == originalPlayer)
    {
        prob = 1;
        return prob;
    }
    if(checkForWinner(board) == oppPlayer)
    {
        prob = -1;
        return prob;
    }
    if(isfull)
    {
        //printBoard(state);
        if(checkForWinner(board) == -1)
            prob = 0;
        return prob;
    }
    if(!turn)
    {
        if(player == A)
            player = B;
        else if(player == B)
            player = A;
    }
    // Check all posibilities
    for(int i = 0 ; i < GameSize*GameSize ; i++)
    {
        if(board[i] != A && board[i] != B)
        {
            state[i] = player;
            prob = winProbability(state , originalPlayer , !turn);
            chooser[counter] = prob;
            counter++;
            state[i] = board[i];
            if(prob == 1 && player == originalPlayer)
                break;
        }
    }
    prob = 0;
    for(int i = 0 ; i < counter; i++)
    {
        if(player == originalPlayer)
        {
            if(prob < chooser[i])
                prob = chooser[i];
        }
        else if(player == oppPlayer)
        {
            prob += chooser[i]/counter;
        }
    }
    //printf(" %lf " , prob);
    return prob;
}
