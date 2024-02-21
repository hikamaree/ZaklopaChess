#include "engine.h"
#include "chess.h"

double evaluate(Square** board) {
	double white = 0;
	double black = 0;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			switch (board[i][j]) {
				case WHITE_KING:
					white += 100.0;
					break;
				case WHITE_QUEEN:
					white += 9.0;
					break;
				case WHITE_ROOK:
					white += 5.0;
					break;
				case WHITE_BISHOP:
					white += 3.0;
					break;
				case WHITE_KNIGHT:
					white += 3.0;
					break;
				case WHITE_PAWN:
					white += 1.0;
					break;
				case BLACK_KING:
					black += 100.0;
					break;
				case BLACK_QUEEN:
					black += 9.0;
					break;
				case BLACK_ROOK:
					black += 5.0;
					break;
				case BLACK_BISHOP:
					black += 3.0;
					break;
				case BLACK_KNIGHT:
					black += 3.0;
					break;
				case BLACK_PAWN:
					black += 1.0;
					break;
				case EMPTY:
					break;
			}
		}
	}
	return white - black;
}

void calculate(Square** board, bool turn) {
	//ovaj deo nije bio zdrav za oci
	return;
}
