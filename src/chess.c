#include "chess.h"
#include <stdlib.h>

Chess* init_chess() {
	Chess* chess = (Chess*)malloc(sizeof(Chess));
	chess->board = (Board)malloc(8 * sizeof(Square*));
	Square* p1 = (Square*)malloc(64 * sizeof(Square));
	for(int i = 0; i < 8; i++) {
		chess->board[i] = p1 + 8 * i;
	}
	chess->moves = (Move**)malloc(8 * sizeof(Move*));
	Move *p2 = (Move*)malloc(64 * sizeof(Move));
	for(int i = 0; i < 8; i++) {
		chess->moves[i] = p2 + 8 * i;
	}
	new_game(chess);
	return chess;
}

void delete_chess(Chess* chess) {
	free(*chess->board);
	free(chess->board);
	free(*chess->moves);
	free(chess->moves);
	free(chess);
}

void set_possition(Chess* chess, char* board) {
	int x = 0;
	int y = 0;
	memset(*chess->board, EMPTY, 64 * sizeof(char));
	for(int i = 0; board[i] != '\0' && x < 8; board++) {
		if(board[i] == '/') {
			x++;
			y = 0;
		}
		else if(piece(board[i])) {
			chess->board[x][y] = board[i];
			y++;
		}
		else if (board[i] >= '0' && board[i] <= '9') {
			y += board[i] - '0';
		}
	}
}

void new_game(Chess *chess) {
	set_possition(chess, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	reset(chess->moves);
	chess->x = -1;
	chess->y = -1;
	chess->mate = NONE;
	chess->enpassant = -1;
	chess->oo_white = true;
	chess->ooo_white = true;
	chess->oo_black = true;
	chess->ooo_black = true;
	chess->moved = false;
	chess->turn = true;
	chess->ch = true;
}

void select_piece(Chess* chess, int x, int y) {
	if((chess->ch && ((chess->turn && white(chess->board[x][y])) || (!chess->turn && black(chess->board[x][y])))) ||
			(!chess->ch && ((chess->turn && black(chess->board[x][y])) || (!chess->turn && white(chess->board[x][y]))))) {
		chess->x = x;
		chess->y = y;
		if(chess->board[chess->x][chess->y] == WHITE_PAWN || chess->board[chess->x][chess->y] == BLACK_PAWN) {
			pawn(chess);
		}
		if(chess->board[chess->x][chess->y] == WHITE_KNIGHT || chess->board[chess->x][chess->y] == BLACK_KNIGHT) {
			knight(chess);
		}
		if(chess->board[chess->x][chess->y] == WHITE_BISHOP || chess->board[chess->x][chess->y] == BLACK_BISHOP) {
			bishop(chess);
		}
		if(chess->board[chess->x][chess->y] == WHITE_ROOK || chess->board[chess->x][chess->y] == BLACK_ROOK) {
			rook(chess);
		}
		if(chess->board[chess->x][chess->y] == WHITE_QUEEN || chess->board[chess->x][chess->y] == BLACK_QUEEN) {
			bishop(chess);
			rook(chess);
		}
		if(chess->board[chess->x][chess->y] == WHITE_KING || chess->board[chess->x][chess->y] == BLACK_KING) {
			king(chess);
		}
	}
}

void move_piece(Chess* chess, int x, int y) {
	if(chess->moves[x][y]) {
		update_enpassant(chess, x, y);
		castle(chess, x, y);
		if(chess->board[x][y] != EMPTY) {
			chess->capture = true;
		}
		make_move(chess, x, y);
		chess->board[x][y] = chess->board[chess->x][chess->y];
		chess->board[chess->x][chess->y] = ' ';
		promotion(chess, x, y);
		chess->moved = true;
		chess->turn = !chess->turn;
		check_mate(chess);
	}
	chess->x = -1;
	chess->y = -1;
	reset(chess->moves);
}

void play(Chess *chess, int x, int y) {
	chess->capture = false;
	chess->moved = false;
	if(chess->x == -1 || chess->y == -1) {
		select_piece(chess, x, y);
	}
	else {
		move_piece(chess, x, y);
	}
}

void play_move(Chess* chess, char *move) {
	if(!strcmp(move, RESIGN_WHITE)) {
		chess->mate = BLACK_WON;
		return;
	}
	if(!strcmp(move, RESIGN_BLACK)) {
		chess->mate = WHITE_WON;
		return;
	}
	play(chess, '8' - move[2], move[1] - 'A');
	play(chess, '8' - move[4], move[3] - 'A');
}

void make_move(Chess* chess, int x1, int y1) {
	chess->move[0] = chess->board[chess->x][chess->y];
	chess->move[1] = chess->y + 'A';
	chess->move[2] = '8' - chess->x;
	chess->move[3] = y1 + 'A';
	chess->move[4] = '8' - x1;
}

bool check_square(Chess* chess, int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8 && (!chess->ch || !check(chess, x, y)) &&
			((!white(chess->board[x][y]) && white(chess->board[chess->x][chess->y])) ||
			 (!black(chess->board[x][y]) && black(chess->board[chess->x][chess->y])))) {
		if((!chess->turn && chess->board[x][y] == BLACK_KING) || (chess->turn && chess->board[x][y] == WHITE_KING)) {
			chess->next_check = true;
		}
		if(chess->ch) {
			chess->mate = NONE;
		}
		return true;
	}
	return false;
}

