// ConnectFour.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include"Game.h"
#include"autoPlayer.h"
using namespace std;

int main()
{

	int rows = 8 , cols = 8;
	int input , depth;
	double stupidity;

	cout << "Game Size ? Enter rows and colums";
	cin >> rows >> cols;

	Game newGame(rows, cols);
	//autoPlayer player1(&newGame , 5  , 40.0 , 0 , 0);
	cout << "Game Difficulty? (1-7) (7 slowest) : ";
	cin >> depth;
	cout << "How Dumb are you? (0-1) ";
	cin >> stupidity;
	autoPlayer player2(&newGame, depth, 40.0, stupidity , 0.5);
	// Players have Smartness , PatternRecognition(higher value less recognition)
	// Knowledge of stupidity of other players and finally greed

	for(int k=0;k < rows*cols/2 + 1;k++)
	{
		newGame.print();
		cout << "Player R Position:";
		cin >> input;
		try
		{
			//newGame.play(player1.move(rows*cols + 1));
			newGame.play(input - 1);
		}
		catch (exception e)
		{
			cerr << e.what();
			break;
		}
		newGame.print();
		if (newGame.checkWinner() != -1 || newGame.checkWinner() == -2)
		{
			cout << "Game Over\n ";
			break;
		}
		cout << "Computing Move...\n";
		//player2 = autoPlayer(&newGame);
		try
		{
			newGame.play(player2.move(rows*cols + 2));
		}
		catch(exception e)
		{
			cerr << e.what();
			break;
		}
		//newGame.print();
		if (newGame.checkWinner() != -1)
		{
			cout << "Game Over\n" ;
			break;
		}
	}

	if (newGame.checkWinner() == rows * cols + 1)
	{
		cout << "You Win!\n";
	}
	else
		cout << "Computer Wins!\n";
	newGame.print();
 
}
