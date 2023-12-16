#include "chess.h"

void new_game(Chess *chess) {
	chess->position[0][0] = 'r';
	chess->position[0][7] = 'r';
	chess->position[0][1] = 'n';
	chess->position[0][6] = 'n';
	chess->position[0][2] = 'b';
	chess->position[0][5] = 'b';
	chess->position[0][3] = 'q';
	chess->position[0][4] = 'k';

	chess->position[7][0] = 'R';
	chess->position[7][7] = 'R';
	chess->position[7][1] = 'N';
	chess->position[7][6] = 'N';
	chess->position[7][2] = 'B';
	chess->position[7][5] = 'B';
	chess->position[7][3] = 'Q';
	chess->position[7][4] = 'K';

	for(int i = 0; i < 8; i++) {
		chess->position[1][i] = 'p';
		chess->position[6][i] = 'P';
	}

	for(int i = 2; i < 6; i++)
		for(int j = 0; j < 8; j++)
			chess->position[i][j] = ' ';

	reset(chess->possible);

	chess->x = -1;
	chess->y = -1;
	chess->mate = 0;
	chess->enpassant = -1;
	chess->oo_white = true;
	chess->ooo_white = true;
	chess->oo_black = true;
	chess->ooo_black = true;
	chess->moved = false;
	chess->turn = true;
	chess->ch = true;
}

void reset(int possible[8][8]) {
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			possible[i][j] = 0;
}

bool white(char piece) {
	return piece >= 'A' && piece <= 'Z';
}
bool black(char piece) {
	return piece >= 'a' && piece <= 'z';
}
bool piece(char piece) {
	return white(piece) || black(piece);
}

void play(Chess *chess, int x1, int y1) {
	chess -> capture = false;
	chess -> moved = false;
	if(chess -> x == -1 || chess -> y == -1) {
		if((chess -> turn && white(chess -> position[x1][y1])) || (!chess -> turn && black(chess -> position[x1][y1]))) {
			chess -> x = x1;
			chess -> y = y1;
			pawn(chess);
			knight(chess);
			bishop(chess);
			rook(chess);
			king(chess);
		}
	}
	else {
		if(chess -> possible[x1][y1]) {
			update_enpassant(chess, x1, y1);
			castle(chess, x1, y1);
			if(chess -> position[x1][y1] != ' ') chess -> capture = true;
			make_move(chess, x1, y1);
			chess -> position[x1][y1] = chess -> position[chess -> x][chess -> y];
			chess -> position[chess -> x][chess -> y] = ' ';
			promotion(chess, x1, y1);
			chess -> moved = true;
			chess -> turn = !chess -> turn;
			end(chess);
			if(chess->mate == 1 && check(chess, -1, -1)) {
				chess->mate++;
				if(chess->turn) {
					chess->mate++;
				}
			}
		}
		chess -> x = -1;
		chess -> y = -1;
		reset(chess -> possible);
	}
}

void play_move(Chess* chess, char *move) {
	play(chess, 56 - move[2], move[1] - 65);
	play(chess, 56 - move[4], move[3] - 65);
}

void make_move(Chess* chess, int x1, int y1) {
	chess->move[0] = chess->position[chess->x][chess->y];
	chess->move[1] = chess->y + 65;
	chess->move[2] = 56 - chess->x;
	chess->move[3] = y1 + 65;
	chess->move[4] = 56 - x1;
}

bool check_square(Chess* chess, int x1, int y1) {
	if (x1 < 8 && x1 >= 0 && y1 < 8 && y1 >= 0 && (!chess -> ch || !check(chess, x1, y1)) &&
			((!white(chess -> position[x1][y1]) && white(chess -> position[chess -> x][chess -> y])) ||
			 (!black(chess -> position[x1][y1]) && black(chess -> position[chess -> x][chess -> y])))) {
		if((!chess -> turn && chess -> position[x1][y1] == 'k') || (chess -> turn && chess -> position[x1][y1] == 'K'))
			chess -> next_check = true;
		if(chess -> ch) chess -> mate = 0;
		return true;
	}
	return false;
}

