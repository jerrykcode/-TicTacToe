#include "stdafx.h"
#include "TicTacToe.h"


typedef char SearchType;
#define SEARCH_MAX '0' //Search for max score as best
#define SEARCH_MIN '1' //Search for minimum score as best

#define NO_ALPHA_BETA (MIN_SCORE - 1)

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
		getBestPosition(X, NO_ALPHA_BETA, &row, &col);
		addX(row, col);
	}
	else {
		getBestPosition(O, NO_ALPHA_BETA, &row, &col);
		addO(row, col);
	}
}

int TicTacToe::getBestPosition(ChessType chessType, int preBestScore, int *pBestRow, int *pBestCol) {
	SearchType searchType = chessType == computerType ? SEARCH_MAX : SEARCH_MIN;
	int bestRow, bestCol, bestScore = searchType == SEARCH_MAX ? MIN_SCORE : MAX_SCORE;
	bool hasBestInit = false;
	for (int row = 0; row < NROWS; row++)
		for (int col = 0; col < NCOLS; col++) {
			if (board[row][col] == EMPTY) {
				board[row][col] = chessType;
				RESULT result = getResult();
				int currentScore;
				if (result != NO_RESULT) {
					currentScore = score[result];
				}
				else {
					currentScore = getBestPosition(REVERSE_CHESS_TYPE(chessType), bestScore, pBestRow, pBestCol);
				}
				board[row][col] = EMPTY;
				if (searchType == SEARCH_MAX) { //If the position with max score is optium					
					if (!hasBestInit || currentScore > bestScore) {
						bestRow = row;
						bestCol = col;
						bestScore = currentScore;
						hasBestInit = true;
					}
					if (preBestScore != NO_ALPHA_BETA && currentScore > preBestScore) goto END;
					if (currentScore == MAX_SCORE) goto END;
				}
				else { //If the position with minmum score is optium					
					if (!hasBestInit || currentScore < bestScore) {
						bestRow = row;
						bestCol = col;
						bestScore = currentScore;
						hasBestInit = true;
					}
					if (preBestScore != NO_ALPHA_BETA && currentScore < preBestScore) goto END;
					if (currentScore == MIN_SCORE) goto END;
				}
			}
		}
END: {
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


