#include "stdafx.h"
#include "ZMap.h"

ZMap::ZMap(int n): n(n) {
	XBoard = initWithRand(n);
	OBoard = initWithRand(n);
	emptyBoard = initWithRand(n);
}

ZMap::~ZMap() {
	free2DArray(XBoard, n);
	free2DArray(OBoard, n);
	free2DArray(emptyBoard, n);
}

int** ZMap::initWithRand(int n) {
	int **arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
		for (int j = 0; j < n; j++)
			arr[i][j] = rand();
	}
	return arr;
}

void ZMap::free2DArray(int **arr, int n) {
	for (int i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}

int ZMap::toInt(Board board) {
	int result = 0;
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++) {
			switch (board[row][col]) {
			case X: {
				result ^= XBoard[row][col];
				break;
			}
			case O: {
				result ^= OBoard[row][col];
				break;
			}
			case EMPTY: {
				result ^= emptyBoard[row][col];
				break;
			}
			default: break;
			}
		}
	return result;
}

void ZMap::insert(Board board, BestPosition pos) {
	int key = toInt(board);
	map_[key] = pos;
}

BestPosition ZMap::value(Board board) {
	int key = toInt(board);
	return map_[key];
}

bool ZMap::hasKey(Board board) {
	int key = toInt(board);
	map<int, BestPosition>::iterator it = map_.find(key);
	return it != map_.end();
}