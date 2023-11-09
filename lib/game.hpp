#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Game {
    private:
    bool ch;
    bool next_check;
    bool oo_white;
    bool ooo_white;
    bool oo_black;
    bool ooo_black;
    int enpassant;
    string move;

    void reset_possible();
    bool check_square(int x1, int y1);
    void update_enpassant(int x1, int y1);
    void promotion(int x1, int y1);
    void castle(int x1, int y1);
    void make_move(int x1, int y1);
    bool check(int x1, int y1);
    void end();

    void pawn();
    void knight();
    void bishop();
    void rook();
    void king();

    public:
    char position[8][8];
    int possible[8][8];
    int x;
    int y;
    bool turn;
    bool moved;
    bool capture;
    int mate;
    Game();
    void new_game();
    void play(int x, int y);
    void play_move(string move);
};

#endif
