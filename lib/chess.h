#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <uchar.h>

typedef struct {
	bool ch;
	bool next_check;
	bool oo_white;
	bool ooo_white;
	bool oo_black;
	bool ooo_black;
	int enpassant;
	char move[5];
	char** position;
	int** possible;
	int x;
	int y;
	bool turn;
	bool moved;
	bool capture;
	int mate;
} Chess;

Chess* init_chess();
void delete_chess(Chess* chess);

void new_game(Chess *chess);
void play(Chess* chess, int x, int y);
void play_move(Chess* chess, char* move);

void reset(int** possible);
bool white(char piece);
bool black(char piece);
bool piece(char piece);

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
