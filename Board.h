#pragma once

#define X 'X'           /* 'X' in tic tac toe */
#define O 'O'			/* 'O' in tic tac toe */
#define EMPTY ' '       /* No chess */
#define REVERSE_CHESS_TYPE(chessType) (chessType == X ? O : X)
#define NROWS 3
#define NCOLS NROWS
typedef char ** Board;	//Chess board
typedef char ChessType; //Type of the chess, 'X' or 'O'

#define MAX_SCORE 1
#define MIN_SCORE -1