void pawn(Chess *chess) {
	if(chess->board[chess->x][chess->y] == WHITE_PAWN) {
		if(!piece(chess->board[chess->x - 1][chess->y])) {
			if(check_square(chess, chess->x - 1, chess->y)) {
				chess->moves[chess->x - 1][chess->y] = POSSIBLE_MOVE;
			}
			if(chess->x == 6 && !piece(chess->board[chess->x - 2][chess->y]) && check_square(chess, chess->x - 2, chess->y)) {
				chess->moves[chess->x - 2][chess->y] = ENABLE_ENPASSANT;
			}
		}
		if(chess->x == 3 && chess->enpassant == chess->y - 1 && check_square(chess, chess->x - 1, chess->y - 1)) {
			chess->moves[chess->x - 1][chess->y - 1] = PLAY_ENPASSANT;
		}
		if(chess->x == 3 && chess->enpassant == chess->y + 1 && check_square(chess, chess->x - 1, chess->y + 1)) {
			chess->moves[chess->x - 1][chess->y + 1] = PLAY_ENPASSANT;
		}
		if(black(chess->board[chess->x - 1][chess->y - 1]) && check_square(chess, chess->x - 1, chess->y - 1)) {
			chess->moves[chess->x - 1][chess->y - 1] = POSSIBLE_MOVE;
		}
		if(black(chess->board[chess->x - 1][chess->y + 1]) && check_square(chess, chess->x - 1, chess->y + 1)) {
			chess->moves[chess->x - 1][chess->y + 1] = POSSIBLE_MOVE;
		}
	}
	else if(chess->board[chess->x][chess->y] == BLACK_PAWN) {
		if(!piece(chess->board[chess->x + 1][chess->y])) {
			if(check_square(chess, chess->x + 1, chess->y)) {
				chess->moves[chess->x + 1][chess->y] = POSSIBLE_MOVE;
			}
			if(chess->x == 1 && !piece(chess->board[chess->x + 2][chess->y]) && check_square(chess, chess->x + 2, chess->y)) {
				chess->moves[chess->x + 2][chess->y] = ENABLE_ENPASSANT;
			}
		}
		if(chess->x == 4 && chess->enpassant == chess->y - 1 && check_square(chess, chess->x + 1, chess->y - 1)) {
			chess->moves[chess->x + 1][chess->y - 1] = PLAY_ENPASSANT;
		}
		if(chess->x == 4 && chess->enpassant == chess->y + 1 && check_square(chess, chess->x + 1, chess->y + 1)) {
			chess->moves[chess->x + 1][chess->y + 1] = PLAY_ENPASSANT;
		}
		if(white(chess->board[chess->x + 1][chess->y - 1]) && check_square(chess, chess->x + 1, chess->y - 1)) {
			chess->moves[chess->x + 1][chess->y - 1] = POSSIBLE_MOVE;
		}
		if(white(chess->board[chess->x + 1][chess->y + 1]) && check_square(chess, chess->x + 1, chess->y + 1)) {
			chess->moves[chess->x + 1][chess->y + 1] = POSSIBLE_MOVE;
		}
	}
}

void promotion(Chess *chess, int x1, int y1) {
	if(x1 == 0 && chess->board[x1][y1] == WHITE_PAWN) {
		chess->board[x1][y1] = WHITE_QUEEN;
	}
	if(x1 == 7 && chess->board[x1][y1] == BLACK_PAWN) {
		chess->board[x1][y1] = BLACK_QUEEN;
	}
}

