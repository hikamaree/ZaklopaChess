#ifndef UI_H
#define UI_H

#include <raylib.h>
#include <stdlib.h>

#define B_SQUARE (Color){ 110, 109, 107, 255 }
#define W_SQUARE (Color){ 144, 143, 141, 255 }
#define S_SQUARE (Color){ 117, 144, 161, 255 }
#define P_SQUARE (Color){ 0, 0, 0, 64 }
#define TEXT_COLOR (Color){ 192, 202, 245, 255 }
#define BACKGROUND (Color){ 26, 27, 38, 255 }
#define BUTTON_D (Color){ 22, 22, 30, 255 }
#define BUTTON (Color){ 41, 46, 66, 255 }
#define END_SCREEN (Color){ 0, 0, 0, 64 }

typedef struct Ui {
    bool options;
    bool rotation;
    bool perspective;
    bool sound;
    bool coordinate;
    bool newgame;

    Texture2D w_king;
    Texture2D w_queen;
    Texture2D w_rook;
    Texture2D w_bishop;
    Texture2D w_knight;
    Texture2D w_pawn;
    Texture2D b_king;
    Texture2D b_queen;
    Texture2D b_rook;
    Texture2D b_bishop;
    Texture2D b_knight;
    Texture2D b_pawn;

    Sound move_sound;
    Sound capture_sound;

    Rectangle button1;
    Rectangle button2;
    Rectangle button3;
    Rectangle button4;
    Rectangle button5;

    Rectangle end;
} Ui;

void set_ui(Ui *ui);
void draw(Ui *ui, char position[8][8], int possible[8][8], int x, int y, bool turn, int mate);
void input(Ui *ui, int *x, int *y, bool turn);
void play_sound(Ui *ui, bool capture);
void end_game(Ui *ui, int mate);
void close_ui(Ui *ui);

#endif
