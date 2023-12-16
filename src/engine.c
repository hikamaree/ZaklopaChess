#include "engine.h"

double calc_eval(Chess* chess) {
	double white = 0;
	double black = 0;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			switch (chess->position[i][j]) {
				case 'Q':
					white += 9.0;
					break;
				case 'R':
					white += 5.0;
					break;
				case 'B':
					white += 3.0;
					break;
				case 'N':
					white += 3.0;
					break;
				case 'P':
					white += 1.0;
					break;
				case 'q':
					black += 9.0;
					break;
				case 'r':
					black += 5.0;
					break;
				case 'b':
					black += 3.0;
					break;
				case 'n':
					black += 3.0;
					break;
				case 'p':
					black += 1.0;
					break;
			}
		}
	}
	return white - black;
}

void calculate(Chess* chess) {
	double eval = calc_eval(chess);
	char move[5];
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			if((chess->turn && white(chess->position[x][y])) || (!chess->turn && black(chess->position[x][y]))) {
				Chess c = *chess;
				c.x = x;
				c.y = y;
				pawn(&c);
				knight(&c);
				bishop(&c);
				rook(&c);
				king(&c);
				for(int x1 = 0; x1 < 8; x1++){
					for(int y1 = 0; y1 < 8; y1++) {
						Chess c1 = c;
						if(c1.possible[x1][y1]) {
							make_move(&c1, x1, y1);
							update_enpassant(&c1, x1, y1);
							castle(&c1, x1, y1);
							c1.position[x1][y1] = c1.position[c1.x][c1.y];
							c1.position[c1.x][c1.y] = ' ';
							promotion(&c1, x1, y1);
							double tmp = calc_eval(&c1);
							if(eval >= tmp) {
								eval = tmp;
								memcpy(move, c1.move, 5);
							}
						}
					}
				}
			}
		}
	}
	play_move(chess, move);
}
