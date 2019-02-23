#pragma once
class Game
{
	const int rows;
	const int cols;
	int redPiece;
	int yellowPiece;
	int *board;
	int turn;
	
	void modify(int r, int c, int val);
public:
	Game(int r , int c);
	int at(int r, int c);
	int getRows();
	int getCols();

	void play(int c);
	void play(int c, int piece);
	int getTurn();
	int checkWinner();
	bool checkWinner(int i, int player);
	bool checkDir(int column , int topRow, int player, int delRow, int delCol);
	int evaluateChances(int player);
	void print();
	void unPlay(int c);
};

