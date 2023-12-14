#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool ch;
    bool next_check;
    bool oo_white;
    bool ooo_white;
    bool oo_black;
    bool ooo_black;
    int enpassant;
    char move[6];
    char position[8][8];
    int possible[8][8];
    int x;
    int y;
    bool turn;
    bool moved;
    bool capture;
    int mate;
} Chess;

void new_game(Chess *chess);
void play(Chess* chess, int x, int y);
void play_move(Chess* chess, char* move);

#endif