void pawn(Chess *chess) {
	if(chess -> position[chess -> x][chess -> y] == 'P') {
		if(!piece(chess -> position[chess -> x - 1][chess -> y])) {
			if(check_square(chess, chess -> x - 1, chess -> y))
				chess -> possible[chess -> x - 1][chess -> y] = 1;
			if(chess -> x == 6 && !piece(chess -> position[chess -> x - 2][chess -> y]) && check_square(chess, chess -> x - 2, chess -> y))
				chess -> possible[chess -> x - 2][chess -> y] = 3;
		}
		if(chess -> x == 3 && chess -> enpassant == chess -> y - 1 && check_square(chess, chess -> x - 1, chess -> y - 1))
			chess -> possible[chess -> x - 1][chess -> y - 1] = 2;
		if(chess -> x == 3 && chess -> enpassant == chess -> y + 1 && check_square(chess, chess -> x - 1, chess -> y + 1))
			chess -> possible[chess -> x - 1][chess -> y + 1] = 2;
		if(black(chess -> position[chess -> x - 1][chess -> y - 1]) && check_square(chess, chess -> x - 1, chess -> y - 1))
			chess -> possible[chess -> x - 1][chess -> y - 1] = 1;
		if(black(chess -> position[chess -> x - 1][chess -> y + 1]) && check_square(chess, chess -> x - 1, chess -> y + 1))
			chess -> possible[chess -> x - 1][chess -> y + 1] = 1;
	}
	else if(chess -> position[chess -> x][chess -> y] == 'p') {
		if(!piece(chess -> position[chess -> x + 1][chess -> y])) {
			if(check_square(chess, chess -> x + 1, chess -> y))
				chess -> possible[chess -> x + 1][chess -> y] = 1;
			if(chess -> x == 1 && !piece(chess -> position[chess -> x + 2][chess -> y]) && check_square(chess, chess -> x + 2, chess -> y))
				chess -> possible[chess -> x + 2][chess -> y] = 3;
		}
		if(chess -> x == 4 && chess -> enpassant == chess -> y - 1 && check_square(chess, chess -> x + 1, chess -> y - 1))
			chess -> possible[chess -> x + 1][chess -> y - 1] = 2;
		if(chess -> x == 4 && chess -> enpassant == chess -> y + 1 && check_square(chess, chess -> x + 1, chess -> y + 1))
			chess -> possible[chess -> x + 1][chess -> y + 1] = 2;
		if(white(chess -> position[chess -> x + 1][chess -> y - 1]) && check_square(chess, chess -> x + 1, chess -> y - 1))
			chess -> possible[chess -> x + 1][chess -> y - 1] = 1;
		if(white(chess -> position[chess -> x + 1][chess -> y + 1]) && check_square(chess, chess -> x + 1, chess -> y + 1))
			chess -> possible[chess -> x + 1][chess -> y + 1] = 1;
	}
}

void promotion(Chess *chess, int x1, int y1) {
	if(x1 == 0 && chess -> position[x1][y1] == 'P')
		chess -> position[x1][y1] = 'Q';
	if(x1 == 7 && chess -> position[x1][y1] == 'p')
		chess -> position[x1][y1] = 'q';
}

void update_enpassant(Chess *chess, int x1, int y1) {
	if(chess -> possible[x1][y1] == 3)
		chess -> enpassant = y1;
	else
		chess -> enpassant = -1;
	if(chess -> possible[x1][y1] == 2){
		chess -> capture = true;
		if(chess -> position[chess -> x][chess -> y] == 'P')
			chess -> position[x1 + 1][y1] = ' ';
		else if(chess -> position[chess -> x][chess -> y] == 'p')
			chess -> position[x1 - 1][y1] = ' ';
	}
}

void knight(Chess *chess) {
	if(chess -> position[chess -> x][chess -> y] == 'N' || chess -> position[chess -> x][chess -> y] == 'n') {
		if(check_square(chess, chess -> x + 2, chess -> y + 1))
			chess -> possible[chess -> x + 2][chess -> y + 1] = 1;
		if(check_square(chess, chess -> x + 2, chess -> y - 1))
			chess -> possible[chess -> x + 2][chess -> y - 1] = 1;
		if(check_square(chess, chess -> x - 2, chess -> y + 1))
			chess -> possible[chess -> x - 2][chess -> y + 1] = 1;
		if(check_square(chess, chess -> x - 2, chess -> y - 1))
			chess -> possible[chess -> x - 2][chess -> y - 1] = 1;
		if(check_square(chess, chess -> x + 1, chess -> y + 2))
			chess -> possible[chess -> x + 1][chess -> y + 2] = 1;
		if(check_square(chess, chess -> x + 1, chess -> y - 2))
			chess -> possible[chess -> x + 1][chess -> y - 2] = 1;
		if(check_square(chess, chess -> x - 1, chess -> y + 2))
			chess -> possible[chess -> x - 1][chess -> y + 2] = 1;
		if(check_square(chess, chess -> x - 1, chess -> y - 2))
			chess -> possible[chess -> x - 1][chess -> y - 2] = 1;
	}
}

