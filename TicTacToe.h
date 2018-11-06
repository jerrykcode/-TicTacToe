#pragma once

#include <algorithm>
using namespace std;

#define X 'X'           /* 'X' in tic tac toe */
#define O 'O'			/* 'O' in tic tac toe */
#define EMPTY ' '       /* No chess */
#define REVERSE_CHESS_TYPE(chessType) (chessType == X ? O : X)
#define NROWS 3
#define NCOLS NROWS
typedef char ** Board;	//Chess board
typedef char ChessType; //Type of the chess, 'X' or 'O'

//The result of the game
typedef enum {
	X_WON = 0,
	O_WON = 1,
	DRAW = 2,
	NO_RESULT,  /* No result yet */
} RESULT;

class TicTacToe {
public:
	//Constructor
	TicTacToe(ChessType computerType) : computerType(computerType)
	{
		//Initialize the chess board
		board = new char*[NROWS];
		for (int i = 0; i < NROWS; i++) {
			board[i] = new char[NCOLS];
			fill(board[i], board[i] + NCOLS, EMPTY); //No chess on the board initial
		}
		score[X_WON] = computerType == X ? 1 : -1;
		score[O_WON] = computerType == X ? -1 : 1;
		score[DRAW] = 0;
	}

	//Destructor
	~TicTacToe() {
		for (int i = 0; i < NROWS; i++)
			free(board[i]);
		free(board);
	}

	/* Returns the result of the game. */
	RESULT getResult();

	/* Adds a chess 'X' on the board at the specific position indicated by @param row and @param col. */
	void addX(int row, int col);

	/* Adds a chess 'O' on the board at the specific position indicated by @param row and @param col. */
	void addO(int row, int col);

	/* */
	void computer();

	ChessType computerType; //The chess type of the computer

	/* Returns the chess type of the computer. */
	ChessType getComputerType() {
		return computerType;
	}

	int score[3]; //The score of diferent result

	/* Sets the value of @param outputBoard with the value of board. */
	void getBoard(Board outputBoard);
private:

	Board board; //The chess board

	RESULT rowResult();
	RESULT colResult();
	RESULT diagResult();

	/*!

	@function getBestPosition

	@brief Gets the best position for the current condition.

	@description DFS深搜

	Traverses all Empty positions on the board, and for each position put chess of chessType type on it. If the result has been 
	determined, the score of this position is the corresponding score of the result(win +1, lose -1, draw 0). If the result is not 
	determined at this	time, the opponent plays chess recursively. The paramter chessType in the recursion function is given the 
	opposite type of current chessType(current X, recursion calculation O; Current O, recursively compute X). After calculating the 
	score of chess playing at this position, we need to restore this position to Empty.
	Note that if chessType==computerType, the position of the maximum score is the optimal position; otherwise, the position of the 
	minimum score is the optimal position.
	As the recursion moves to the next level, the search type for optimal position changes as a result of chessType changes.

	遍历棋盘上所有Empty的位置，在位置上放入chessType类型的棋子，此时若已判出结果，则此位置
	的分数为该结果对应的分数(胜+1分，败-1分，平0分)；若此时尚未判出结果，则递归计算对手下棋，
	递归函数中chessType赋为当前chessType的反类型(当前X，递归计算O；当前O，递归计算X)，以递归
	结果为此位置分数。计算出在此位置下棋的分数后，需要将此位置还原为Empty。
	注意若chessType==computerType，则最大分数的位置为最优位置，否则最小分数的位置为最优位置。
	递归进入下一层后，由于chessType变化，最优位置是分数最大还是分数最小也变化。

	@param pBestRow
	Pointer to the row index of the best position.

	@param pBestCol
	Pointer to the column index of the best position.

	@param chessType
	The chess type of this turn

	@return Returns the score of the best position, 1 for win, -1 for lose and 0 for draw.
	*/
	int getBestPosition(int *pBestRow, int *pBestCol, ChessType chessType);
};