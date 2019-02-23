#include "pch.h"
#include "Game.h"
#include<iostream>

using namespace std;

Game::Game(int r , int c) : rows(r) , cols(c)
{
	board = new int[r*c];
	for (int i = 0; i < r*c; i++)
		board[i] = 0;

	redPiece = r * c + 1;
	yellowPiece = r * c + 2;
	turn = 1;
}

int Game::at(int r, int c)
{
	return board[r*cols + c];
}

int Game::getRows()
{
	return rows;
}

int Game::getCols()
{
	return cols;
}

void Game::modify(int r, int c, int val)
{
	board[r*cols + c] = val;
}

void Game::play(int c)
{
	// Choose piece
	int piece = (turn == 1) ? redPiece : yellowPiece;

	for (int i = rows - 1; i >= 0; i--)
	{
		if (at(i, c) == 0)
		{
			modify(i, c, piece);
			break;
		}
	}

	// Change Turn
	turn = (turn == 1) ? 2 : 1; 
}

void Game::play(int c, int piece)
{
	for (int i = rows - 1; i >= 0; i--)
	{
		if (at(i, c) == 0)
		{
			modify(i, c, piece);
			break;
		}
	}
}

int Game::getTurn()
{
	return turn;
}
int Game::checkWinner()
{
	int winner = -1, counter;
	for (int player = rows * cols + 1; player < rows*cols + 3; player++)
	{
		counter = 0;
		// Horizontal
		for (int i = 0; i < rows; i++)
		{
			counter = 0;
			for (int j = 0; j < cols; j++)
			{
				if (at(i, j) == player)
				{
					counter++;
					if (counter == 4)
					{
						if (winner == -1 || winner == player)
							winner = player;
						else
							winner = -2; // -2 means multiple Winners
					}
				}
				else
				{
					counter = 0;
				}
			}
		}
		// Vertical
		counter = 0;
		for (int i = 0; i < rows; i++)
		{
			counter = 0;
			for (int j = 0; j < cols; j++)
			{
				if (at(j, i) == player)
				{
					counter++;
					if (counter == 4)
					{
						if (winner == -1 || winner == player)
							winner = player;
						else
							winner = -2; // -2 means multiple Winners
					}
				}
				else
				{
					counter = 0;
				}
			}
		}
		// Diag 1
		counter = 0;
		int j;
		for (int k = 1; k <= cols; k++)
		{
			counter = 0;
			for (int i = 0; i < k && i < rows; i++)
			{
				j = cols - k + i;
				if (at(i, j) == player)
				{
					counter++;
					if (counter == 4)
					{
						if (winner == -1 || winner == player)
							winner = player;
						else
							winner = -2; // -2 means multiple Winners
					}
				}
				else
				{
					counter = 0;
				}
			}
		}
		int i;
		counter = 0;
		for (int k = 1; k < rows; k++)
		{
			counter = 0;
			for (int j = 0; j < k && j < cols; j++)
			{
				i = rows - k + j;
				if (at(i, j) == player)
				{
					counter++;
					if (counter == 4)
					{
						if (winner == -1 || winner == player)
							winner = player;
						else
							winner = -2; // -2 means multiple Winners
					}
				}
				else
				{
					counter = 0;
				}
			}
		}
		// Diag 2
		counter = 0;
		for (int k = 1; k <= rows; k++)
		{
			counter = 0;
			for (int j = 0; j < k && j < cols; j++)
			{
				i = k - j - 1;
				if (at(i, j) == player)
				{
					counter++;
					if (counter == 4)
					{
						if (winner == -1 || winner == player)
							winner = player;
						else
							winner = -2; // -2 means multiple Winners
					}
				}
				else
				{
					counter = 0;
				}
			}
		}
		counter = 0;
		for (int k = 1; k < cols; k++)
		{
			counter = 0;
			for (int i = rows - 1; rows - 1 - i < k && i > 0; i--)
			{
				j = rows + cols - k - i - 1;
				if (at(i, j) == player)
				{
					counter++;
					if (counter == 4)
					{
						if (winner == -1 || winner == player)
							winner = player;
						else
							winner = -2; // -2 means multiple Winners
					}
				}
				else
				{
					counter = 0;
				}
			}
		}
	}
	return winner;
}