void bishop(Chess *chess) {
	if(chess -> position[chess -> x][chess -> y] == 'b' || chess -> position[chess -> x][chess -> y] == 'B' ||
			chess -> position[chess -> x][chess -> y] == 'q' || chess -> position[chess -> x][chess -> y] == 'Q') {
		for(int i = 1; chess -> x + i < 8 && chess -> y + i < 8; i++) {
			if(check_square(chess, chess -> x + i, chess -> y + i))
				chess -> possible[chess -> x + i][chess -> y + i] = 1;
			if(piece(chess -> position[chess -> x + i][chess -> y + i]))
				break;
		}
		for(int i = 1; chess -> x + i < 8 && chess -> y - i >= 0; i++) {
			if(check_square(chess, chess -> x + i, chess -> y - i))
				chess -> possible[chess -> x + i][chess -> y - i] = 1;
			if(piece(chess -> position[chess -> x + i][chess -> y - i]))
				break;
		}
		for(int i = 1; chess -> x - i >= 0 && chess -> y + i < 8; i++) {
			if(check_square(chess, chess -> x - i, chess -> y + i))
				chess -> possible[chess -> x - i][chess -> y + i] = 1;
			if(piece(chess -> position[chess -> x - i][chess -> y + i]))
				break;
		}
		for(int i = 1; chess -> x - i >= 0 && chess -> y - i >= 0; i++) {
			if(check_square(chess, chess -> x - i, chess -> y - i))
				chess -> possible[chess -> x - i][chess -> y - i] = 1;
			if(piece(chess -> position[chess -> x - i][chess -> y - i]))
				break;
		}
	}
}

void rook(Chess *chess) {
	if(chess -> position[chess -> x][chess -> y] == 'r' || chess -> position[chess -> x][chess -> y] == 'R' ||
			chess -> position[chess -> x][chess -> y] == 'q' || chess -> position[chess -> x][chess -> y] == 'Q') {
		for(int i = 1; chess -> x + i < 8; i++) {
			if(check_square(chess, chess -> x + i, chess -> y))
				chess -> possible[chess -> x + i][chess -> y] = 1;
			if(piece(chess -> position[chess -> x + i][chess -> y]))
				break;
		}
		for(int i = 1; chess -> x - i >= 0; i++) {
			if(check_square(chess, chess -> x - i, chess -> y))
				chess -> possible[chess -> x - i][chess -> y] = 1;
			if(piece(chess -> position[chess -> x - i][chess -> y]))
				break;
		}
		for(int i = 1; chess -> y + i < 8; i++) {
			if(check_square(chess, chess -> x, chess -> y + i))
				chess -> possible[chess -> x][chess -> y + i] = 1;
			if(piece(chess -> position[chess -> x][chess -> y + i]))
				break;
		}
		for(int i = 1; chess -> y - i >= 0; i++) {
			if(check_square(chess, chess -> x, chess -> y - i))
				chess -> possible[chess -> x][chess -> y - i] = 1;
			if(piece(chess -> position[chess -> x][chess -> y - i]))
				break;
		}
	}
}