void update_enpassant(Chess *chess, int x1, int y1) {
	if(chess->moves[x1][y1] == ENABLE_ENPASSANT) {
		chess->enpassant = y1;
	}
	else {
		chess->enpassant = -1;
	}
	if(chess->moves[x1][y1] == PLAY_ENPASSANT){
		chess->capture = true;
		if(chess->board[chess->x][chess->y] == WHITE_PAWN) {
			chess->board[x1 + 1][y1] = ' ';
		}
		else if(chess->board[chess->x][chess->y] == BLACK_PAWN) {
			chess->board[x1 - 1][y1] = ' ';
		}
	}
}

void knight(Chess *chess) {
	int8_t jmpx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
	int8_t jmpy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
	if(chess->board[chess->x][chess->y] == WHITE_KNIGHT || chess->board[chess->x][chess->y] == BLACK_KNIGHT) {
		for (int i = 0; i < 8; i++) {
			if(check_square(chess, chess->x + jmpx[i], chess->y + jmpy[i])) {
				chess->moves[chess->x + jmpx[i]][chess->y + jmpy[i]] = POSSIBLE_MOVE;
			}
		}
	}
}

void bishop(Chess *chess) {
	for(int i = 1; chess->x + i < 8 && chess->y + i < 8; i++) {
		if(check_square(chess, chess->x + i, chess->y + i)) {
			chess->moves[chess->x + i][chess->y + i] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x + i][chess->y + i])) {
			break;
		}
	}
	for(int i = 1; chess->x + i < 8 && chess->y - i >= 0; i++) {
		if(check_square(chess, chess->x + i, chess->y - i)) {
			chess->moves[chess->x + i][chess->y - i] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x + i][chess->y - i])) {
			break;
		}
	}
	for(int i = 1; chess->x - i >= 0 && chess->y + i < 8; i++) {
		if(check_square(chess, chess->x - i, chess->y + i)) {
			chess->moves[chess->x - i][chess->y + i] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x - i][chess->y + i])) {
			break;
		}
	}
	for(int i = 1; chess->x - i >= 0 && chess->y - i >= 0; i++) {
		if(check_square(chess, chess->x - i, chess->y - i)) {
			chess->moves[chess->x - i][chess->y - i] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x - i][chess->y - i])) {
			break;
		}
	}
}

void rook(Chess *chess) {
	for(int i = 1; chess->x + i < 8; i++) {
		if(check_square(chess, chess->x + i, chess->y)) {
			chess->moves[chess->x + i][chess->y] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x + i][chess->y])) {
			break;
		}
	}
	for(int i = 1; chess->x - i >= 0; i++) {
		if(check_square(chess, chess->x - i, chess->y)) {
			chess->moves[chess->x - i][chess->y] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x - i][chess->y])) {
			break;
		}
	}
	for(int i = 1; chess->y + i < 8; i++) {
		if(check_square(chess, chess->x, chess->y + i)) {
			chess->moves[chess->x][chess->y + i] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x][chess->y + i])) {
			break;
		}
	}
	for(int i = 1; chess->y - i >= 0; i++) {
		if(check_square(chess, chess->x, chess->y - i)) {
			chess->moves[chess->x][chess->y - i] = POSSIBLE_MOVE;
		}
		if(piece(chess->board[chess->x][chess->y - i])) {
			break;
		}
	}
}

