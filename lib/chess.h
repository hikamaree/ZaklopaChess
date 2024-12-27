#ifndef GAME_H
#define GAME_H

#include <stdint.h>
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

typedef enum : uint8_t {
	NONE = 0,
	DRAW,
	WHITE_WON,
	BLACK_WON,
} Mate;

typedef struct {
	bool ch;
	bool next_check;
	bool oo_white;
	bool ooo_white;
	bool oo_black;
	bool ooo_black;
	int enpassant;
	char move[5];
	Square** board;
	Move** moves;
	int x;
	int y;
	bool turn;
	bool moved;
	bool capture;
	Mate mate;
} Chess;

#define RESIGN_WHITE "R"
#define RESIGN_BLACK "r"

#define reset(moves) (memset(*moves, 0, 64 * sizeof(Move)))
#define white(piece) (piece >= 'A' && piece <= 'Z')
#define black(piece) (piece >= 'a' && piece <= 'z')
#define piece(square) (black(square) || white(square))

Chess* init_chess();
Chess* copy_chess(Chess*);
void delete_chess(Chess*);

void new_game(Chess*);
void play(Chess*, const int, const int);
void play_move(Chess*, const char*);
void set_possition(Chess*, const char*);
void select_piece(Chess* chess, int x, int y);
void move_piece(Chess* chess, int x, int y);

#endif
