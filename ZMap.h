#pragma once

/*
@File ZMap.h

@Description Define a class "ZMap" for Zobrist hashing

*/

#include "Board.h"
#include <map>
#include <random>
using namespace std;

struct BestPosition {
	BestPosition(int bestScore, int bestRow, int bestCol) :
		bestScore(bestScore),
		bestRow(bestRow),
		bestCol(bestCol) 
	{
	
	}
	
	BestPosition() {
		BestPosition(0, 0, 0);
	}

	int bestScore;
	int bestRow, bestCol;
};

class ZMap {
public:
	ZMap(int n);
	~ZMap();
	
	void insert(Board board, BestPosition pos);

	BestPosition value(Board board);

	bool hasKey(Board board);

private:

	int toInt(Board board);

	int** initWithRand(int n);
	void free2DArray(int **arr, int n);

	int n;
	default_random_engine rand;
	int **XBoard;
	int **OBoard;
	int **emptyBoard;
	map<int, BestPosition> map_;
};