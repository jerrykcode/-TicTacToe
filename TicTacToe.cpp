#include "stdafx.h"
#include "TicTacToe.h"


typedef char SearchType;
#define SEARCH_MAX '0' //Search for max score as best
#define SEARCH_MIN '1' //Search for minimum score as best

RESULT TicTacToe::getResult() {
	RESULT result;
	result = rowResult();
	if (result != NO_RESULT)
		return result;
	result = colResult();
	if (result != NO_RESULT)
		return result;
	result = diagResult();
	if (result != NO_RESULT)
		return result;
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++) {
			if (board[row][col] == EMPTY) return NO_RESULT;
		}
	return DRAW;
}

RESULT TicTacToe::rowResult() {
	for (int row = 0; row < NROWS; row++) {
		if (board[row][0] == EMPTY) continue;
		bool rowEqual = true;
		for (int col = 0; col < NCOLS; col++) {
			if (board[row][col] != board[row][0]) {
				rowEqual = false;
				break;
			}
		}
		if (rowEqual) {
			if (board[row][0] == X) return X_WON;
			else return O_WON;
		}
	}
	return NO_RESULT;
}

RESULT TicTacToe::colResult() {
	for (int col = 0; col < NCOLS; col++) {
		if (board[0][col] == EMPTY) continue;
		bool colEqual = true;
		for (int row = 0; row < NROWS; row++) {
			if (board[row][col] != board[0][col]) {
				colEqual = false;
				break;
			}
		}
		if (colEqual) {
			if (board[0][col] == X) return X_WON;
			else return O_WON;
		}
	}
	return NO_RESULT;
}

RESULT TicTacToe::diagResult() {
	bool leftEqual = true, rightEqual = true;
	for (int row = 0; row < NROWS; row++) {
		if (board[row][row] != board[0][0]) leftEqual = false;
		if (board[row][NCOLS - row - 1] != board[0][NCOLS - 1]) rightEqual = false;
	}
	if (leftEqual) {
		switch (board[0][0]) {
		case X: {
			return X_WON;
			break;
		}
		case O: {
			return O_WON;
			break;
		}
		default: {
			return NO_RESULT;
			break;
		}
		}
	}
	if (rightEqual) {
		switch (board[0][NCOLS - 1]) {
		case X: {
			return X_WON;
			break;
		}
		case O: {
			return O_WON;
			break;
		}
		default: {
			return NO_RESULT;
			break;
		}
		}
	}
	return NO_RESULT;
}

void TicTacToe::addX(int row, int col) {
	board[row][col] = X;
}

void TicTacToe::addO(int row, int col) {
	board[row][col] = O;
}

void TicTacToe::computer() {
	int row, col;
	if (computerType == X) {
		getBestPosition(&row, &col, X);
		addX(row, col);
	}
	else {
		getBestPosition(&row, &col, O);
		addO(row, col);
	}
}

int TicTacToe::getBestPosition(int *pBestRow, int *pBestCol, ChessType chessType) {
	SearchType searchType = chessType == computerType ? SEARCH_MAX : SEARCH_MIN;
	int bestScore = searchType == SEARCH_MAX ? -1 : 1;
	int bestRow, bestCol;
	bool hasBestInit = false;
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++) {
			//Traverses all empty positions
			if (board[row][col] == EMPTY) {
				int currentScore;
				board[row][col] = chessType;
				RESULT result = getResult();
				if (result != NO_RESULT) {
					currentScore = score[result];
				}
				else {
					currentScore = getBestPosition(pBestRow, pBestCol, REVERSE_CHESS_TYPE(chessType));
				}
				board[row][col] = EMPTY;
				if (searchType == SEARCH_MAX) { //If the position with the max score is the optium
					if (currentScore > bestScore || !hasBestInit) {
						bestScore = currentScore;
						bestRow = row;
						bestCol = col;
						hasBestInit = true;
						if (currentScore == 1) goto RETURN;
					}
				}
				else { //If the position with the minimum score is the optium
					if (currentScore < bestScore || !hasBestInit) {
						bestScore = currentScore;
						bestRow = row;
						bestCol = col;
						hasBestInit = true;
						if (currentScore == -1) goto RETURN;
					}
				}
			}
		}
RETURN: {
	*pBestRow = bestRow;
	*pBestCol = bestCol;
	return bestScore;
	}
}

void TicTacToe::getBoard(Board outputBoard) {
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++)
			outputBoard[row][col] = board[row][col];
}

