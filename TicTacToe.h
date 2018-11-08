#pragma once

#include "Board.h"
#include "ZMap.h"
#include <algorithm>
using namespace std;

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
		score[X_WON] = computerType == X ? MAX_SCORE : MIN_SCORE;
		score[O_WON] = computerType == X ? MIN_SCORE : MAX_SCORE;
		score[DRAW] = 0;

		zmap = *(new ZMap(NROWS));
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

	ZMap zmap = NULL;

	RESULT rowResult();
	RESULT colResult();
	RESULT diagResult();

	/*!

	@function getBestPosition

	@brief Gets the best position for the current condition.

	@description DFS����

	Traverses all Empty positions on the board, and for each position put chess of chessType type on it. If the result has been 
	determined, the score of this position is the corresponding score of the result(win +1, lose -1, draw 0). If the result is not 
	determined at this	time, the opponent plays chess recursively. The paramter chessType in the recursion function is given the 
	opposite type of current chessType(current X, recursion calculation O; Current O, recursively compute X). After calculating the 
	score of chess playing at this position, we need to restore this position to Empty.
	Note that if chessType==computerType, the position of the maximum score is the optimal position; otherwise, the position of the 
	minimum score is the optimal position.
	As the recursion moves to the next level, the search type for optimal position changes as a result of chessType changes.

	��������������Empty��λ�ã���λ���Ϸ���chessType���͵����ӣ���ʱ�����г���������λ��
	�ķ���Ϊ�ý����Ӧ�ķ���(ʤ+1�֣���-1�֣�ƽ0��)������ʱ��δ�г��������ݹ����������壬
	�ݹ麯����chessType��Ϊ��ǰchessType�ķ�����(��ǰX���ݹ����O����ǰO���ݹ����X)���Եݹ�
	���Ϊ��λ�÷�����������ڴ�λ������ķ�������Ҫ����λ�û�ԭΪEmpty��
	ע����chessType==computerType������������λ��Ϊ����λ�ã�������С������λ��Ϊ����λ�á�
	�ݹ������һ�������chessType�仯������λ���Ƿ�������Ƿ�����СҲ�仯��

	@param pBestRow
	Pointer to the row index of the best position.

	@param pBestCol
	Pointer to the column index of the best position.

	@param chessType
	The chess type of this turn

	@return Returns the score of the best position, 1 for win, -1 for lose and 0 for draw.
	*/
	int getBestPosition(ChessType chessType, int preBestScore, int *pBestRow, int *pBestCol);
};