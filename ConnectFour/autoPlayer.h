#pragma once
#include"Game.h"
class autoPlayer
{
	Game *Original;
	int rows, cols;
	//Game state;

	const int maxDepth ;
	double evalChanceReduce; // take care it should be double
	double stupidity; // How Stupid is the opposite Player ? 
	double greed;
public:
	autoPlayer(Game *Original , int depth , double evalReduce , double stupidity , double greed);
	double winProbability(int player, bool turn , Game state , int depth , int column);
	int move(int player);
};