bool Game::checkWinner(int column , int player)
{
	int topRow = 0;
	for (int i = 0; i < rows; i++)
	{
		if (at(i, column) != 0)
		{
			topRow = i;
			break;
		}
	}

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i != 0 || j != 0)
			{
				if (checkDir(column, topRow, player, i, j))
					return true;
			}
		}
	}
	return false;
}

bool Game::checkDir(int column , int topRow, int player, int delRow, int delCol)
{
	int counter = 1;
	int x, y;
	for (x = column + delCol, y = topRow + delRow ; x < cols && x >= 0 && y < cols && y >= 0; x += delCol)
	{
		if (at(x, y) == player)
			counter++;
		else
			break;
		if (counter >= 4)
			break;
		y += delRow;
	}
	for (x = column - delCol, y = topRow - delRow; x < cols && x >= 0 && y < cols && y >= 0; x -= delCol)
	{
		if (at(x, y) == player)
			counter++;
		else
			break;
		if (counter >= 4)
			break;
		y -= delRow;
	}
	if (counter >= 4)
		return true;
	else
		return false;
}

int Game::evaluateChances(int player)
{
	int counter = 0 , chances = 0;
	// Horizontal
	for (int i = 0; i < rows; i++)
	{
		counter = 0;
		for (int j = 0; j < cols; j++)
		{
			if (at(i, j) == player)
			{
				counter++;
			}
			else if (counter == 3 && at(i, j) == 0)
			{
				chances += 1;
			}
			else
			{
				counter = 0;
			}
		}
	}
	// Vertical
	counter = 0;
	for (int i = 0; i < rows; i++)
	{
		counter = 0;
		for (int j = 0; j < cols; j++)
		{
			if (at(j, i) == player)
			{
				counter++;
			}
			else if (counter == 3 && at(i, j) == 0)
			{
				chances += 1;
			}
			else
			{
				counter = 0;
			}
		}
	}
	// Diag 1
	counter = 0;
	int j;
	for (int k = 1; k <= cols; k++)
	{
		counter = 0;
		for (int i = 0; i < k && i < rows; i++)
		{
			j = cols - k + i;
			if (at(i, j) == player)
			{
				counter++;
			}
			else if (counter == 3 && at(i, j) == 0)
			{
				chances += 1;
			}
			else
			{
				counter = 0;
			}
		}
	}
	int i;
	counter = 0;
	for (int k = 1; k < rows; k++)
	{
		counter = 0;
		for (int j = 0; j < k && j < cols; j++)
		{
			i = rows - k + j;
			if (at(i, j) == player)
			{
				counter++;

			}
			else if (counter == 3 && at(i, j) == 0)
			{
				chances += 1;
			}
			else
			{
				counter = 0;
			}
		}
	}
	// Diag 2
	counter = 0;
	for (int k = 1; k <= rows; k++)
	{
		counter = 0;
		for (int j = 0; j < k && j < cols; j++)
		{
			i = k - j - 1;
			if (at(i, j) == player)
			{
				counter++;
			}
			else if (counter == 3 && at(i, j) == 0)
			{
				chances += 1;
			}
			else
			{
				counter = 0;
			}
		}
	}
	counter = 0;
	for (int k = 1; k < cols; k++)
	{
		counter = 0;
		for (int i = rows - 1; rows - 1 - i < k && i > 0; i--)
		{
			j = rows + cols - k - i - 1;
			if (at(i, j) == player)
			{
				counter++;
			}
			else if (counter == 3 && at(i, j) == 0)
			{
				chances += 1;
			}
			else
			{
				counter = 0;
			}
		}
	}
	return chances;
}

void Game::print()
{
	cout << "  ";
	for (int i = 0 ; i< cols ; i++)
		cout << " " << i+1;
	cout << endl;
	for (int i = 0; i < rows; i++)
	{
		cout << i + 1 << " ";
		for (int j = 0; j < cols; j++)
		{
			if (at(i, j) == redPiece)
			{
				cout << " R";
			}
			else if (at(i, j) == yellowPiece)
			{
				cout << " Y";
			}
			else if(at(i , j) == 0)
				cout << " *";
		}
		cout << endl;
	}
	cout << endl;
}

void Game::unPlay(int c)
{
	for (int i = 0; i < rows; i++)
	{
		if (at(i, c) != 0)
		{
			modify(i, c, 0);
			break;
		}
	}
	//turn = (turn == 2) ? 1 : 2;
}