void king(Chess *chess) {
	if(check_square(chess, chess->x + 1, chess->y)) {
		chess->moves[chess->x + 1][chess->y] = POSSIBLE_MOVE;
	}
	if(check_square(chess, chess->x - 1, chess->y)) {
		chess->moves[chess->x - 1][chess->y] = POSSIBLE_MOVE;
	}
	if(check_square(chess, chess->x, chess->y + 1)) {
		chess->moves[chess->x][chess->y + 1] = POSSIBLE_MOVE;
	}
	if(check_square(chess, chess->x, chess->y - 1)) {
		chess->moves[chess->x][chess->y - 1] = POSSIBLE_MOVE;
	}
	if(check_square(chess, chess->x + 1, chess->y + 1)) {
		chess->moves[chess->x + 1][chess->y + 1] = POSSIBLE_MOVE;
	}
	if(check_square(chess, chess->x + 1, chess->y - 1)) {
		chess->moves[chess->x + 1][chess->y - 1] = POSSIBLE_MOVE;
	}
	if(check_square(chess, chess->x - 1, chess->y + 1)) {
		chess->moves[chess->x - 1][chess->y + 1] = POSSIBLE_MOVE;
	}
	if(check_square(chess, chess->x - 1, chess->y - 1)) {
		chess->moves[chess->x - 1][chess->y - 1] = POSSIBLE_MOVE;
	}
	if(chess->board[chess->x][chess->y] == WHITE_KING && chess->board[7][5] == ' ' && chess->board[7][6] == ' ' && chess->oo_white) {
		if(chess->ch && !check(chess, 7, 6) && !check(chess, 7, 5) && !check(chess, 7, 4)) {
			chess->moves[7][6] = WHITE_OO;
		}
	}
	if(chess->board[chess->x][chess->y] == WHITE_KING && chess->board[7][3] == ' ' && chess->board[7][2] == ' ' && chess->board[7][1] == ' ' && chess->ooo_white) {
		if(chess->ch && !check(chess, 7, 2) && !check(chess, 7, 3) && !check(chess, 7, 4)) {
			chess->moves[7][2] = WHITE_OOO;
		}
	}
	if(chess->board[chess->x][chess->y] == BLACK_KING && chess->board[0][5] == ' ' && chess->board[0][6] == ' ' && chess->oo_black) {
		if(chess->ch && !check(chess, 0, 6) && !check(chess, 0, 5) && !check(chess, 0, 4)) {
			chess->moves[0][6] = BLACK_OO;
		}
	}
	if(chess->board[chess->x][chess->y] == BLACK_KING && chess->board[0][3] == ' ' && chess->board[0][2] == ' ' && chess->board[0][1] && chess->ooo_black) {
		if(chess->ch && !check(chess, 0, 2) && !check(chess, 0, 3) && !check(chess, 0, 4)) {
			chess->moves[0][2] = BLACK_OOO;
		}
	}
}

void castle(Chess *chess, int x1, int y1) {
	if(chess->board[7][7] != WHITE_ROOK) {
		chess->oo_white = false;
	}
	if(chess->board[7][0] != WHITE_ROOK) {
		chess->ooo_white = false;
	}
	if(chess->board[7][4] != WHITE_KING) {
		chess->oo_white = false;
		chess->ooo_white = false;
	}
	if(chess->board[0][7] != BLACK_ROOK) {
		chess->oo_black = false;
	}
	if(chess->board[0][0] != BLACK_ROOK) {
		chess->ooo_black = false;
	}
	if(chess->board[0][4] != BLACK_KING) {
		chess->oo_black = false;
		chess->ooo_black = false;
	}
	if(chess->moves[x1][y1] == WHITE_OO) {
		chess->board[7][5] = chess->board[7][7];
		chess->board[7][7] = ' ';
	}
	if(chess->moves[x1][y1] == WHITE_OOO) {
		chess->board[7][3] = chess->board[7][0];
		chess->board[7][0] = ' ';
	}
	if(chess->moves[x1][y1] == BLACK_OO) {
		chess->board[0][5] = chess->board[0][7];
		chess->board[0][7] = ' ';
	}
	if(chess->moves[x1][y1] == BLACK_OOO) {
		chess->board[0][3] = chess->board[0][0];
		chess->board[0][0] = ' ';
	}
}

bool check(Chess *chess, int x1, int y1) {
	chess->ch = false;
	chess->next_check = false;
	int tmp_x = chess->x;
	int tmp_y = chess->y;
	char tmp_piece = ' ';
	if(x1 != -1) {
		tmp_piece = chess->board[x1][y1];
		chess->board[x1][y1] = chess->board[chess->x][chess->y];
		chess->board[chess->x][chess->y] = ' ';
	}
	int tmp_moves[64];
	memcpy(tmp_moves, *chess->moves, 64 * sizeof(int));

	for(int i = 0; i < 8 && !chess->next_check; i++) {
		for(int j = 0; j < 8 && !chess->next_check; j++) {
			select_piece(chess, i, j);
		}
	}

	chess->x = tmp_x;
	chess->y = tmp_y;
	if(x1 != -1) {
		chess->board[chess->x][chess->y] = chess->board[x1][y1];
		chess->board[x1][y1] = tmp_piece;
	}
	memcpy(*chess->moves, tmp_moves, 64 * sizeof(int));
	chess->ch = true;
	return chess->next_check;
}

void check_mate(Chess *chess) {
	chess->mate = DRAW;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			select_piece(chess, i, j);
		}
	}
	if(chess->mate && check(chess, -1, -1)) {
		chess->mate = WHITE_WON;
		if(chess->turn) {
			chess->mate = BLACK_WON;
		}
	}
}
