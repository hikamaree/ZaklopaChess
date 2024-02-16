#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum : char {
	EMPTY = ' ',
	WHITE_PAWN = 'P',
	WHITE_KNIGHT = 'N',
	WHITE_BISHOP = 'B',
	WHITE_ROOK = 'R',
	WHITE_QUEEN = 'Q',
	WHITE_KING = 'K',
	BLACK_PAWN = 'p',
	BLACK_KNIGHT = 'n',
	BLACK_BISHOP = 'b',
	BLACK_ROOK = 'r',
	BLACK_QUEEN = 'q',
	BLACK_KING = 'k',
} Square;

typedef Square** Board;

typedef enum : int8_t {
	INPOSSIBLE_MOVE = 0,
	POSSIBLE_MOVE = 1,
	ENABLE_ENPASSANT = 2,
	PLAY_ENPASSANT = 3,
	WHITE_OO = 4,
	WHITE_OOO = 5,
	BLACK_OO = 6,
	BLACK_OOO = 7,
} Move;

typedef struct {
	bool ch;
	bool next_check;
	bool oo_white;
	bool ooo_white;
	bool oo_black;
	bool ooo_black;
	int enpassant;
	char move[5];
	Board board;
	Move** moves;
	int x;
	int y;
	bool turn;
	bool moved;
	bool capture;
	int mate;
} Chess;

#define reset(moves) (memset(*moves, 0, 64 * sizeof(Move)))

#define white(piece) (piece >= 'A' && piece <= 'Z')
#define black(piece) (piece >= 'a' && piece <= 'z')
#define piece(square) (black(square) || white(square))

Chess* init_chess();
void delete_chess(Chess* chess);

void new_game(Chess *chess);
void play(Chess* chess, int x, int y);
void play_move(Chess* chess, char* move);

bool check_square(Chess *chess, int x1, int y1);
void update_enpassant(Chess *chess, int x1, int y1);
void promotion(Chess *chess, int x1, int y1);
void castle(Chess *chess, int x1, int y1);
void make_move(Chess *chess, int x1, int y1);
bool check(Chess *chess, int x1, int y1);
void check_mate(Chess *chess);

void pawn(Chess *chess);
void knight(Chess *chess);
void bishop(Chess *chess);
void rook(Chess *chess);
void king(Chess *chess);

#endif
