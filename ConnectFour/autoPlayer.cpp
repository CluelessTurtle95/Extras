#include "pch.h"
#include "autoPlayer.h"
#include<iostream>

using namespace std;

autoPlayer::autoPlayer(Game* Original, int depth = 5,double evalReduce = 40.0, double stupidity = 0.5,double greed = 0.1) : maxDepth(depth) 
{
	evalChanceReduce = evalReduce;
	autoPlayer::stupidity = stupidity;
	autoPlayer::Original = Original;
	rows = Original->getRows();
	cols = Original->getCols();
	autoPlayer::greed = greed;
}

double autoPlayer::winProbability(int player, bool turn, Game state, int depth, int column)
{

	//state->print();
	//Game& state = board;
	int oppPlayer = rows * cols + ((player == rows * cols + 1) ? 2 : 1);
	if (!turn)
	{
		if (state.checkWinner(column, player))// if (state.checkWinner() == player)
		{
			//cout << "Test";
			return 1;
		}
	}
	else
	{
		if (state.checkWinner(column, oppPlayer)) //if (state.checkWinner() == oppPlayer) //  
		{
			//cout << "Test";
			return -1;
		}
	}
	bool isfull = true;
	for(int i = 0 ; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (state.at(i, j) == 0)
			{
				isfull = false;
			}
			//cout << isfull;
		}
	if (isfull && state.checkWinner() == -1)
	{
		//cout << "Test";
		return 0;
	}
	if (depth > maxDepth)
		return state.evaluateChances(player)/evalChanceReduce;
	int originalPlayer = player;
	int counter = 0;
	double *chooser = new double[cols];
	player = turn ? originalPlayer : oppPlayer;
	for (int i = 0; i < cols; i++)
	{
		if (state.at(0, i) == 0)
		{
			state.play(i , player);
			//state.print();
			chooser[counter] = winProbability(originalPlayer, !turn , state , depth + 1 , i);
			//state = board;
			state.unPlay(i);
			//state.print();
			if (chooser[counter] == 1 && turn)
			{
				return 1;
			}
			counter++;
		}
	}
	double result = 0 , result2 = 4;
	if (turn)
	{
		for (int i = 0; i < counter; i++)
		{
			if (chooser[i] > result)
				result = chooser[i];
		}
	}
	else
	{
		for (int i = 0; i < counter; i++)
		{
			result += chooser[i];
			if (chooser[i] < result2)
				result2 = chooser[i];
		}
		//cout << "{ " << result << "-"<< counter << " }";
		result = result / counter;

		result = result * stupidity + result2 * (1 - stupidity) ;
	}
	//for (int i = 0; i < counter; i++)
		//cout << " " << i << " " << chooser[i] << endl;
	//state.print();
	//system("pause");

	return result;
}

int autoPlayer::move(int player)
{
	int resultPos = -1;
	double prob = -2.1 , temp;
	int oppPlayer = (player == rows * cols + 1) ? (player + 1) : (player - 1);
	for (int i = 0; i < cols; i++)
	{
		if (Original->at(0, i) == 0)
		{
			Original->play(i , player);
			temp = winProbability(player, false, *Original, 1 , i) - winProbability(oppPlayer, true, *Original, 1 , i);
			Original->unPlay(i);
			// cout << "Coulumns Considered :" << i + 1 << " Maximer:" << temp << endl; 
			if (temp > prob)
			{
				resultPos = i;
				prob = temp;
			}
		}
	}
	cout << "Column Chosen :" << resultPos + 1 << endl;
	return resultPos;
}