void king(Chess *chess) {
	if(chess -> position[chess -> x][chess -> y] == 'k' || chess -> position[chess -> x][chess -> y] == 'K') {
		if(check_square(chess, chess -> x + 1, chess -> y))
			chess -> possible[chess -> x + 1][chess -> y] = 1;
		if(check_square(chess, chess -> x - 1, chess -> y))
			chess -> possible[chess -> x - 1][chess -> y] = 1;
		if(check_square(chess, chess -> x, chess -> y + 1))
			chess -> possible[chess -> x][chess -> y + 1] = 1;
		if(check_square(chess, chess -> x, chess -> y - 1))
			chess -> possible[chess -> x][chess -> y - 1] = 1;
		if(check_square(chess, chess -> x + 1, chess -> y + 1))
			chess -> possible[chess -> x + 1][chess -> y + 1] = 1;
		if(check_square(chess, chess -> x + 1, chess -> y - 1))
			chess -> possible[chess -> x + 1][chess -> y - 1] = 1;
		if(check_square(chess, chess -> x - 1, chess -> y + 1))
			chess -> possible[chess -> x - 1][chess -> y + 1] = 1;
		if(check_square(chess, chess -> x - 1, chess -> y - 1))
			chess -> possible[chess -> x - 1][chess -> y - 1] = 1;
		// castle
		if(chess -> position[chess -> x][chess -> y] == 'K' && chess -> position[7][5] == ' ' && chess -> position[7][6] == ' ' && chess -> oo_white)
			if(chess -> ch && !check(chess, 7, 6) && !check(chess, 7, 5) && !check(chess, 7, 4))
				chess -> possible[7][6] = 4;
		if(chess -> position[chess -> x][chess -> y] == 'K' && chess -> position[7][3] == ' ' && chess -> position[7][2] == ' ' && chess -> position[7][1] == ' ' && chess -> ooo_white)
			if(chess -> ch && !check(chess, 7, 2) && !check(chess, 7, 3) && !check(chess, 7, 4))
				chess -> possible[7][2] = 5;
		if(chess -> position[chess -> x][chess -> y] == 'k' && chess -> position[0][5] == ' ' && chess -> position[0][6] == ' ' && chess -> oo_black)
			if(chess -> ch && !check(chess, 0, 6) && !check(chess, 0, 5) && !check(chess, 0, 4))
				chess -> possible[0][6] = 6;
		if(chess -> position[chess -> x][chess -> y] == 'k' && chess -> position[0][3] == ' ' && chess -> position[0][2] == ' ' && chess -> position[0][1] && chess -> ooo_black)
			if(chess -> ch && !check(chess, 0, 2) && !check(chess, 0, 3) && !check(chess, 0, 4))
				chess -> possible[0][2] = 7;
	}
}

void castle(Chess *chess, int x1, int y1) {
	if(chess -> position[7][7] != 'R')
		chess -> oo_white = false;
	if(chess -> position[7][0] != 'R')
		chess -> ooo_white = false;
	if(chess -> position[7][4] != 'K') {
		chess -> oo_white = false;
		chess -> ooo_white = false;
	}
	if(chess -> position[0][7] != 'r')
		chess -> oo_black = false;
	if(chess -> position[0][0] != 'r')
		chess -> ooo_black = false;
	if(chess -> position[0][4] != 'k') {
		chess -> oo_black = false;
		chess -> ooo_black = false;
	}

	if(chess -> possible[x1][y1] == 4) {
		chess -> position[7][5] = chess -> position[7][7];
		chess -> position[7][7] = ' ';
	}
	if(chess -> possible[x1][y1] == 5) {
		chess -> position[7][3] = chess -> position[7][0];
		chess -> position[7][0] = ' ';
	}
	if(chess -> possible[x1][y1] == 6) {
		chess -> position[0][5] = chess -> position[0][7];
		chess -> position[0][7] = ' ';
	}
	if(chess -> possible[x1][y1] == 7) {
		chess -> position[0][3] = chess -> position[0][0];
		chess -> position[0][0] = ' ';
	}
}

bool check(Chess *chess, int x1, int y1) {
	chess->ch = false;
	chess->next_check = false;
	int tmp_x = chess->x;
	int tmp_y = chess->y;
	char tmp_piece = chess->position[x1][y1];
	if(x1 != -1) {
		chess->position[x1][y1] = chess->position[chess->x][chess->y];
		chess->position[chess->x][chess->y] = ' ';
	}
	int tmp_possible[8][8];
	memcpy(tmp_possible, chess->possible, 64 * sizeof(int));

	for(int i = 0; i < 8 && !chess->next_check; i++) {
		for(int j = 0; j < 8 && !chess->next_check; j++) {
			if((chess->turn && black(chess->position[i][j])) || (!chess->turn && white(chess->position[i][j]))) {
				chess->x = i;
				chess->y = j;
				reset(chess->possible);
				pawn(chess);
				knight(chess);
				bishop(chess);
				rook(chess);
				king(chess);
			}
		}
	}
	chess->x = tmp_x;
	chess->y = tmp_y;
	if(x1 != -1) {
		chess->position[chess->x][chess->y] = chess->position[x1][y1];
		chess->position[x1][y1] = tmp_piece;
	}
	memcpy(chess->possible, tmp_possible, 64 * sizeof(int));
	chess->ch = true;
	return chess->next_check;
}

void end(Chess *chess) {
	chess -> mate = 1;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if((chess->turn && white(chess->position[i][j])) || (!chess->turn && black(chess->position[i][j]))) {
				chess->x = i;
				chess->y = j;
				reset(chess->possible);
				pawn(chess);
				knight(chess);
				bishop(chess);
				rook(chess);
				king(chess);
			}
		}
	}
	if(chess->mate && check(chess, -1, -1)) {
		chess->mate++;
		if(chess->turn) {
			chess->mate++;
		}
	}
}
